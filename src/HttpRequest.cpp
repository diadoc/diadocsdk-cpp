#include "StdAfx.h"
#include "HttpRequest.h"
#include "ApiException.h"
#include "StringHelper.h"

HttpRequest::HttpRequest(IN HINTERNET hConnect, IN LPCWSTR pwszVerb, IN LPCWSTR pwszObjectName, IN LPCWSTR pwszVersion, IN LPCWSTR pwszReferrer OPTIONAL,
	IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL, IN DWORD dwFlags)
	: _handle(WinHttpOpenRequest(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags))
{
	if (_handle == NULL) throw WinHttpException("WinHttpOpenRequest error", GetLastError());
}

HttpRequest::~HttpRequest(void)
{
	if (_handle != NULL)
		WinHttpCloseHandle(_handle);
}

HttpRequest::HttpRequest(HttpRequest&& orig)
{
	_handle = std::move(orig._handle);
	orig._handle = NULL;
}

HttpRequest& HttpRequest::operator= (HttpRequest&& right)
{
	_handle = std::move(right._handle);
	right._handle = NULL;
	return *this;
}

void HttpRequest::SetCredentials(IN DWORD AuthTargets, IN DWORD AuthScheme, IN LPCWSTR pwszUserName, IN LPCWSTR pwszPassword, IN LPVOID pAuthParams) const
{
	if (!WinHttpSetCredentials(_handle, AuthTargets, AuthScheme, pwszUserName, pwszPassword, pAuthParams))
		throw WinHttpException("WinHttpSetCredentials error", GetLastError());
}

void HttpRequest::Send(__in_ecount_opt(dwHeadersLength) LPCWSTR lpszHeaders, IN DWORD dwHeadersLength, __in_bcount_opt(dwOptionalLength) LPVOID lpOptional,
	IN DWORD dwOptionalLength, IN DWORD dwTotalLength, IN DWORD_PTR dwContext) const
{
	WppTraceDebugOut("Calling WinHttpSendRequest:");
	WppTraceDebugOut(L"\tHeaders (%i): %s",dwHeadersLength,lpszHeaders);
	WppTraceDebugOut(L"\tdwOptionalLength: %i",dwOptionalLength);
	WppTraceDebugOut(L"\tdwTotalLength: %i",dwTotalLength);
	if (!WinHttpSendRequest(_handle, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext))
		throw WinHttpException("WinHttpSendRequest error", GetLastError());
}

void HttpRequest::WriteData(__in_bcount_opt(dwNumberOfBytesToWrite) LPCVOID lpBuffer, IN DWORD dwNumberOfBytesToWrite) const
{
	DWORD numberOfBytesWritten;
	if (!WinHttpWriteData(_handle, lpBuffer, dwNumberOfBytesToWrite, &numberOfBytesWritten) || (numberOfBytesWritten != dwNumberOfBytesToWrite))
		throw WinHttpException("WinHttpWriteData error", GetLastError());
}

void HttpRequest::ReceiveResponse(IN LPVOID lpReserved) const
{
	if (!WinHttpReceiveResponse(_handle, lpReserved))
		throw WinHttpException("WinHttpReceiveResponse error", GetLastError());
}

std::wstring HttpRequest::QueryHeadersString(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL) const
{
	auto bytes = QueryHeaders(dwInfoLevel, pwszName, lpdwIndex);
	std::wstring utf16Str(reinterpret_cast<wchar_t*>(&bytes[0]), bytes.size()/sizeof(wchar_t));
	return utf16Str;
}

HttpRequest::Bytes_t HttpRequest::QueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL) const
{
	DWORD dwBufferLength = 0;
	if (!TryQueryHeaders(dwInfoLevel, pwszName, NULL, &dwBufferLength, lpdwIndex))
	{
		auto lastError = GetLastError();
		if (lastError != ERROR_INSUFFICIENT_BUFFER)
			throw WinHttpException("WinHttpQueryHeaders error", GetLastError());
	}
	Bytes_t buf;
	buf.resize(dwBufferLength);
	QueryHeaders(dwInfoLevel, pwszName, &buf[0], &dwBufferLength, lpdwIndex);
	buf.resize(dwBufferLength);
	return buf;
}

bool HttpRequest::TryQueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL, Bytes_t* bytes) const
{
	DWORD dwBufferLength = 0;
	if (!TryQueryHeaders(dwInfoLevel, pwszName, NULL, &dwBufferLength, lpdwIndex))
		return false;
	Bytes_t& buf = *bytes;
	buf.resize(dwBufferLength);
	return TryQueryHeaders(dwInfoLevel, pwszName, &buf[0], &dwBufferLength, lpdwIndex);
}

void HttpRequest::QueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL,
	__out_bcount_part_opt(*lpdwBufferLength, *lpdwBufferLength) __out_data_source(NETWORK) LPVOID lpBuffer,
	IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex OPTIONAL) const
{
	if (!TryQueryHeaders(dwInfoLevel, pwszName, lpBuffer, lpdwBufferLength, lpdwIndex))
		throw WinHttpException("WinHttpQueryHeaders error", GetLastError());
}

bool HttpRequest::TryQueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL,
	__out_bcount_part_opt(*lpdwBufferLength, *lpdwBufferLength) __out_data_source(NETWORK) LPVOID lpBuffer,
	IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex OPTIONAL) const
{
	return WinHttpQueryHeaders(_handle, dwInfoLevel, pwszName, lpBuffer, lpdwBufferLength, lpdwIndex);
}

DWORD HttpRequest::GetStatusCode() const
{
	DWORD statusCode;
	DWORD dwBufferLength = sizeof(statusCode);
	QueryHeaders(WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &dwBufferLength, NULL);
	return statusCode;
}

bool HttpRequest::TryGetRetryAfter(int* retryAfter) const
{
	DWORD dwBufferLength = 0;
	TryQueryHeaders(WINHTTP_QUERY_RETRY_AFTER, WINHTTP_HEADER_NAME_BY_INDEX, NULL, &dwBufferLength, NULL);
	if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) return false;
	std::vector<wchar_t> retryAfterBuf;
	retryAfterBuf.resize(dwBufferLength / sizeof(wchar_t));
	auto status = TryQueryHeaders(WINHTTP_QUERY_RETRY_AFTER, WINHTTP_HEADER_NAME_BY_INDEX, &retryAfterBuf[0], &dwBufferLength, NULL);
	if (!status) return false;
	std::wstring retryAfterStr(&retryAfterBuf[0]);
	*retryAfter = wcstol(retryAfterStr.c_str(), NULL, 0);
	return true;
}

std::wstring HttpRequest::GetContentType() const
{
	return QueryHeadersString(WINHTTP_QUERY_CONTENT_TYPE, WINHTTP_HEADER_NAME_BY_INDEX, NULL);
}

std::wstring HttpRequest::DebugQueryAllHeaders() const
{
	return QueryHeadersString(WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, NULL);
}

HttpRequest::ContentDisposition HttpRequest::GetContentDisposition() const
{
	return ContentDisposition(QueryHeadersString(WINHTTP_QUERY_CONTENT_DISPOSITION, WINHTTP_HEADER_NAME_BY_INDEX, NULL));
}

HttpRequest::ContentDisposition::ContentDisposition(const std::wstring& headerStr)
{
	auto headerParts = StringHelper::Split(headerStr, L';');
	dispositionType = headerParts[0];
	for (size_t i = 1; i < headerParts.size(); ++i)
	{
		ParseParameter(headerParts[i]);
	}
}

void HttpRequest::ContentDisposition::ParseParameter(const std::wstring& paramStr)
{
	auto equalPos = paramStr.find_first_of(L'=');
	if (equalPos == std::wstring::npos) throw std::runtime_error("Неправильный формат заголовка Content-Disposition");
	auto paramName = StringHelper::Trim(paramStr.substr(0, equalPos), L' ');
	auto paramValue = StringHelper::Trim(paramStr.substr(equalPos + 1), L'\"');
	dispositionParams[paramName] = paramValue;
}

HttpRequest::ContentDisposition::ContentDisposition(ContentDisposition&& orig)
{
	dispositionType = std::move(orig.dispositionType);
	dispositionParams = std::move(orig.dispositionParams);
}

HttpRequest::ContentDisposition& HttpRequest::ContentDisposition::operator=(ContentDisposition&& right)
{
	dispositionType = std::move(right.dispositionType);
	dispositionParams = std::move(right.dispositionParams);
	return *this;
}

const std::wstring HttpRequest::ContentDisposition::FileNameParam(L"filename");
std::wstring HttpRequest::ContentDisposition::GetFileName() const
{
	return dispositionParams.at(FileNameParam);
}

HttpRequest::ContentDisposition::~ContentDisposition()
{
}

DWORD HttpRequest::QueryDataAvailable() const
{
	DWORD numberOfBytes;
	if (!WinHttpQueryDataAvailable(_handle, &numberOfBytes))
		throw WinHttpException("WinHttpQueryDataAvailable error", GetLastError());
	return numberOfBytes;
}

void HttpRequest::ReadData(__out_bcount_part(dwNumberOfBytesToRead, *lpdwNumberOfBytesRead) __out_data_source(NETWORK) LPVOID lpBuffer, IN DWORD dwNumberOfBytesToRead) const
{
	DWORD bytesRead;
	if (!WinHttpReadData(_handle, lpBuffer, dwNumberOfBytesToRead, &bytesRead) || (bytesRead != dwNumberOfBytesToRead))
		throw WinHttpException("WinHttpReadData error", GetLastError());
}

HttpRequest::Bytes_t HttpRequest::ReadAllResponse() const
{
	Bytes_t result;
	while (true)
	{
		auto size = QueryDataAvailable();
		if (size == 0) break;
		Bytes_t localBuffer;
		localBuffer.resize(size);
		ReadData(&localBuffer[0], size);
		result.insert(result.end(), localBuffer.begin(), localBuffer.end());
	}
	return result;
}

void HttpRequest::QueryAuthSchemes(OUT LPDWORD lpdwSupportedSchemes, OUT LPDWORD lpdwFirstScheme, OUT LPDWORD pdwAuthTarget) const
{
	if (!WinHttpQueryAuthSchemes(_handle, lpdwSupportedSchemes, lpdwFirstScheme, pdwAuthTarget))
		throw WinHttpException("WinHttpQueryAuthSchemes error", GetLastError());
}

BOOL HttpRequest::QueryOption(__in DWORD dwOption, __out LPVOID lpBuffer, __inout LPDWORD lpdwBufferLength)
{
	return WinHttpQueryOption(_handle, dwOption, lpBuffer, lpdwBufferLength);
}

HttpRequest::Bytes_t HttpRequest::QueryOption(__in DWORD dwOption)
{
	DWORD dwBufferLength = 0;
	QueryOption(dwOption, NULL, &dwBufferLength);
	Bytes_t result;
	result.resize(dwBufferLength);
	if (!QueryOption(dwOption, &result[0], &dwBufferLength))
		throw ApiException("WinHttpQueryOption error", GetLastError());
	return result;
}