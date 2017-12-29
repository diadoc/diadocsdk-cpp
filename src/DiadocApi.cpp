#include "stdafx.h"
#include "DiadocApi.h"
#include "ApiException.h"
#include "HttpConnect.h"
#include "HttpException.h"
#include "CertSystemStore.h"
#include "CryptHelper.h"
#include "StringHelper.h"
#include "Invoicing\FnsRegistrationMessageInfo.pb.h"

using namespace Diadoc::Api::Proto;
using namespace Diadoc::Api::Proto::Recognition;
using namespace Diadoc::Api::Proto::Documents;
using namespace Diadoc::Api::Proto::Documents::Types;
using namespace Diadoc::Api::Proto::Docflow;
using namespace Diadoc::Api::Proto::Forwarding;
using namespace Diadoc::Api::Proto::Events;
using namespace Diadoc::Api::Proto::Invoicing;
using namespace Diadoc::Api::Proto::KeyValueStorage;

const std::wstring DiadocApi::GET(L"GET");
const std::wstring DiadocApi::POST(L"POST");

DiadocApi::DiadocApi(const std::wstring& serverUrl, const std::wstring& clientId, const std::wstring& proxyUrl, bool useDefaultProxySettings)
	: api_client_id_(clientId)
	, session_(InitSession(proxyUrl, useDefaultProxySettings))
{
	WppTraceDebugOut(L"DiadocApi::DiadocApi(\"%s\", ...)", serverUrl.c_str());
	ParseServerUrl(serverUrl, &api_url_, &api_port_, &connection_flags_);
	WppTraceDebugOut(L"ParseServerUrl:");
	WppTraceDebugOut(L"\tapi_url_: %s", api_url_.c_str());
	WppTraceDebugOut(L"\tapi_port_: %i", api_port_);
	WppTraceDebugOut(L"\tconnection_flags_: %x", connection_flags_);
}

void DiadocApi::ParseServerUrl(const std::wstring& serverUrl, std::wstring* apiHost, INTERNET_PORT* port, DWORD* flags)
{
	*port = INTERNET_DEFAULT_HTTPS_PORT;
	*flags = WINHTTP_FLAG_SECURE;
	std::wstring::size_type hostBegin = 0;
	static const std::wstring protocolDelimiter(L"://");
	auto protocolOff = serverUrl.find_first_of(protocolDelimiter);
	if (protocolOff != std::wstring::npos)
	{
		hostBegin = protocolOff + protocolDelimiter.size();
		auto protocol = serverUrl.substr(0, protocolOff);
		if (protocol == L"http")
		{
			*port = INTERNET_DEFAULT_HTTP_PORT;
			*flags = 0;
		}
		else if (protocol != L"https")
		{
			std::stringstream buf;
			buf << "Invalid argument (serverUrl), protocol: " << StringHelper::Utf16ToUtf8(protocol);
			throw std::runtime_error(buf.str());
		}
	}
	auto hostEnd = serverUrl.find_first_of(L'/', hostBegin);
	auto hostStr = serverUrl.substr(hostBegin, hostEnd != std::wstring::npos ? hostEnd - hostBegin : std::wstring::npos);
	auto portOff = hostStr.find_first_of(L':');
	if (portOff != std::wstring::npos)
	{
		auto portStr = hostStr.substr(portOff + 1);
		*port = static_cast<INTERNET_PORT>(_tcstoul(portStr.c_str(), NULL, 0));
	}
	*apiHost = hostStr.substr(0, portOff);
}

Diadoc::Api::Proto::Invoicing::Signers::DocumentTitleType DiadocApi::CreateUtdDocumentTitleType(bool forBuyer, bool forCorrection)
{
    return forBuyer
        ? (forCorrection ? Signers::UcdBuyer : Signers::UtdBuyer)
        : (forCorrection ? Signers::UcdSeller : Signers::UtdSeller);
}

DiadocApi::~DiadocApi() 
{
}

DiadocApi::Bytes_t DiadocApi::ToProtoBytes(const google::protobuf::MessageLite& obj)
{
	Bytes_t bytes;
	auto size = obj.ByteSize();
	if (size == 0) return bytes;
	bytes.resize(size);
	obj.SerializeToArray(&bytes[0], size);
	return bytes;
}

std::wstring DiadocApi::GetDocumentPathUrl(std::wstring boxId, std::wstring messageId, std::wstring entityId)
{
	std::wstring url;
	url += L"/";

	// Get BoxId in true format
	std::wstring boxIdInTrueFormat;
	boxIdInTrueFormat = boxId.substr(0, 8) + L"-" + boxId.substr(8, 4) + L"-" + boxId.substr(12, 4) + L"-" + boxId.substr(16, 4) + L"-" + boxId.substr(20, 12);

	url += boxIdInTrueFormat + L"/Document/Show?letterId=" + messageId + L"&documentId=" + entityId;

	return url;
}

void DiadocApi::SetProxyCredentials(const std::wstring& username, const std::wstring& password)
{
	proxy_username_ = username;
	proxy_password_ = password;
}

std::wstring DiadocApi::GetAuthToken()
{
	return token_;
}

HttpSession DiadocApi::InitSession(std::wstring proxyUrl, bool useDefaultProxySettings)
{
	if (!proxyUrl.empty()) {
		WppTraceDebugOut(L"Passed not empty proxyUrl to InitSession: %s", proxyUrl.c_str());
		return HttpSession(GetUserAgent().c_str(), WINHTTP_ACCESS_TYPE_NAMED_PROXY, proxyUrl.c_str(), L"<local>", 0);
	}

	BOOL fAutoProxy = FALSE;
	WINHTTP_AUTOPROXY_OPTIONS autoProxyOptions;
	WINHTTP_PROXY_INFO autoProxyInfo;
	autoProxyOptions.dwFlags = 0;
	autoProxyOptions.dwAutoDetectFlags = 0;
	autoProxyOptions.lpvReserved = NULL;
	autoProxyOptions.dwReserved = 0;

	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG pProxyConfig;
	memset(&pProxyConfig, 0, sizeof(pProxyConfig));
	WppTraceDebugOut(L"Calling WinHttpGetIEProxyConfigForCurrentUser...");
	if( useDefaultProxySettings && WinHttpGetIEProxyConfigForCurrentUser( &pProxyConfig ))
	{
		if( pProxyConfig.fAutoDetect )
		{
			WppTraceDebugOut(L"\tfAutoProxy: TRUE");
			fAutoProxy = TRUE;
		}

		if( pProxyConfig.lpszAutoConfigUrl != NULL )
		{
			fAutoProxy = TRUE;
			autoProxyOptions.dwFlags |= WINHTTP_AUTOPROXY_CONFIG_URL;
			autoProxyOptions.lpszAutoConfigUrl = pProxyConfig.lpszAutoConfigUrl;
			WppTraceDebugOut(L"\tfAutoProxy: TRUE");
			WppTraceDebugOut(L"\tdwFlags: WINHTTP_AUTOPROXY_CONFIG_URL");
			WppTraceDebugOut(L"\tlpszAutoConfigUrl: %s",pProxyConfig.lpszAutoConfigUrl);
		}
	}
	else if (useDefaultProxySettings)
	{
		fAutoProxy = TRUE;
		WppTraceDebugOut(L"WinHttpGetIEProxyConfigForCurrentUser returns FALSE, GetLastError(): %i", GetLastError());
	}

	if( fAutoProxy )
	{
		WppTraceDebugOut(L"Setting autoProxyOptions...");
		// basic flags you almost always want
		autoProxyOptions.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
		autoProxyOptions.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
		autoProxyOptions.fAutoLogonIfChallenged = TRUE;
		HINTERNET hiOpen = WinHttpOpen(_T("WinHTTP AutoProxy/1.0"), WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
		// here we reset fAutoProxy in case an auto-proxy isn't actually
		// configured for this url
		WppTraceDebugOut(L"Calling WinHttpGetProxyForUrl for https://diadoc-api.kontur.ru...");
		fAutoProxy = WinHttpGetProxyForUrl( hiOpen, _T("https://diadoc-api.kontur.ru"), &autoProxyOptions, &autoProxyInfo );
		if (!fAutoProxy)
			WppTraceDebugOut(L"WinHttpGetProxyForUrl return false, GetLastError: %i", GetLastError());
	}

	if ( fAutoProxy )
	{
		WppTraceDebugOut(L"Set proxy options based on autoProxyInfo:");
		WppTraceDebugOut(L"\tdwAccessType: %x",autoProxyInfo.dwAccessType);
		WppTraceDebugOut(L"\tlpszProxy: %s",autoProxyInfo.lpszProxy);
		WppTraceDebugOut(L"\tlpszProxyBypass: %s",autoProxyInfo.lpszProxyBypass);
		return HttpSession(GetUserAgent().c_str(), autoProxyInfo.dwAccessType, autoProxyInfo.lpszProxy, autoProxyInfo.lpszProxyBypass, 0);
	}
	else
	{
		if( pProxyConfig.lpszProxy != NULL )
		{
			WppTraceDebugOut(L"Set proxy options based on pProxyConfig");
			WppTraceDebugOut(L"\tdwAccessType: WINHTTP_ACCESS_TYPE_NAMED_PROXY");
			WppTraceDebugOut(L"\tlpszProxy: %s",pProxyConfig.lpszProxy);
			WppTraceDebugOut(L"\tlpszProxyBypass: %s",pProxyConfig.lpszProxyBypass);
			decltype(InitSession(L"")) session(GetUserAgent().c_str(), WINHTTP_ACCESS_TYPE_NAMED_PROXY, pProxyConfig.lpszProxy, pProxyConfig.lpszProxyBypass, 0);
			if (pProxyConfig.lpszAutoConfigUrl)
				GlobalFree(pProxyConfig.lpszAutoConfigUrl);
			if (pProxyConfig.lpszProxy)
				GlobalFree(pProxyConfig.lpszProxy);
			if (pProxyConfig.lpszProxyBypass)
				GlobalFree(pProxyConfig.lpszProxyBypass);
			return session;
		}
		else
		{
			// there is no auto proxy and no manually configured proxy
		}
	}

	WppTraceDebugOut(L"Not using proxy");
	return HttpSession(GetUserAgent().c_str(), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
}

DiadocApi::Bytes_t DiadocApi::PerformHttpRequest(const std::wstring& queryString, const std::wstring& method)
{
	return PerformHttpRequest(queryString, Bytes_t(), method);
}

std::string DiadocApi::PerformHttpRequestString(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method)
{
	auto responseBytes = PerformHttpRequest(queryString, requestBody, method);
	return std::string(responseBytes.begin(), responseBytes.end());
}

std::string DiadocApi::PerformHttpRequestString(const std::wstring& queryString, const std::wstring& method)
{
	auto responseBytes = PerformHttpRequest(queryString, method);
	return std::string(responseBytes.begin(), responseBytes.end());
}

DWORD ChooseAuthScheme(DWORD dwSupportedSchemes)
{
	//  It is the server's responsibility only to accept 
	//  authentication schemes that provide a sufficient
	//  level of security to protect the servers resources.
	//
	//  The client is also obligated only to use an authentication
	//  scheme that adequately protects its username and password.
	//
	//  Thus, this sample code does not use Basic authentication  
	//  because Basic authentication exposes the client's username
	//  and password to anyone monitoring the connection.

	if (dwSupportedSchemes & WINHTTP_AUTH_SCHEME_NEGOTIATE)
		return WINHTTP_AUTH_SCHEME_NEGOTIATE;
	else if (dwSupportedSchemes & WINHTTP_AUTH_SCHEME_NTLM)
		return WINHTTP_AUTH_SCHEME_NTLM;
	else if (dwSupportedSchemes & WINHTTP_AUTH_SCHEME_DIGEST)
		return WINHTTP_AUTH_SCHEME_DIGEST;
	else if (dwSupportedSchemes & WINHTTP_AUTH_SCHEME_BASIC)
		return WINHTTP_AUTH_SCHEME_BASIC;
	else
		return 0;
}

DiadocApi::Bytes_t DiadocApi::PerformHttpRequest(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method)
{
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(method.c_str(), queryString.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return request.ReadAllResponse();
}

TaskResult<DiadocApi::Bytes_t> DiadocApi::PerformAsyncHttpRequest(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method)
{
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(method.c_str(), queryString.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	int retryAfter;
	if (request.TryGetRetryAfter(&retryAfter))
		return TaskResult<Bytes_t>::CreateWithRetryAfter(retryAfter);
	return TaskResult<Bytes_t>::CreateWithResult(request.ReadAllResponse());
}

std::string response_as_string(const HttpRequest& request)
{
	auto bytes = request.ReadAllResponse();
	return std::string(bytes.begin(), bytes.end());
}

void DiadocApi::SendRequest(HttpRequest& request, const Bytes_t& requestBody)
{
	WppTraceDebugOut(L"SendRequest...");
	DWORD dwProxyAuthScheme = 0;
	auto autorizationHeader = AuthorizationHeader();
	int authorizationCount = 0;
	while (true)
	{
		//  If a proxy authentication challenge was responded to, reset
		//  those credentials before each SendRequest, because the proxy  
		//  may require re-authentication after responding to a 401 or  
		//  to a redirect. If you don't, you can get into a 
		//  407-401-407-401- loop.
		if(dwProxyAuthScheme != 0)
		{
			WppTraceDebugOut(L"\tSetCredentials for request:");
			WppTraceDebugOut(L"\t\tdwProxyAuthScheme: %x",dwProxyAuthScheme);
			request.SetCredentials(WINHTTP_AUTH_TARGET_PROXY, dwProxyAuthScheme, proxy_username_.c_str(), proxy_password_.c_str(), NULL);
		}

		WppTraceDebugOut(L"\tSending request...");
		request.Send(autorizationHeader.c_str(), autorizationHeader.size(), WINHTTP_NO_REQUEST_DATA, 0, requestBody.size(), 0);
		if (!requestBody.empty()) {
			WppTraceDebugOut(L"\tWriting data (%i size)...",requestBody.size());
			request.WriteData(&requestBody[0], requestBody.size());
		}

		try
		{
			WppTraceDebugOut(L"\tReceiving response...");
			request.ReceiveResponse(NULL);
		}
		catch (ApiException& e)
		{
			if (e.CauseCode != ERROR_WINHTTP_RESEND_REQUEST) throw;
			continue;
		}
		auto dwStatusCode = request.GetStatusCode();
		WppTraceDebugOut(L"\t\tstatus code: %i", dwStatusCode);
		WppTraceDebugOut(L"\t\tHTTP headers from response: %s", request.DebugQueryAllHeaders().c_str());
		switch(dwStatusCode)
		{
		case HTTP_STATUS_OK:
		case HTTP_STATUS_NO_CONTENT:
			return;

		case HTTP_STATUS_PROXY_AUTH_REQ:
			{
				if (proxy_username_.empty())
					throw HttpException("Proxy authentication failed: no user name provided", dwStatusCode, response_as_string(request));
				if (++authorizationCount > 2)
					throw HttpException("Proxy authentication failed: no attempts left", dwStatusCode, response_as_string(request));
				DWORD dwSupportedSchemes;
				DWORD dwFirstScheme;
				DWORD dwTarget;
				request.QueryAuthSchemes(&dwSupportedSchemes, &dwFirstScheme, &dwTarget);
				DWORD dwSelectedScheme = ChooseAuthScheme(dwSupportedSchemes);
				if(dwSelectedScheme == 0)
					throw HttpException("Proxy authentication failed: can not select auth scheme", dwStatusCode, response_as_string(request));
				WppTraceDebugOut(L"\t\tdwSelectedScheme: %i", dwSelectedScheme);
				request.SetCredentials(dwTarget, dwSelectedScheme, proxy_username_.c_str(), proxy_password_.c_str(), NULL);
			}
			break;
		case HTTP_STATUS_DENIED:
			throw HttpException("Server authorization failed", dwStatusCode, response_as_string(request));

		default:
			// The status code does not indicate success.
			throw HttpException("HTTP error", dwStatusCode, response_as_string(request));
		}
	}
}

std::wstring DiadocApi::AuthorizationHeader()
{
	std::wstringstream headers_stream;
	headers_stream << L"Authorization: DiadocAuth ddauth_api_client_id=" << api_client_id_;
	if (token_.length() > 0)
		headers_stream << L",ddauth_token=" << token_.c_str();
	return headers_stream.str();
}

std::wstring DiadocApi::GetUserAgent()
{
	return L"Diadoc API C++ v" + GetVersionString();
}

std::wstring DiadocApi::GetVersionString()
{
	TCHAR fileName[MAX_PATH];
	GetModuleFileName(NULL, fileName, sizeof(fileName));
	auto dwSize = GetFileVersionInfoSize(fileName, NULL);
	if(dwSize == 0)
		return std::wstring(L"x.x.x.x");

	std::vector<char> buffer;
	buffer.resize(dwSize);
	if(!GetFileVersionInfo(fileName, 0, dwSize, &buffer[0]))
		return std::wstring(L"x.x.x.x");

	UINT uiSize;
	VS_FIXEDFILEINFO* data = NULL;
	if(!VerQueryValue(&buffer[0], L"\\", (void**)&data, &uiSize) || data == NULL || uiSize != sizeof(VS_FIXEDFILEINFO))
		return std::wstring(L"x.x.x.x");

	std::wstringstream wss;
	wss << (data->dwProductVersionMS >> 16) << L"." << (data->dwProductVersionMS & 0xFFFF) << L"." << (data->dwProductVersionLS >> 16) << L"." << (data->dwProductVersionLS & 0xFFFF);
	return wss.str();
}

BoxList DiadocApi::GetBoxes()
{
	WppTraceDebugOut(L"GetBoxes...");
	std::wstringstream wss;
	wss << L"/GetBoxesByAuthToken";
	return FromProtoBytes<BoxList>(PerformHttpRequest(wss.str(), GET));
}

BoxList DiadocApi::GetBoxesByInnKpp(const std::wstring& inn, const std::wstring& kpp)
{
	WppTraceDebugOut(L"GetBoxesByInnKpp...");
	std::wstringstream buf;
	buf << L"/GetBoxesByInnKpp?inn=" << StringHelper::CanonicalizeUrl(inn);
	if (!kpp.empty())
		buf << L"&kpp=" << StringHelper::CanonicalizeUrl(kpp);
	return FromProtoBytes<BoxList>(PerformHttpRequest(buf.str(), GET));
}

BoxInfo DiadocApi::GetBoxInfo(const std::wstring& boxId)
{
	WppTraceDebugOut(L"GetBoxInfo...");
	std::wstringstream buf;
	buf << L"/GetBoxInfo?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	return FromProtoBytes<BoxInfo>(PerformHttpRequest(buf.str(), GET));
}

void DiadocApi::Authenticate(const std::wstring& login, const std::wstring& password)
{
	WppTraceDebugOut(L"Authenticating by login/password pair...");
	std::wstringstream wss;
	wss << L"/Authenticate?login=" << StringHelper::CanonicalizeUrl(login) << L"&password=" << StringHelper::CanonicalizeUrl(password) << std::flush;
	auto response = PerformHttpRequestString(wss.str(), POST);
	token_ = StringHelper::Utf8ToUtf16(response);
}

void DiadocApi::Authenticate(const Bytes_t& certBytes, bool useLocalMachineStorage)
{
	WppTraceDebugOut(L"Authenticating by certBytes...");
	auto response = PerformHttpRequest(L"/Authenticate", certBytes, POST);
	CertSystemStore store(useLocalMachineStorage);
	auto decryptedResponse = store.Decrypt(response);
	token_ = CryptHelper::ToBase64(decryptedResponse);
}

void DiadocApi::VerifyThatUserHasAccessToAnyBox(const Bytes_t& certBytes)
{
	WppTraceDebugOut(L"Verifing that user has access to any box...");
	auto response = PerformHttpRequest(L"/VerifyThatUserHasAccessToAnyBox", certBytes, POST);
}

void DiadocApi::RecycleDraft(const std::wstring& boxId, const std::wstring& draftId)
{
	WppTraceDebugOut(L"RecycleDraft...");
	std::wstringstream queryString;
	queryString << L"/RecycleDraft?boxId=" << boxId << L"&draftId=" << draftId;
	PerformHttpRequest(queryString.str(), POST);
}

std::wstring DiadocApi::Recognize(const std::wstring& fileName, const Bytes_t& fileContent)
{
	WppTraceDebugOut(L"Recognize...");
	std::wstringstream wss;
	wss << L"/Recognize?filename=" << StringHelper::CanonicalizeUrl(fileName);
	return StringHelper::Utf8ToUtf16(PerformHttpRequestString(wss.str(), fileContent, POST));
}

BoxEventList DiadocApi::GetNewEvents(const std::wstring& boxId, const std::wstring& afterEventId)
{
	WppTraceDebugOut(L"GetNewEvents...");
	std::wstringstream queryString;
	queryString << L"/V5/GetNewEvents?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	if (!afterEventId.empty())
		queryString << L"&afterEventId=" << StringHelper::CanonicalizeUrl(afterEventId);
	queryString << L"&includeDrafts";
	return FromProtoBytes<BoxEventList>(PerformHttpRequest(queryString.str(), GET));
}

BoxEvent DiadocApi::GetEvent(const std::wstring& boxId, const std::wstring& eventId)
{
	WppTraceDebugOut(L"GetEvent...");
	std::wstringstream buf;
	buf << L"/V2/GetEvent?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&eventId=" << StringHelper::CanonicalizeUrl(eventId);
	return FromProtoBytes<BoxEvent>(PerformHttpRequest(buf.str(), GET));
}

Message DiadocApi::PostDiadocMessage(const MessageToPost& msg, const std::wstring& operationId)
{
	WppTraceDebugOut(L"PostDiadocMessage...");
	std::wstringstream buf;
	buf << L"/V3/PostMessage";
	if (!operationId.empty())
		buf << L"?operationId=" << StringHelper::CanonicalizeUrl(operationId);
	return FromProtoBytes<Message>(PerformHttpRequest(buf.str(), ToProtoBytes(msg), POST));
}

MessagePatch DiadocApi::PostMessagePatch(const MessagePatchToPost& patch, const std::wstring& operationId)
{
	WppTraceDebugOut(L"PostMessagePatch...");
	std::wstringstream buf;
	buf << L"/V3/PostMessagePatch";
	if (!operationId.empty())
		buf << L"?operationId=" << StringHelper::CanonicalizeUrl(operationId);
	return FromProtoBytes<MessagePatch>(PerformHttpRequest(buf.str(), ToProtoBytes(patch), POST));
}

PrepareDocumentsToSignResponse DiadocApi::PrepareDocumentsToSign(const PrepareDocumentsToSignRequest& request)
{
	WppTraceDebugOut("PrepareDocumentsToSign...");
	DiadocApi::Bytes_t result = PerformHttpRequest(L"/PrepareDocumentsToSign", ToProtoBytes(request), POST);
	return FromProtoBytes<PrepareDocumentsToSignResponse>(result);
}

Message DiadocApi::SendDraft(const DraftToSend& request, const std::wstring& operationId)
{
	WppTraceDebugOut(L"SendDraft...");
	std::wstringstream buf;
	buf << L"/SendDraft";
	if (!operationId.empty())
		buf << L"?operationId=" << StringHelper::CanonicalizeUrl(operationId);
	return FromProtoBytes<Message>(PerformHttpRequest(buf.str(), ToProtoBytes(request), POST));
}

DiadocApi::Bytes_t DiadocApi::GetEntityContent(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId)
{
	WppTraceDebugOut(L"GetEntityContent...");
	std::wstringstream buf;
	buf << L"/V4/GetEntityContent?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);
	return PerformHttpRequest(buf.str(), GET);
}

Message DiadocApi::GetDiadocMessage(const std::wstring& boxId, const std::wstring& messageId, bool withOriginalSignature, bool injectEntityContent)
{
	WppTraceDebugOut(L"GetDiadocMessage...");
	std::wstringstream buf;
	buf << L"/V4/GetMessage?"
		<< L"boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&messageId=" << StringHelper::CanonicalizeUrl(messageId);

	if (withOriginalSignature) buf << L"&originalSignature";
	buf << L"&injectEntityContent=" << (injectEntityContent ? L"True" : L"False");

	return FromProtoBytes<Message>(PerformHttpRequest(buf.str(), GET));
}

Message DiadocApi::GetDiadocMessage(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId, bool withOriginalSignature, bool injectEntityContent)
{
	WppTraceDebugOut(L"GetDiadocMessage...");
	std::wstringstream buf;
	buf << L"/V4/GetMessage?"
		<< L"boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&messageId=" << StringHelper::CanonicalizeUrl(messageId)
		<< L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);

	if (withOriginalSignature) buf << L"&originalSignature";
	buf << L"&injectEntityContent=" << (injectEntityContent ? L"True" : L"False");
	
	return FromProtoBytes<Message>(PerformHttpRequest(buf.str(), GET));
}

Recognized DiadocApi::GetRecognized(const std::wstring& recognitionId)
{
	WppTraceDebugOut("GetRecognized...");
	std::wstringstream queryString;
	queryString << L"/GetRecognized?recognitionId=" << StringHelper::CanonicalizeUrl(recognitionId);
	return FromProtoBytes<Recognized>(PerformHttpRequest(queryString.str(), GET));
}

std::string DiadocApi::GetValueFromDraftResponseLine(const std::string& line)
{
	auto point = line.find_first_of('=');
	return line.substr(point + 1);
}

Organization DiadocApi::GetOrganization(const std::wstring& id, const std::wstring& idName)
{
	WppTraceDebugOut("GetOrganization...");
	std::wstringstream buf;
	buf << L"/GetOrganization?" << idName << L"=" << StringHelper::CanonicalizeUrl(id);
	return FromProtoBytes<Organization>(PerformHttpRequest(buf.str(), GET));
}

OrganizationUsersList DiadocApi::GetOrganizationUsers(const std::wstring& orgId)
{
	WppTraceDebugOut("GetOrganizationUsers...");
	std::wstringstream buf;
	buf << L"/GetOrganizationUsers?orgId=" << StringHelper::CanonicalizeUrl(orgId);
	return FromProtoBytes<OrganizationUsersList>(PerformHttpRequest(buf.str(), GET));
}

DiadocApi::PrintFormResult::PrintFormResult(int retryAfter)
	: RetryAfter(retryAfter)
	, HasContent(false)
{
}

DiadocApi::PrintFormResult::PrintFormResult(const std::wstring& contentType, const std::wstring& fileName, const Bytes_t& bytes)
	: ContentType(contentType)
	, FileName(fileName)
	, Bytes(bytes)
	, HasContent(true)
{
}

DiadocApi::PrintFormResult::PrintFormResult(PrintFormResult&& orig)
{
	RetryAfter = std::move(orig.RetryAfter);
	HasContent = std::move(orig.HasContent);
	ContentType = std::move(orig.ContentType);
	FileName = std::move(orig.FileName);
	Bytes = std::move(orig.Bytes);
}

DiadocApi::PrintFormResult& DiadocApi::PrintFormResult::operator=(PrintFormResult&& right)
{
	RetryAfter = std::move(right.RetryAfter);
	HasContent = std::move(right.HasContent);
	ContentType = std::move(right.ContentType);
	FileName = std::move(right.FileName);
	Bytes = std::move(right.Bytes);
	return *this;
}

DiadocApi::PrintFormResult::~PrintFormResult()
{
}

DiadocApi::PrintFormResult DiadocApi::GeneratePrintForm(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& documentId)
{
	WppTraceDebugOut("GeneratePrintForm...");
	std::wstringstream buf;
	buf << L"/GeneratePrintForm?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&documentId=" << StringHelper::CanonicalizeUrl(documentId);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(L"GET", buf.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, Bytes_t());
	int retryAfter;
	if (request.TryGetRetryAfter(&retryAfter))
	{
		return PrintFormResult(retryAfter);
	}
	return PrintFormResult(request.GetContentType(), request.GetContentDisposition().GetFileName(), request.ReadAllResponse());
}

TaskResult<DocumentProtocol> DiadocApi::GenerateDocumentProtocol(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& documentId)
{
	std::wstringstream buf;
	buf << "?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&documentId=" << StringHelper::CanonicalizeUrl(documentId);
	return PerformAsyncHttpRequest<DocumentProtocol>("GenerateDocumentProtocol", buf.str(), GET);
}

DocumentList DiadocApi::GetDocuments(const std::wstring& boxId, const std::wstring& filterCategory, const std::wstring& counteragentBoxId, __int64* timestampFrom, __int64* timestampTo,
	const std::wstring& fromDocumentDate, const std::wstring& toDocumentDate, const std::wstring& departmentId, bool excludeSubdepartments, const std::string& afterIndexKey, int* count)
{
	DocumentFilter documentFilter(boxId, filterCategory);
	if (!counteragentBoxId.empty())
		documentFilter.CounteragentBoxId = counteragentBoxId;
	documentFilter.TimestampFrom = timestampFrom;
	documentFilter.TimestampTo = timestampTo;
	if (!fromDocumentDate.empty())
		documentFilter.FromDocumentDate = fromDocumentDate;
	if (!toDocumentDate.empty())
		documentFilter.ToDocumentDate = toDocumentDate;
	if (!departmentId.empty())
		documentFilter.DepartmentId = departmentId;
	documentFilter.ExcludeSubdepartments = excludeSubdepartments;
	if (!afterIndexKey.empty())
		documentFilter.AfterIndexKey = afterIndexKey;
	documentFilter.Count = count;
	return GetDocuments(documentFilter);
}

DocumentList DiadocApi::GetDocuments(const DocumentFilter& documentFilter)
{
	WppTraceDebugOut("GetDocuments...");
	std::wstringstream buf;
	buf << L"/V3/GetDocuments?boxId=" << StringHelper::CanonicalizeUrl(documentFilter.BoxId) << L"&filterCategory=" << StringHelper::CanonicalizeUrl(documentFilter.FilterCategory);
	if (!documentFilter.CounteragentBoxId.empty())
		buf << L"&counteragentBoxId=" << StringHelper::CanonicalizeUrl(documentFilter.CounteragentBoxId);
	if (documentFilter.TimestampFrom != NULL)
		buf << L"&timestampFromTicks=" << *documentFilter.TimestampFrom;
	if (documentFilter.TimestampTo != NULL)
		buf << L"&timestampToTicks=" << *documentFilter.TimestampTo;
	if (!documentFilter.FromDocumentDate.empty())
		buf << L"&fromDocumentDate=" << StringHelper::CanonicalizeUrl(documentFilter.FromDocumentDate);
	if (!documentFilter.ToDocumentDate.empty())
		buf << L"&toDocumentDate=" << StringHelper::CanonicalizeUrl(documentFilter.ToDocumentDate);
	if (!documentFilter.DepartmentId.empty())
		buf << L"&departmentId=" << StringHelper::CanonicalizeUrl(documentFilter.DepartmentId);
	if (documentFilter.ExcludeSubdepartments)
		buf << L"&excludeSubdepartments";
	if (!documentFilter.SortDirection.empty())
		buf << L"&sortDirection=" << StringHelper::CanonicalizeUrl(documentFilter.SortDirection);
	if (!documentFilter.AfterIndexKey.empty())
		buf << L"&afterIndexKey=" << StringHelper::CanonicalizeUrl(StringHelper::Utf8ToUtf16(documentFilter.AfterIndexKey));
	if (documentFilter.Count != NULL)
		buf << L"&count=" << *documentFilter.Count;
	return FromProtoBytes<DocumentList>(PerformHttpRequest(buf.str(), GET));
}

Document DiadocApi::GetDocument(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId)
{
	WppTraceDebugOut("GetDocument...");
	std::wstringstream buf;
	buf << L"/V3/GetDocument?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);
	return FromProtoBytes<Document>(PerformHttpRequest(buf.str(), GET));
}

void DiadocApi::Delete(const std::wstring &boxId, const std::wstring &messageId, const std::wstring &documentId)
{
	WppTraceDebugOut("Delete...");
	std::wstringstream queryString;
	queryString << L"/Delete?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId);
	if (!documentId.empty())
		queryString << L"&documentId=" << StringHelper::CanonicalizeUrl(documentId);
	PerformHttpRequest(queryString.str(), POST);
}

DiadocApi::WebFile::WebFile(const HttpRequest& request)
	: FileName(request.GetContentDisposition().GetFileName())
	, Content(request.ReadAllResponse())
{
}

DiadocApi::WebFile::WebFile(WebFile&& orig)
{
	FileName = std::move(orig.FileName);
	Content = std::move(orig.Content);
}

DiadocApi::WebFile& DiadocApi::WebFile::operator=(WebFile&& right)
{
	FileName = std::move(right.FileName);
	Content = std::move(right.Content);
	return *this;
}

DiadocApi::WebFile::~WebFile()
{
}

DiadocApi::WebFile DiadocApi::GenerateDocumentReceiptXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::Signer signer)
{
	WppTraceDebugOut("GenerateDocumentReceiptXml...");
	auto requestBody = ToProtoBytes(signer);
	std::wstringstream buf;
	buf << L"/GenerateDocumentReceiptXml?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&attachmentId=" << StringHelper::CanonicalizeUrl(attachmentId);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), buf.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceDocumentReceiptXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::Signer signer)
{
	WppTraceDebugOut("GenerateInvoiceDocumentReceiptXml...");
	auto requestBody = ToProtoBytes(signer);
	std::wstringstream buf;
	buf << L"/GenerateInvoiceDocumentReceiptXml?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&attachmentId=" << StringHelper::CanonicalizeUrl(attachmentId);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), buf.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceCorrectionRequestXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const InvoiceCorrectionRequestInfo& correctionInfo)
{
	WppTraceDebugOut("GenerateInvoiceCorrectionRequestXml...");
	std::wstringstream queryString;
	queryString << L"/GenerateInvoiceCorrectionRequestXml?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&attachmentId=" << StringHelper::CanonicalizeUrl(attachmentId);
	auto requestBody = ToProtoBytes(correctionInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateRevocationRequestXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const RevocationRequestInfo& revocationRequestInfo)
{
	WppTraceDebugOut("GenerateRevocationRequestXml...");
	std::wstringstream queryString;
	queryString << L"/GenerateRevocationRequestXml?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&attachmentId=" << StringHelper::CanonicalizeUrl(attachmentId);
	auto requestBody = ToProtoBytes(revocationRequestInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateSignatureRejectionXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const SignatureRejectionInfo& signatureRejectionInfo)
{
	WppTraceDebugOut("GenerateSignatureRejectionXml...");
	std::wstringstream queryString;
	queryString << L"/GenerateSignatureRejectionXml?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&attachmentId=" << StringHelper::CanonicalizeUrl(attachmentId);
	auto requestBody = ToProtoBytes(signatureRejectionInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

InvoiceCorrectionRequestInfo DiadocApi::GetInvoiceCorrectionRequestInfo(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId)
{
	WppTraceDebugOut("GetInvoiceCorrectionRequestInfo...");
	std::wstringstream queryString;
	queryString << L"/GetInvoiceCorrectionRequestInfo?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);
	return FromProtoBytes<InvoiceCorrectionRequestInfo>(PerformHttpRequest(queryString.str(), GET));
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceXml(const InvoiceInfo& invoiceInfo, bool disableValidation)
{
	return GenerateInvoiceXml(invoiceInfo, "Invoice", "GenerateInvoiceXml...", disableValidation);
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceRevisionXml(const Diadoc::Api::Proto::Invoicing::InvoiceInfo& invoiceRevisionInfo, bool disableValidation)
{
	return GenerateInvoiceXml(invoiceRevisionInfo, "InvoiceRevision", "GenerateInvoiceRevisionXml...", disableValidation);
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceCorrectionXml(const Diadoc::Api::Proto::Invoicing::InvoiceCorrectionInfo& invoiceCorrectionInfo, bool disableValidation)
{
	return GenerateInvoiceXml(invoiceCorrectionInfo, "InvoiceCorrection", "GenerateInvoiceCorrectionXml...", disableValidation);
}

DiadocApi::WebFile DiadocApi::GenerateInvoiceCorrectionRevisionXml(const Diadoc::Api::Proto::Invoicing::InvoiceCorrectionInfo& invoiceCorrectionRevisionInfo, bool disableValidation)
{
	return GenerateInvoiceXml(invoiceCorrectionRevisionInfo, "InvoiceCorrectionRevision", "GenerateInvoiceCorrectionRevisionXml...", disableValidation);
}

template <typename T>
DiadocApi::WebFile DiadocApi::GenerateInvoiceXml(const T& info, std::string invoiceTypeStr, std::string logString, bool disableValidation)
{
	WppTraceDebugOut(logString.c_str());
	auto requestBody = ToProtoBytes(info);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateInvoiceXml?invoiceType=" << invoiceTypeStr.c_str() << (disableValidation ? L"&disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateTorg12XmlForSeller(const Torg12SellerTitleInfo& torg12SellerInfo, bool disableValidation)
{
	WppTraceDebugOut("GenerateTorg12XmlForSeller...");
	auto requestBody = ToProtoBytes(torg12SellerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateTorg12XmlForSeller" << (disableValidation ? L"?disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateTorg12XmlForBuyer(const Torg12BuyerTitleInfo& torg12BuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId)
{
	WppTraceDebugOut("GenerateTorg12XmlForBuyer...");
	std::wstringstream queryString;
	queryString << L"/GenerateTorg12XmlForBuyer?boxId=" << StringHelper::CanonicalizeUrl(boxId)
				<< L"&sellerTitleMessageId=" << StringHelper::CanonicalizeUrl(sellerTitleMessageId)
				<< L"&sellerTitleAttachmentId=" << StringHelper::CanonicalizeUrl(sellerTitleAttachmentId);
	auto requestBody = ToProtoBytes(torg12BuyerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateTovTorg551XmlForSeller(const TovTorgSellerTitleInfo& tovTorgSellerInfo, bool disableValidation)
{
	WppTraceDebugOut("GenerateTovTorg551XmlForSeller...");
	auto requestBody = ToProtoBytes(tovTorgSellerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateTorg12XmlForSeller?documentVersion=tovtorg_05_01_02" << (disableValidation ? L"&disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateTovTorg551XmlForBuyer(const TovTorgBuyerTitleInfo& tovTorgBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId)
{
	WppTraceDebugOut("GenerateTovTorg551XmlForBuyer...");
	std::wstringstream queryString;
	queryString << L"/GenerateTorg12XmlForBuyer?boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&sellerTitleMessageId=" << StringHelper::CanonicalizeUrl(sellerTitleMessageId)
		<< L"&sellerTitleAttachmentId=" << StringHelper::CanonicalizeUrl(sellerTitleAttachmentId)
		<< L"&documentVersion=tovtorg_05_01_02";
	auto requestBody = ToProtoBytes(tovTorgBuyerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateAcceptanceCertificateXmlForSeller(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificateSellerTitleInfo& acceptanceCertificateSellerInfo, bool disableValidation)
{
	WppTraceDebugOut("GenerateAcceptanceCertificateXmlForSeller...");
	auto requestBody = ToProtoBytes(acceptanceCertificateSellerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateAcceptanceCertificateXmlForSeller" << (disableValidation ? L"?disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateAcceptanceCertificateXmlForBuyer(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificateBuyerTitleInfo& acceptanceCertificateBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId)
{
	WppTraceDebugOut("GenerateAcceptanceCertificateXmlForBuyer...");
	std::wstringstream queryString;
	queryString << L"/GenerateAcceptanceCertificateXmlForBuyer?boxId=" << StringHelper::CanonicalizeUrl(boxId)
				<< L"&sellerTitleMessageId=" << StringHelper::CanonicalizeUrl(sellerTitleMessageId)
				<< L"&sellerTitleAttachmentId=" << StringHelper::CanonicalizeUrl(sellerTitleAttachmentId);
	auto requestBody = ToProtoBytes(acceptanceCertificateBuyerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateAcceptanceCertificate552XmlForSeller(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552SellerTitleInfo& acceptanceCertificateSellerInfo, bool disableValidation)
{
    WppTraceDebugOut("GenerateAcceptanceCertificate552XmlForSeller...");
    auto requestBody = ToProtoBytes(acceptanceCertificateSellerInfo);
    auto connect = session_.Connect(api_url_.c_str(), api_port_);
    std::wstringstream queryString;
    queryString << L"/GenerateAcceptanceCertificate552XmlForSeller?documentVersion=rezru_05_01_01" << (disableValidation ? L"&disableValidation" : L"");
    auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
    SendRequest(request, requestBody);
    return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateAcceptanceCertificate552XmlForBuyer(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552BuyerTitleInfo& acceptanceCertificateBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId)
{
    WppTraceDebugOut("GenerateAcceptanceCertificate552XmlForBuyer...");
    std::wstringstream queryString;
    queryString << L"/GenerateAcceptanceCertificate552XmlForBuyer?boxId=" << StringHelper::CanonicalizeUrl(boxId)
                << L"&sellerTitleMessageId=" << StringHelper::CanonicalizeUrl(sellerTitleMessageId)
                << L"&sellerTitleAttachmentId=" << StringHelper::CanonicalizeUrl(sellerTitleAttachmentId)
                << L"&documentVersion=rezru_05_01_01";
    auto requestBody = ToProtoBytes(acceptanceCertificateBuyerInfo);
    auto connect = session_.Connect(api_url_.c_str(), api_port_);
    auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
    SendRequest(request, requestBody);
    return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateUniversalTransferDocumentXmlForSeller(const UniversalTransferDocumentSellerTitleInfo& utdSellerInfo, bool disableValidation)
{
	WppTraceDebugOut("GenerateUniversalTransferDocumentXmlForSeller...");
	auto requestBody = ToProtoBytes(utdSellerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateUniversalTransferDocumentXmlForSeller"
		<< (disableValidation ? L"?disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateUniversalCorrectionDocumentXmlForSeller(const UniversalCorrectionDocumentSellerTitleInfo& utdSellerInfo, bool disableValidation)
{
	WppTraceDebugOut("GenerateUniversalCorrectionDocumentXmlForSeller...");
	auto requestBody = ToProtoBytes(utdSellerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	std::wstringstream queryString;
	queryString << L"/GenerateUniversalTransferDocumentXmlForSeller"
		<< L"?correction"
		<< (disableValidation ? L"&disableValidation" : L"");
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

DiadocApi::WebFile DiadocApi::GenerateUniversalTransferDocumentXmlForBuyer(const UniversalTransferDocumentBuyerTitleInfo& utdBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId)
{
	WppTraceDebugOut("GenerateUniversalTransferDocumentXmlForBuyer...");
	std::wstringstream queryString;
	queryString << L"/GenerateUniversalTransferDocumentXmlForBuyer?boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&sellerTitleMessageId=" << StringHelper::CanonicalizeUrl(sellerTitleMessageId)
		<< L"&sellerTitleAttachmentId=" << StringHelper::CanonicalizeUrl(sellerTitleAttachmentId);
	auto requestBody = ToProtoBytes(utdBuyerInfo);
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(POST.c_str(), queryString.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	SendRequest(request, requestBody);
	return WebFile(request);
}

// WARN: [[deprecated]]
// WARN: Use overload with DocumentTitleType parameter
Signers::ExtendedSignerDetails DiadocApi::GetExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, bool forBuyer, bool forCorrection)
{
    Signers::DocumentTitleType documentTitleType = CreateUtdDocumentTitleType(forBuyer, forCorrection);
    return GetExtendedSignerDetails(token, boxId, thumbprint, documentTitleType);
}

Signers::ExtendedSignerDetails DiadocApi::GetExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, const Signers::DocumentTitleType& documentTitleType)
{
	WppTraceDebugOut("GetExtendedSignerDetails...");

	std::wstringstream queryString;
	queryString
		<< L"/V2/ExtendedSignerDetails?boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&thumbprint=" << StringHelper::CanonicalizeUrl(thumbprint)
		<< L"&documentTitleType=" << std::to_wstring(static_cast<int>(documentTitleType));

	return PerformHttpRequest<Signers::ExtendedSignerDetails>("GET", queryString.str());
}

// WARN: [[deprecated]]
// WARN: Use overload with DocumentTitleType parameter
Signers::ExtendedSignerDetails DiadocApi::PostExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, bool forBuyer, bool forCorrection, const Signers::ExtendedSignerDetailsToPost& signerDetails)
{
	Signers::DocumentTitleType documentTitleType = CreateUtdDocumentTitleType(forBuyer, forCorrection);
	return PostExtendedSignerDetails(token, boxId, thumbprint, documentTitleType, signerDetails);
}

Signers::ExtendedSignerDetails DiadocApi::PostExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, const Signers::DocumentTitleType& documentTitleType, const Signers::ExtendedSignerDetailsToPost& signerDetails)
{
	WppTraceDebugOut("PostExtendedSignerDetails...");

	std::wstringstream queryString;
	queryString
		<< L"/V2/ExtendedSignerDetails?boxId=" << StringHelper::CanonicalizeUrl(boxId)
		<< L"&thumbprint=" << StringHelper::CanonicalizeUrl(thumbprint)
		<< L"&documentTitleType=" << std::to_wstring(static_cast<int>(documentTitleType));

	return PerformHttpRequest<Signers::ExtendedSignerDetailsToPost, Signers::ExtendedSignerDetails>("POST", queryString.str(), signerDetails);
}

InvoiceInfo DiadocApi::ParseInvoiceXml(const Bytes_t& invoiceXmlContent)
{
	WppTraceDebugOut("ParseInvoiceXml...");
	return FromProtoBytes<InvoiceInfo>(PerformHttpRequest(L"/ParseInvoiceXml", invoiceXmlContent, L"POST"));
}

Torg12SellerTitleInfo DiadocApi::ParseTorg12SellerTitleXml(const Bytes_t& content)
{
	WppTraceDebugOut("ParseTorg12SellerTitleXml...");
	return FromProtoBytes<Torg12SellerTitleInfo>(PerformHttpRequest(L"/ParseTorg12SellerTitleXml", content, L"POST"));
}

TovTorgSellerTitleInfo DiadocApi::ParseTovTorg551SellerTitleXml(const Bytes_t& content)
{
	WppTraceDebugOut("ParseTovTorg551SellerTitleXml...");
	return FromProtoBytes<TovTorgSellerTitleInfo>(PerformHttpRequest(L"/ParseTorg12SellerTitleXml?documentVersion=tovtorg_05_01_02", content, L"POST"));
}

Torg12BuyerTitleInfo DiadocApi::ParseTorg12BuyerTitleXml(const Bytes_t& content)
{
	WppTraceDebugOut("ParseTorg12BuyerTitleXml...");
	return FromProtoBytes<Torg12BuyerTitleInfo>(PerformHttpRequest(L"/ParseTorg12BuyerTitleXml", content, L"POST"));
}

TovTorgBuyerTitleInfo DiadocApi::ParseTovTorg551BuyerTitleXml(const Bytes_t& content)
{
	WppTraceDebugOut("ParseTovTorg551BuyerTitleXml...");
	return FromProtoBytes<TovTorgBuyerTitleInfo>(PerformHttpRequest(L"/ParseTorg12BuyerTitleXml?documentVersion=tovtorg_05_01_02", content, L"POST"));
}

AcceptanceCertificateSellerTitleInfo DiadocApi::ParseAcceptanceCertificateSellerTitleXml(const Bytes_t& sellerTitleXmlContent)
{
	WppTraceDebugOut("ParseAcceptanceCertificateSellerTitleXml...");
	return FromProtoBytes<AcceptanceCertificateSellerTitleInfo>(PerformHttpRequest(L"/ParseAcceptanceCertificateSellerTitleXml", sellerTitleXmlContent, L"POST"));
}

AcceptanceCertificateBuyerTitleInfo DiadocApi::ParseAcceptanceCertificateBuyerTitleXml(const Bytes_t& buyerTitleXmlContent)
{
    WppTraceDebugOut("ParseAcceptanceCertificateBuyerTitleXml...");
    return FromProtoBytes<AcceptanceCertificateBuyerTitleInfo>(PerformHttpRequest(L"/ParseAcceptanceCertificateBuyerTitleXml", buyerTitleXmlContent, L"POST"));
}

AcceptanceCertificate552SellerTitleInfo DiadocApi::ParseAcceptanceCertificate552SellerTitleXml(const Bytes_t& sellerTitleXmlContent)
{
    WppTraceDebugOut("ParseAcceptanceCertificate552SellerTitleXml...");
    return FromProtoBytes<AcceptanceCertificate552SellerTitleInfo>(PerformHttpRequest(L"/ParseAcceptanceCertificate552SellerTitleXml?documentVersion=rezru_05_01_01", sellerTitleXmlContent, L"POST"));
}

AcceptanceCertificate552BuyerTitleInfo DiadocApi::ParseAcceptanceCertificate552BuyerTitleXml(const Bytes_t& buyerTitleXmlContent)
{
    WppTraceDebugOut("ParseAcceptanceCertificate552BuyerTitleXml...");
    return FromProtoBytes<AcceptanceCertificate552BuyerTitleInfo>(PerformHttpRequest(L"/ParseAcceptanceCertificate552BuyerTitleXml?documentVersion=rezru_05_01_01", buyerTitleXmlContent, L"POST"));
}

Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentSellerTitleInfo DiadocApi::ParseUniversalTransferDocumentSellerTitleXml(const Bytes_t& utdXmlContent)
{
	WppTraceDebugOut("ParseUniversalTransferDocumentSellerTitleXml...");
	return FromProtoBytes<UniversalTransferDocumentSellerTitleInfo>(PerformHttpRequest(L"/ParseUniversalTransferDocumentSellerTitleXml", utdXmlContent, L"POST"));
}

Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentBuyerTitleInfo DiadocApi::ParseUniversalTransferDocumentBuyerTitleXml(const Bytes_t& utdXmlContent)
{
	WppTraceDebugOut("ParseUniversalTransferDocumentBuyerTitleXml...");
	return FromProtoBytes<UniversalTransferDocumentBuyerTitleInfo>(PerformHttpRequest(L"/ParseUniversalTransferDocumentBuyerTitleXml", utdXmlContent, L"POST"));
}

Diadoc::Api::Proto::Invoicing::UniversalCorrectionDocumentSellerTitleInfo DiadocApi::ParseUniversalCorrectionDocumentSellerTitleXml(const Bytes_t& utdXmlContent)
{
	WppTraceDebugOut("ParseUniversalCorrectionDocumentSellerTitleXml...");
	return FromProtoBytes<UniversalCorrectionDocumentSellerTitleInfo>(PerformHttpRequest(L"/ParseUniversalCorrectionDocumentSellerTitleXml", utdXmlContent, L"POST"));
}

Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentBuyerTitleInfo DiadocApi::ParseUniversalCorrectionDocumentBuyerTitleXml(const Bytes_t& utdXmlContent)
{
	WppTraceDebugOut("ParseUniversalCorrectionDocumentBuyerTitleXml...");
	return FromProtoBytes<UniversalTransferDocumentBuyerTitleInfo>(PerformHttpRequest(L"/ParseUniversalCorrectionDocumentBuyerTitleXml", utdXmlContent, L"POST"));
}

RevocationRequestInfo DiadocApi::ParseRevocationRequestXml(const Bytes_t& xmlContent)
{
	WppTraceDebugOut("ParseRevocationRequestXml...");
	return FromProtoBytes<RevocationRequestInfo>(PerformHttpRequest(L"/ParseRevocationRequestXml", xmlContent, L"POST"));
}

SignatureRejectionInfo DiadocApi::ParseSignatureRejectionXml(const Bytes_t& xmlContent)
{
	WppTraceDebugOut("ParseSignatureRejectionXml...");
	return FromProtoBytes<SignatureRejectionInfo>(PerformHttpRequest(L"/ParseSignatureRejectionXml", xmlContent, L"POST"));
}

OrganizationList DiadocApi::GetOrganizationsByInnKpp(const std::wstring& inn, const std::wstring& kpp, bool includeRelations)
{
	WppTraceDebugOut("GetOrganizationsByInnKpp...");
	std::wstringstream buf;
	buf << L"/GetOrganizationsByInnKpp?inn=" << StringHelper::CanonicalizeUrl(inn);
	if (!kpp.empty())
		buf << L"&kpp=" << StringHelper::CanonicalizeUrl(kpp);
	if (includeRelations)
		buf << L"&includeRelations=" << StringHelper::CanonicalizeUrl(L"true");
	return FromProtoBytes<OrganizationList>(PerformHttpRequest(buf.str(), GET));
}

std::vector<Diadoc::Api::Proto::Organization> DiadocApi::GetOrganizationsByInnList(const GetOrganizationsByInnListRequest& request)
{
	WppTraceDebugOut("GetOrganizationsByInnList without myOrgId...");

	auto response = FromProtoBytes<GetOrganizationsByInnListResponse>(
		PerformHttpRequest(L"/GetOrganizationsByInnList", ToProtoBytes(request), POST));
	auto orgs = response.organizations();
	std::vector<Diadoc::Api::Proto::Organization> result;
	std::transform(orgs.begin(), orgs.end(), std::back_inserter(result), [&](const Diadoc::Api::Proto::OrganizationWithCounteragentStatus& o)
	{
		return o.organization();
	});
	return result;
}

std::vector<Diadoc::Api::Proto::OrganizationWithCounteragentStatus> DiadocApi::GetOrganizationsByInnList(const std::wstring& myOrgId, const GetOrganizationsByInnListRequest& request)
{
	WppTraceDebugOut("GetOrganizationsByInnList with myOrgId...");

	std::wstringstream buf;
	buf << L"/GetOrganizationsByInnList?myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId);
	auto response = FromProtoBytes<GetOrganizationsByInnListResponse>(PerformHttpRequest(buf.str(), ToProtoBytes(request), POST));
	auto orgs = response.organizations();
	std::vector<Diadoc::Api::Proto::OrganizationWithCounteragentStatus> result;
	std::copy(orgs.begin(), orgs.end(), std::back_inserter(result));
	return result;
}

Organization DiadocApi::GetOrganizationById(const std::wstring& orgId)
{
	return GetOrganization(orgId, L"orgId");
}

Organization DiadocApi::GetOrganizationByInn(const std::wstring& inn)
{
	return GetOrganization(inn, L"inn");
}

Organization DiadocApi::GetOrganizationByFnsParticipantId(const std::wstring& fnsParticipantId)
{
	return GetOrganization(fnsParticipantId, L"fnsParticipantId");
}

OrganizationList DiadocApi::GetMyOrganizations()
{
	return GetMyOrganizations(true);
}

OrganizationList DiadocApi::GetMyOrganizations(bool autoRegister)
{
	WppTraceDebugOut("GetMyOrganizations...");
	std::wstringstream buf;
	buf << L"/GetMyOrganizations";
	if (autoRegister == false)
		buf << "?autoRegister=" << StringHelper::CanonicalizeUrl(L"false");
	return FromProtoBytes<OrganizationList>(PerformHttpRequest(buf.str(), GET));
}

Diadoc::Api::Proto::User DiadocApi::GetMyUser()
{
	WppTraceDebugOut("GetMyUser...");
	return FromProtoBytes<Diadoc::Api::Proto::User>(PerformHttpRequest(L"/GetMyUser", GET));
}

OrganizationUserPermissions DiadocApi::GetMyPermissions(const std::wstring& orgId)
{
	WppTraceDebugOut("GetMyPermissions...");
	std::wstringstream buf;
	buf << L"/GetMyPermissions?orgId=" << StringHelper::CanonicalizeUrl(orgId);
	return FromProtoBytes<OrganizationUserPermissions>(PerformHttpRequest(buf.str(), GET));
}

Box DiadocApi::GetBox(const std::wstring& boxId)
{
	WppTraceDebugOut("GetBox...");
	std::wstringstream buf;
	buf << L"/GetBox?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	return FromProtoBytes<Box>(PerformHttpRequest(buf.str(), GET));
}

Department DiadocApi::GetDepartment(const std::wstring& orgId, const std::wstring& departmentId)
{
	WppTraceDebugOut("GetDepartment...");
	std::wstringstream buf;
	buf << L"/GetDepartment?orgId=" << StringHelper::CanonicalizeUrl(orgId)
		<< L"&departmentId=" << StringHelper::CanonicalizeUrl(departmentId);
	return FromProtoBytes<Department>(PerformHttpRequest(buf.str(), GET));
}

CounteragentList DiadocApi::GetCounteragents(const std::wstring& myOrgId, const std::wstring& counteragentStatus, const std::wstring& afterIndexKey)
{
	WppTraceDebugOut("V2/GetCounteragents...");
	std::wstringstream buf;
	buf << L"/V2/GetCounteragents?myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId);
	if (!counteragentStatus.empty())
		buf << L"&counteragentStatus=" << StringHelper::CanonicalizeUrl(counteragentStatus);
	if (!afterIndexKey.empty())
		buf << L"&afterIndexKey=" << StringHelper::CanonicalizeUrl(afterIndexKey);
	return FromProtoBytes<CounteragentList>(PerformHttpRequest(buf.str(), GET));
}

Diadoc::Api::Proto::AsyncMethodResult DiadocApi::AcquireCounteragent(const std::wstring& myOrgId, const Diadoc::Api::Proto::AcquireCounteragentRequest& request)
{
	return AcquireCounteragent(myOrgId, std::wstring(), request);
}

Diadoc::Api::Proto::AsyncMethodResult DiadocApi::AcquireCounteragent(const std::wstring& myOrgId, const std::wstring& myDepartmentId, const Diadoc::Api::Proto::AcquireCounteragentRequest& request)
{
	WppTraceDebugOut("AcquireCounteragent...");
	std::wstringstream buf;
	buf <<  L"myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId);
	if (!myDepartmentId.empty())
		buf << L"&myDepartmentId=" << StringHelper::CanonicalizeUrl(myDepartmentId);
	return PerformHttpRequest<AcquireCounteragentRequest, AsyncMethodResult>("/V2/AcquireCounteragent", buf.str(), request);
}

TaskResult<AcquireCounteragentResult> DiadocApi::AcquireCounteragentResult(const std::wstring& taskId)
{
	return PerformAsyncHttpRequest<Diadoc::Api::Proto::AcquireCounteragentResult>("AcquireCounteragentResult", L"taskId=" + StringHelper::CanonicalizeUrl(taskId), GET);
}

void DiadocApi::BreakWithCounteragent(const std::wstring& myOrgId, const std::wstring& counteragentOrgId, const std::wstring& comment)
{
	WppTraceDebugOut("BreakWithCounteragent...");
	std::wstringstream buf;
	buf << L"/BreakWithCounteragent?myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId) << L"&counteragentOrgId=" << StringHelper::CanonicalizeUrl(counteragentOrgId);
	if (!comment.empty())
		buf << L"&comment=" << StringHelper::CanonicalizeUrl(comment);
	PerformHttpRequest(buf.str(), POST);
}

Counteragent DiadocApi::GetCounteragent(const std::wstring& myOrgId, const std::wstring& counteragentOrgId)
{
	WppTraceDebugOut(L"V2/GetCounteragent...");
	std::wstringstream buf;
	buf << L"/V2/GetCounteragent?myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId) << L"&counteragentOrgId=" << StringHelper::CanonicalizeUrl(counteragentOrgId);
	return FromProtoBytes<Counteragent>(PerformHttpRequest(buf.str(), GET));
}

CounteragentCertificateList DiadocApi::GetCounteragentCertificates(const std::wstring& myOrgId, const std::wstring& counteragentOrgId)
{
	WppTraceDebugOut(L"GetCounteragentCertificates...");
	std::wstringstream buf;
	buf << L"/GetCounteragentCertificates?myOrgId=" << StringHelper::CanonicalizeUrl(myOrgId) << L"&counteragentOrgId=" << StringHelper::CanonicalizeUrl(counteragentOrgId);
	return FromProtoBytes<CounteragentCertificateList>(PerformHttpRequest(buf.str(), GET));
}

bool DiadocApi::CanSendInvoice(const std::wstring& boxId, const Bytes_t& certBytes)
{
	WppTraceDebugOut("CanSendInvoice...");
	std::wstringstream buf;
	buf << L"/CanSendInvoice?boxId=" << StringHelper::CanonicalizeUrl(boxId);	
	try
	{
		PerformHttpRequest(buf.str(), certBytes, POST);
		return true;
	}
	catch (HttpException e)
	{
		if (e.StatusCode == 403)
			return false;
		throw e;
	}
}

void DiadocApi::SendFnsRegistrationMessage(const std::wstring& boxId, const Bytes_t& certBytes)
{
	WppTraceDebugOut("SendFnsRegistrationMessage...");
	std::wstringstream buf;
	buf << L"/SendFnsRegistrationMessage?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	FnsRegistrationMessageInfo regMessageInfo;
	regMessageInfo.add_certificates(&certBytes[0], certBytes.size());
	PerformHttpRequest(buf.str(), ToProtoBytes(regMessageInfo), POST);
}

void DiadocApi::MoveDocuments(const Diadoc::Api::Proto::Documents::DocumentsMoveOperation& operation)
{
	WppTraceDebugOut("MoveDocuments...");
	auto requestBody = ToProtoBytes(operation);
	PerformHttpRequest(L"/MoveDocuments", requestBody, POST);
}

KeyValueStorageApiGetResponse DiadocApi::GetOrganizationStorageEntries(const std::wstring& orgId, const KeyValueStorageApiGetRequest& keys)
{
	WppTraceDebugOut("GetOrganizationStorageEntries...");
	std::wstringstream buf;
	buf << L"/KeyValueStorageGet?orgId=" << StringHelper::CanonicalizeUrl(orgId);
	auto requestBody = ToProtoBytes(keys);
	return FromProtoBytes<KeyValueStorageApiGetResponse>(PerformHttpRequest(buf.str(), requestBody, POST));
}

void DiadocApi::PutOrganizationStorageEntries(const std::wstring& orgId, const KeyValueStorageApiPutRequest& entries)
{
	WppTraceDebugOut("PutOrganizationStorageEntries...");
	std::wstringstream buf;
	buf << L"/KeyValueStoragePut?orgId=" << StringHelper::CanonicalizeUrl(orgId);
	auto requestBody = ToProtoBytes(entries);
	PerformHttpRequest(buf.str(), requestBody, POST);
}

GetDocflowBatchResponse DiadocApi::GetDocflows(const std::wstring& boxId, const GetDocflowBatchRequest& request)
{
	return PerformHttpRequestWithBoxId<GetDocflowBatchRequest, GetDocflowBatchResponse>("GetDocflows", boxId, request);
}

GetDocflowEventsResponse DiadocApi::GetDocflowEvents(const std::wstring& boxId, const GetDocflowEventsRequest& request)
{
	return PerformHttpRequestWithBoxId<GetDocflowEventsRequest, GetDocflowEventsResponse>("GetDocflowEvents", boxId, request);
}

SignatureInfo DiadocApi::GetSignatureInfo(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId)
{
	WppTraceDebugOut(L"GetSignatureInfo...");
	std::wstringstream buf;
	buf << L"/GetSignatureInfo?boxId=" << StringHelper::CanonicalizeUrl(boxId) << L"&messageId=" << StringHelper::CanonicalizeUrl(messageId) << L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);
	return FromProtoBytes<SignatureInfo>(PerformHttpRequest(buf.str(), GET));
}

void DiadocApi::ForwardDocument(const std::wstring& boxId, const ForwardDocumentRequest& request)
{
	WppTraceDebugOut("ForwardDocument...");
	std::wstringstream buf;
	buf << L"/ForwardDocument?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	PerformHttpRequest(buf.str(), ToProtoBytes(request), POST);
}

GetForwardedDocumentsResponse DiadocApi::GetForwardedDocuments(const std::wstring& boxId, const GetForwardedDocumentsRequest& request)
{
	return PerformHttpRequestWithBoxId<GetForwardedDocumentsRequest, GetForwardedDocumentsResponse>("GetForwardedDocuments", boxId, request);
}

GetForwardedDocumentEventsResponse DiadocApi::GetForwardedDocumentEvents(const std::wstring& boxId, const GetForwardedDocumentEventsRequest& request)
{
	return PerformHttpRequestWithBoxId<GetForwardedDocumentEventsRequest, GetForwardedDocumentEventsResponse>("GetForwardedDocumentEvents", boxId, request);
}

template<class TRequest, class TResponse>
TResponse DiadocApi::PerformHttpRequestWithBoxId(const std::string& action, const std::wstring& boxId, const TRequest& request)
{
	WppTraceDebugOut((action + "...").c_str());
	return PerformHttpRequest<TRequest, TResponse>(action, L"boxId=" + StringHelper::CanonicalizeUrl(boxId), request);
}

template<class TRequest, class TResponse>
TResponse DiadocApi::PerformHttpRequest(const std::string& action, const std::wstring& queryString, const TRequest& request)
{
	WppTraceDebugOut((action + "...").c_str());
	std::wstringstream buf;
	buf << L"/" << StringHelper::Utf8ToUtf16(action) << L"?" << queryString;
	auto requestBody = ToProtoBytes(request);
	auto response = PerformHttpRequest(buf.str(), requestBody, POST);
	return FromProtoBytes<TResponse>(response);
}

template<class TResponse>
TResponse DiadocApi::PerformHttpRequest(const std::string& action, const std::wstring& queryString)
{
	WppTraceDebugOut((action + "...").c_str());
	std::wstringstream buf;
	buf << L"/" << StringHelper::Utf8ToUtf16(action) << L"?" << queryString;
	auto response = PerformHttpRequest(buf.str(), Bytes_t(), POST);
	return FromProtoBytes<TResponse>(response);
}

template <class TResponse>
TaskResult<TResponse> DiadocApi::PerformAsyncHttpRequest(const std::string& action, const std::wstring& queryString, const std::wstring& method)
{
	WppTraceDebugOut((action + "...").c_str());
	std::wstringstream buf;
	buf << L"/" << StringHelper::Utf8ToUtf16(action) << L"?" << queryString;
	auto bytesResult = PerformAsyncHttpRequest(buf.str(), Bytes_t(), method);
	return TaskResult<TResponse>::ConvertResult(bytesResult, [](const Bytes_t& bytes)
	{
		return FromProtoBytes<TResponse>(bytes);
	});
}

DiadocApi::Bytes_t DiadocApi::GetForwardedEntityContent(const std::wstring& boxId, const ForwardedDocumentId& forwardedDocumentId, const std::wstring& entityId)
{
	WppTraceDebugOut(L"GetForwardedEntityContent...");
	std::wstringstream buf;
	buf << L"/GetForwardedEntityContent?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	buf << L"&fromBoxId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.fromboxid());
	buf << L"&messageId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.documentid().messageid());
	buf << L"&documentId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.documentid().entityid());
	buf << L"&forwardEventId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.forwardeventid());
	buf << L"&entityId=" << StringHelper::CanonicalizeUrl(entityId);
	return PerformHttpRequest(buf.str(), GET);
}

TaskResult<DocumentProtocol> DiadocApi::GenerateForwardedDocumentProtocol(const std::wstring& boxId, const ForwardedDocumentId& forwardedDocumentId)
{
	std::wstringstream buf;
	buf << L"?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	buf << L"&fromBoxId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.fromboxid());
	buf << L"&messageId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.documentid().messageid());
	buf << L"&documentId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.documentid().entityid());
	buf << L"&forwardEventId=" << StringHelper::Utf8ToUtf16(forwardedDocumentId.forwardeventid());
	return PerformAsyncHttpRequest<DocumentProtocol>("GenerateForwardedDocumentProtocol", buf.str(), GET);
}

AsyncMethodResult DiadocApi::CloudSign(const CloudSignRequest& request, const std::wstring& certificateThumbprint)
{
	return PerformHttpRequest<CloudSignRequest, AsyncMethodResult>("CloudSign", L"certificateThumbprint=" + StringHelper::CanonicalizeUrl(certificateThumbprint), request);
}

TaskResult<CloudSignResult> DiadocApi::CloudSignResult(const std::wstring& taskId)
{
	return PerformAsyncHttpRequest<Diadoc::Api::Proto::CloudSignResult>("CloudSignResult", L"taskId=" + StringHelper::CanonicalizeUrl(taskId), GET);
}

AsyncMethodResult DiadocApi::CloudSignConfirm(const std::wstring& token, const std::wstring& confirmationCode)
{
	return PerformHttpRequest<AsyncMethodResult>("CloudSignConfirm", L"token=" + StringHelper::CanonicalizeUrl(token) + L"&confirmationCode=" + StringHelper::CanonicalizeUrl(confirmationCode));
}

TaskResult<CloudSignConfirmResult> DiadocApi::CloudSignConfirmResult(const std::wstring& taskId)
{
	return PerformAsyncHttpRequest<Diadoc::Api::Proto::CloudSignConfirmResult>("CloudSignConfirmResult", L"taskId=" + StringHelper::CanonicalizeUrl(taskId), GET);
}

AsyncMethodResult DiadocApi::AutoSignReceipts(const std::wstring& boxId, const std::wstring& certificateThumbprint, const std::wstring& batchKey)
{
	std::wstringstream params;
	params << "boxId=" << StringHelper::CanonicalizeUrl(boxId);
	if (!certificateThumbprint.empty())
		params << "&certificateThumbprint=" << StringHelper::CanonicalizeUrl(certificateThumbprint);
	if (!batchKey.empty())
		params << "&batchKey=" << StringHelper::CanonicalizeUrl(batchKey);
	return PerformHttpRequest<AsyncMethodResult>("AutoSignReceipts", params.str());
}

TaskResult<AutosignReceiptsResult> DiadocApi::WaitAutosignReceiptsResult(const std::wstring &taskId)
{
	return PerformAsyncHttpRequest<Diadoc::Api::Proto::AutosignReceiptsResult>("AutosignReceiptsResult", L"taskId=" + StringHelper::CanonicalizeUrl(taskId), GET);
}

DocumentList DiadocApi::GetDocumentsByMessageId(const std::wstring& boxId, const std::wstring& messageId)
{
	auto queryString = L"/GetDocumentsByMessageId?boxId=" + StringHelper::CanonicalizeUrl(boxId)
		+ L"&messageId=" + StringHelper::CanonicalizeUrl(messageId);
	auto bytes = PerformHttpRequest(queryString, GET);
	return FromProtoBytes<DocumentList>(bytes);
}

GetDocumentTypesResponse DiadocApi::GetDocumentTypes(const std::wstring& boxId)
{
	WppTraceDebugOut("GetDocumentTypes...");
	std::wstringstream buf;
	buf << L"/GetDocumentTypes?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	return FromProtoBytes<GetDocumentTypesResponse>(PerformHttpRequest(buf.str(), GET));
}

DetectDocumentTypesResponse DiadocApi::DetectDocumentTypes(const std::wstring& boxId, const std::wstring& nameOnShelf)
{
    WppTraceDebugOut("DetectDocumentTypes...");
    auto queryString = L"/DetectDocumentTypes?boxId=" + StringHelper::CanonicalizeUrl(boxId)
                       + L"&nameOnShelf=" + StringHelper::CanonicalizeUrl(nameOnShelf);
    return FromProtoBytes<DetectDocumentTypesResponse>(PerformHttpRequest(queryString, GET));
}

DetectDocumentTypesResponse DiadocApi::DetectDocumentTypes(const std::wstring& boxId, const Bytes_t& content)
{
	WppTraceDebugOut("DetectDocumentTypes...");
	std::wstringstream buf;
	buf << L"/DetectDocumentTypes?boxId=" << StringHelper::CanonicalizeUrl(boxId);
	return FromProtoBytes<DetectDocumentTypesResponse>(PerformHttpRequest(buf.str(), content, POST));
}

DiadocApi::WebFile DiadocApi::GetContent(const std::wstring& typeNamedId, const std::wstring& function, const std::wstring& version, int titleIndex)
{
	WppTraceDebugOut("GetContent...");
	std::wstringstream buf;
	buf << L"/GetContent?typeNamedId=" << StringHelper::CanonicalizeUrl(typeNamedId);
	buf << L"&function=" << StringHelper::CanonicalizeUrl(function);
	buf << L"&version=" << StringHelper::CanonicalizeUrl(version);
	buf << L"&titleIndex=" << titleIndex;
	auto connect = session_.Connect(api_url_.c_str(), api_port_);
	auto request = connect.OpenRequest(GET.c_str(), buf.str().c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, connection_flags_);
	Bytes_t requestBody;
	SendRequest(request, requestBody);
	return WebFile(request);
}