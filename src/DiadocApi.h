#pragma once

#include <Windows.h>
#include <sstream>

#include "protos\Events\DiadocMessage-GetApi.pb.h"
#include "protos\Events\DiadocMessage-PostApi.pb.h"
#include "protos\Recognition\Recognition.pb.h"
#include "protos\Documents\Document.pb.h"
#include "protos\Documents\DocumentList.pb.h"
#include "protos\Documents\DocumentsMoveOperation.pb.h"
#include "protos\Documents\DocumentProtocol.pb.h"
#include "protos\Documents\Types\DocumentTypeDescription.pb.h"
#include "protos\Docflow\DocflowApi.pb.h"
#include "protos\Forwarding\ForwardingApi.pb.h"
#include "protos\Invoicing\InvoiceCorrectionRequestInfo.pb.h"
#include "protos\Invoicing\RevocationRequestInfo.pb.h"
#include "protos\Invoicing\SignatureRejectionInfo.pb.h"
#include "protos\Invoicing\InvoiceInfo.pb.h"
#include "protos\Invoicing\Torg12Info.pb.h"
#include "protos\Invoicing\TovTorgInfo.pb.h"
#include "protos\Invoicing\AcceptanceCertificateInfo.pb.h"
#include "protos\Invoicing\AcceptanceCertificate552Info.pb.h"
#include "protos\Invoicing\UniversalTransferDocumentInfo.pb.h"
#include "protos\KeyValueStorage\KeyValueStorage.pb.h"
#include "protos\Counteragent.pb.h"
#include "protos\Organization.pb.h"
#include "protos\User.pb.h"
#include "protos\BoxList.pb.h"
#include "protos\OrganizationUserPermissions.pb.h"
#include "protos\OrganizationUser.pb.h"
#include "protos\SignatureInfo.pb.h"
#include "protos\GetOrganizationsByInnList.pb.h"
#include "protos\AsyncMethodResult.pb.h"
#include "protos\CloudSign.pb.h"
#include "protos\AcquireCounteragent.pb.h"
#include "DocumentFilter.h"
#include "HttpSession.h"
#include "TaskResult.h"

class DiadocApi
{
public:
	typedef std::vector<char> Bytes_t;

	DiadocApi(const std::wstring& serverUrl, const std::wstring& apiClientId, const std::wstring& proxyUrl = std::wstring(), bool useDefaultProxySettings = true);
	virtual ~DiadocApi(void);

	std::wstring GetAuthToken();
	void SetProxyCredentials(const std::wstring& username, const std::wstring& password);
	std::wstring GetDocumentPathUrl(std::wstring boxId, std::wstring messageId, std::wstring entityId);

	void Authenticate(const Bytes_t& certBytes, bool useLocalMachineStorage = false);
	void VerifyThatUserHasAccessToAnyBox(const Bytes_t& certBytes);
	void Authenticate(const std::wstring& login, const std::wstring& password);

	Diadoc::Api::Proto::BoxList GetBoxes();
	Diadoc::Api::Proto::BoxList GetBoxesByInnKpp(const std::wstring& inn, const std::wstring& kpp);
	Diadoc::Api::Proto::BoxInfo GetBoxInfo(const std::wstring& boxId);
	
	Diadoc::Api::Proto::Events::BoxEventList GetNewEvents(const std::wstring& boxId, const std::wstring& afterMessageId = std::wstring());
	Diadoc::Api::Proto::Events::BoxEvent GetEvent(const std::wstring& boxId, const std::wstring& eventId);

	Diadoc::Api::Proto::Events::Message PostDiadocMessage(const Diadoc::Api::Proto::Events::MessageToPost& msg, const std::wstring& operationId = std::wstring());
	Diadoc::Api::Proto::Events::MessagePatch PostMessagePatch(const Diadoc::Api::Proto::Events::MessagePatchToPost& patch, const std::wstring& operationId = std::wstring());
	Diadoc::Api::Proto::Events::PrepareDocumentsToSignResponse PrepareDocumentsToSign(const Diadoc::Api::Proto::Events::PrepareDocumentsToSignRequest& request);
	Diadoc::Api::Proto::Events::Message SendDraft(const Diadoc::Api::Proto::Events::DraftToSend& request, const std::wstring& operationId = std::wstring());

	void RecycleDraft(const std::wstring& boxId, const std::wstring& draftId);

	void Delete(const std::wstring &boxId, const std::wstring &messageId, const std::wstring &documentId = std::wstring());

	Bytes_t GetEntityContent(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId);
	Diadoc::Api::Proto::Events::Message GetDiadocMessage(const std::wstring& boxId, const std::wstring& messageId, bool withOriginalSignature = false, bool injectEntityContent = false);
	Diadoc::Api::Proto::Events::Message GetDiadocMessage(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId, bool withOriginalSignature = false, bool injectEntityContent = false);

	Diadoc::Api::Proto::Invoicing::InvoiceCorrectionRequestInfo GetInvoiceCorrectionRequestInfo(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId);
	Diadoc::Api::Proto::Documents::DocumentList GetDocuments(const std::wstring& boxId, const std::wstring& filterCategory, const std::wstring& counteragentBoxId, __int64* timestampFrom,
		__int64* timestampTo, const std::wstring& fromDocumentDate, const std::wstring& toDocumentDate, const std::wstring& departmentId, bool excludeSubdepartments, const std::string& afterIndexKey);
	Diadoc::Api::Proto::Documents::DocumentList GetDocuments(const DocumentFilter& documentFilter);
	Diadoc::Api::Proto::Documents::Document GetDocument(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId);
	
	std::wstring Recognize(const std::wstring& fileName, const Bytes_t& fileContent);
	Diadoc::Api::Proto::Recognition::Recognized GetRecognized(const std::wstring& recognitionId);

	class PrintFormResult
	{
	public:
		PrintFormResult(int replyAfter);
		PrintFormResult(const std::wstring& contentType, const std::wstring& fileName, const Bytes_t& bytes);

		// move
		PrintFormResult(PrintFormResult&& orig);
		PrintFormResult& operator=(PrintFormResult&& right);

		~PrintFormResult();

		int GetRetryAfter() const { return RetryAfter; }
		bool GetHasContent() const { return HasContent; }
		std::wstring GetContentType() const { return ContentType; }
		std::wstring GetFileName() const { return FileName; }
		Bytes_t GetBytes() const { return Bytes; }

	private:
		int RetryAfter;
		bool HasContent;

		// content
		std::wstring ContentType;
		std::wstring FileName;
		Bytes_t Bytes;
	};

	PrintFormResult GeneratePrintForm(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& documentId);

	TaskResult<Diadoc::Api::Proto::Documents::DocumentProtocol> GenerateDocumentProtocol(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& documentId);

	class WebFile
	{
	public:
		WebFile(const HttpRequest& request);
		WebFile(WebFile&& orig);
		WebFile& operator=(WebFile&& right);
		~WebFile();
		std::wstring GetFileName() const { return FileName; }
		Bytes_t GetContent() const { return Content; }

	private:
		std::wstring FileName;
		Bytes_t Content;
	};

	WebFile GenerateDocumentReceiptXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::Signer);

	WebFile GenerateInvoiceDocumentReceiptXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::Signer);
	WebFile GenerateInvoiceCorrectionRequestXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::InvoiceCorrectionRequestInfo& correctionInfo);
	
	WebFile GenerateRevocationRequestXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::RevocationRequestInfo& revocationRequestInfo);
	WebFile GenerateSignatureRejectionXml(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& attachmentId, const Diadoc::Api::Proto::Invoicing::SignatureRejectionInfo& signatureRejectionInfo);

	WebFile GenerateInvoiceXml(const Diadoc::Api::Proto::Invoicing::InvoiceInfo& invoiceInfo, bool disableValidation = false);
	WebFile GenerateInvoiceRevisionXml(const Diadoc::Api::Proto::Invoicing::InvoiceInfo& invoiceRevisionInfo, bool disableValidation = false);
	WebFile GenerateInvoiceCorrectionXml(const Diadoc::Api::Proto::Invoicing::InvoiceCorrectionInfo& invoiceCorrectionInfo, bool disableValidation = false);
	WebFile GenerateInvoiceCorrectionRevisionXml(const Diadoc::Api::Proto::Invoicing::InvoiceCorrectionInfo& invoiceCorrectionRevisionInfo, bool disableValidation = false);

	WebFile GenerateTorg12XmlForSeller(const Diadoc::Api::Proto::Invoicing::Torg12SellerTitleInfo& torg12SellerInfo, bool disableValidation = false);
	WebFile GenerateTorg12XmlForBuyer(const Diadoc::Api::Proto::Invoicing::Torg12BuyerTitleInfo& torg12BuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId);
	WebFile GenerateTovTorg551XmlForSeller(const Diadoc::Api::Proto::Invoicing::TovTorgSellerTitleInfo& tovTorgSellerInfo, bool disableValidation = false);
	WebFile GenerateTovTorg551XmlForBuyer(const Diadoc::Api::Proto::Invoicing::TovTorgBuyerTitleInfo& tovTorgBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId);

	WebFile GenerateAcceptanceCertificateXmlForSeller(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificateSellerTitleInfo& acceptanceCertificateSellerInfo, bool disableValidation = false);
	WebFile GenerateAcceptanceCertificateXmlForBuyer(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificateBuyerTitleInfo& acceptanceCertificateBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId);
	WebFile GenerateAcceptanceCertificate552XmlForSeller(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552SellerTitleInfo& acceptanceCertificateSellerInfo, bool disableValidation = false);
	WebFile GenerateAcceptanceCertificate552XmlForBuyer(const Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552BuyerTitleInfo& acceptanceCertificateBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId);

	WebFile GenerateUniversalTransferDocumentXmlForSeller(const Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentSellerTitleInfo& utdSellerInfo, bool disableValidation = false);
	WebFile GenerateUniversalCorrectionDocumentXmlForSeller(const Diadoc::Api::Proto::Invoicing::UniversalCorrectionDocumentSellerTitleInfo& utdSellerInfo, bool disableValidation = false);
	WebFile GenerateUniversalTransferDocumentXmlForBuyer(const Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentBuyerTitleInfo& utdBuyerInfo, const std::wstring& boxId, const std::wstring& sellerTitleMessageId, const std::wstring& sellerTitleAttachmentId);

	// WARN: [[deprecated]]
	// WARN: Use overload with DocumentTitleType parameter
	Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetails GetExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, bool forBuyer, bool forCorrection);
	Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetails GetExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, const Diadoc::Api::Proto::Invoicing::Signers::DocumentTitleType &documentTitleType);

	// WARN: [[deprecated]]
	// WARN: Use overload with DocumentTitleType parameter
	Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetails PostExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, bool forBuyer, bool forCorrection, const Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetailsToPost &signerDetails);
	Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetails PostExtendedSignerDetails(const std::wstring& token, const std::wstring& boxId, const std::wstring& thumbprint, const Diadoc::Api::Proto::Invoicing::Signers::DocumentTitleType &documentTitleType, const Diadoc::Api::Proto::Invoicing::Signers::ExtendedSignerDetailsToPost &signerDetails);

	Diadoc::Api::Proto::Invoicing::InvoiceInfo ParseInvoiceXml(const Bytes_t& invoiceXmlContent);
	Diadoc::Api::Proto::Invoicing::Torg12SellerTitleInfo ParseTorg12SellerTitleXml(const Bytes_t& content);
	Diadoc::Api::Proto::Invoicing::TovTorgSellerTitleInfo ParseTovTorg551SellerTitleXml(const Bytes_t& content);
	Diadoc::Api::Proto::Invoicing::Torg12BuyerTitleInfo ParseTorg12BuyerTitleXml(const Bytes_t& content);
	Diadoc::Api::Proto::Invoicing::TovTorgBuyerTitleInfo ParseTovTorg551BuyerTitleXml(const Bytes_t& content);
	Diadoc::Api::Proto::Invoicing::AcceptanceCertificateSellerTitleInfo ParseAcceptanceCertificateSellerTitleXml(const Bytes_t& sellerTitleXmlContent);
	Diadoc::Api::Proto::Invoicing::AcceptanceCertificateBuyerTitleInfo ParseAcceptanceCertificateBuyerTitleXml(const Bytes_t& buyerTitleXmlContent);
	Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552SellerTitleInfo ParseAcceptanceCertificate552SellerTitleXml(const Bytes_t& sellerTitleXmlContent);
	Diadoc::Api::Proto::Invoicing::AcceptanceCertificate552BuyerTitleInfo ParseAcceptanceCertificate552BuyerTitleXml(const Bytes_t& buyerTitleXmlContent);
	Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentSellerTitleInfo ParseUniversalTransferDocumentSellerTitleXml(const Bytes_t& utdXmlContent);
	Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentBuyerTitleInfo ParseUniversalTransferDocumentBuyerTitleXml(const Bytes_t& utdXmlContent);
	Diadoc::Api::Proto::Invoicing::UniversalCorrectionDocumentSellerTitleInfo ParseUniversalCorrectionDocumentSellerTitleXml(const Bytes_t& utdXmlContent);
	Diadoc::Api::Proto::Invoicing::UniversalTransferDocumentBuyerTitleInfo ParseUniversalCorrectionDocumentBuyerTitleXml(const Bytes_t& utdXmlContent);

	Diadoc::Api::Proto::Invoicing::RevocationRequestInfo ParseRevocationRequestXml(const Bytes_t& xmlContent);
	Diadoc::Api::Proto::Invoicing::SignatureRejectionInfo ParseSignatureRejectionXml(const Bytes_t& xmlContent);

	Diadoc::Api::Proto::OrganizationList GetOrganizationsByInnKpp(const std::wstring& inn, const std::wstring& kpp = std::wstring(), bool includeRelations = false);

	std::vector<Diadoc::Api::Proto::Organization> GetOrganizationsByInnList(const Diadoc::Api::Proto::GetOrganizationsByInnListRequest& request);

	template<typename InIt>
	std::vector<Diadoc::Api::Proto::Organization> GetOrganizationsByInnList(InIt firstInn, InIt lastInn)
	{
		Diadoc::Api::Proto::GetOrganizationsByInnListRequest request;
		std::copy(firstInn, lastInn, google::protobuf::RepeatedFieldBackInserter(request.mutable_innlist()));
		return GetOrganizationsByInnList(request);
	}

	template<typename InIt, typename Fn>
	std::vector<Diadoc::Api::Proto::Organization> GetOrganizationsByInnList(InIt firstInn, InIt lastInn, Fn transformFunc)
	{
		Diadoc::Api::Proto::GetOrganizationsByInnListRequest request;
		std::transform(firstInn, lastInn, google::protobuf::RepeatedFieldBackInserter(request.mutable_innlist()), transformFunc);
		return GetOrganizationsByInnList(request);
	}

	std::vector<Diadoc::Api::Proto::OrganizationWithCounteragentStatus> GetOrganizationsByInnList(const std::wstring& myOrgId, const Diadoc::Api::Proto::GetOrganizationsByInnListRequest& request);

	template<typename InIt>
	std::vector<Diadoc::Api::Proto::OrganizationWithCounteragentStatus> GetOrganizationsByInnList(const std::wstring& myOrgId, InIt firstInn, InIt lastInn)
	{
		Diadoc::Api::Proto::GetOrganizationsByInnListRequest request;
		std::copy(firstInn, lastInn, google::protobuf::RepeatedFieldBackInserter(request.mutable_innlist()));
		return GetOrganizationsByInnList(myOrgId, request);
	}

	template<typename InIt, typename Fn>
	std::vector<Diadoc::Api::Proto::OrganizationWithCounteragentStatus> GetOrganizationsByInnList(const std::wstring& myOrgId, InIt firstInn, InIt lastInn, Fn transformFunc)
	{
		Diadoc::Api::Proto::GetOrganizationsByInnListRequest request;
		std::transform(firstInn, lastInn, google::protobuf::RepeatedFieldBackInserter(request.mutable_innlist()), transformFunc);
		return GetOrganizationsByInnList(myOrgId, request);
	}

	Diadoc::Api::Proto::Organization GetOrganizationById(const std::wstring& orgId);
	Diadoc::Api::Proto::Organization GetOrganizationByInn(const std::wstring& inn);
	Diadoc::Api::Proto::Organization GetOrganizationByFnsParticipantId(const std::wstring& fnsParticipantId);
	Diadoc::Api::Proto::OrganizationList GetMyOrganizations();
	Diadoc::Api::Proto::OrganizationList GetMyOrganizations(bool autoRegister);
	Diadoc::Api::Proto::User GetMyUser();
	Diadoc::Api::Proto::OrganizationUsersList GetOrganizationUsers(const std::wstring& orgId);
	Diadoc::Api::Proto::Box GetBox(const std::wstring& boxId);
	Diadoc::Api::Proto::Department GetDepartment(const std::wstring& orgId, const std::wstring& departmentId);
	Diadoc::Api::Proto::CounteragentList GetCounteragents(const std::wstring& myOrgId, const std::wstring& counteragentStatus = std::wstring(), const std::wstring& afterIndexKey = std::wstring());
	Diadoc::Api::Proto::Counteragent GetCounteragent(const std::wstring& myOrgId, const std::wstring& counteragentOrgId);
	Diadoc::Api::Proto::CounteragentCertificateList GetCounteragentCertificates(const std::wstring& myOrgId, const std::wstring& counteragentOrgId);

	Diadoc::Api::Proto::AsyncMethodResult AcquireCounteragent(const std::wstring& myOrgId, const Diadoc::Api::Proto::AcquireCounteragentRequest& request);
	Diadoc::Api::Proto::AsyncMethodResult AcquireCounteragent(const std::wstring& myOrgId, const std::wstring& myDepartmentId, const Diadoc::Api::Proto::AcquireCounteragentRequest& request);
	TaskResult<Diadoc::Api::Proto::AcquireCounteragentResult> AcquireCounteragentResult(const std::wstring& taskId);
	void BreakWithCounteragent(const std::wstring& myOrgId, const std::wstring& counteragentOrgId, const std::wstring& comment = std::wstring());

	bool CanSendInvoice(const std::wstring& boxId, const Bytes_t& certBytes);
	void SendFnsRegistrationMessage(const std::wstring& boxId, const Bytes_t& certBytes);
	void MoveDocuments(const Diadoc::Api::Proto::Documents::DocumentsMoveOperation& operation);

	Diadoc::Api::Proto::OrganizationUserPermissions GetMyPermissions(const std::wstring& orgId);

	Diadoc::Api::Proto::KeyValueStorage::KeyValueStorageApiGetResponse GetOrganizationStorageEntries(const std::wstring& orgId, const Diadoc::Api::Proto::KeyValueStorage::KeyValueStorageApiGetRequest& keys);
	void PutOrganizationStorageEntries(const std::wstring& orgId, const Diadoc::Api::Proto::KeyValueStorage::KeyValueStorageApiPutRequest& entries);

	Diadoc::Api::Proto::Docflow::GetDocflowBatchResponse GetDocflows(const std::wstring& boxId, const Diadoc::Api::Proto::Docflow::GetDocflowBatchRequest& request);
	Diadoc::Api::Proto::Docflow::GetDocflowEventsResponse GetDocflowEvents(const std::wstring& boxId, const Diadoc::Api::Proto::Docflow::GetDocflowEventsRequest& request);
	Diadoc::Api::Proto::SignatureInfo GetSignatureInfo(const std::wstring& boxId, const std::wstring& messageId, const std::wstring& entityId);
	
	void ForwardDocument(const std::wstring& boxId, const Diadoc::Api::Proto::Forwarding::ForwardDocumentRequest& request);
	Diadoc::Api::Proto::Forwarding::GetForwardedDocumentsResponse GetForwardedDocuments(const std::wstring& boxId, const Diadoc::Api::Proto::Forwarding::GetForwardedDocumentsRequest& request);
	Diadoc::Api::Proto::Forwarding::GetForwardedDocumentEventsResponse GetForwardedDocumentEvents(const std::wstring& boxId, const Diadoc::Api::Proto::Forwarding::GetForwardedDocumentEventsRequest& request);
	Bytes_t GetForwardedEntityContent(const std::wstring& boxId, const Diadoc::Api::Proto::Forwarding::ForwardedDocumentId& forwardedDocumentId, const std::wstring& entityId);
	TaskResult<Diadoc::Api::Proto::Documents::DocumentProtocol> GenerateForwardedDocumentProtocol(const std::wstring& boxId, const Diadoc::Api::Proto::Forwarding::ForwardedDocumentId& forwardedDocumentId);
	Diadoc::Api::Proto::AsyncMethodResult CloudSign(const Diadoc::Api::Proto::CloudSignRequest& request, const std::wstring& certificateThumbprint);
	TaskResult<Diadoc::Api::Proto::CloudSignResult> CloudSignResult(const std::wstring& taskId);
	Diadoc::Api::Proto::AsyncMethodResult CloudSignConfirm(const std::wstring& token, const std::wstring& confirmationCode);
	TaskResult<Diadoc::Api::Proto::CloudSignConfirmResult> CloudSignConfirmResult(const std::wstring& taskId);
	Diadoc::Api::Proto::AsyncMethodResult AutoSignReceipts(const std::wstring& boxId, const std::wstring& certificateThumbprint, const std::wstring& batchKey);
	TaskResult<Diadoc::Api::Proto::AutosignReceiptsResult> WaitAutosignReceiptsResult(const std::wstring& taskId);
	Diadoc::Api::Proto::Documents::DocumentList GetDocumentsByMessageId(const std::wstring& boxId, const std::wstring& messageId);
	Diadoc::Api::Proto::Documents::Types::GetDocumentTypesResponse GetDocumentTypes(const std::wstring& boxId);
	WebFile GetContent(const std::wstring& typeNamedId, const std::wstring& function, const std::wstring& version, int titleIndex);

protected:
	Bytes_t PerformHttpRequest(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method);
	TaskResult<Bytes_t> PerformAsyncHttpRequest(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method);
	Bytes_t PerformHttpRequest(const std::wstring& queryString, const std::wstring& method);
	std::string PerformHttpRequestString(const std::wstring& queryString, const Bytes_t& requestBody, const std::wstring& method);
	std::string PerformHttpRequestString(const std::wstring& queryString, const std::wstring& method);

	std::wstring api_url_;
	std::wstring api_client_id_;
	INTERNET_PORT api_port_;
	DWORD connection_flags_;
	HttpSession session_;
	std::wstring token_;

	std::wstring proxy_username_;
	std::wstring proxy_password_;

private:
	static void ParseServerUrl(const std::wstring& serverUrl, std::wstring* apiHost, INTERNET_PORT* port, DWORD* flags);
	static Diadoc::Api::Proto::Invoicing::Signers::DocumentTitleType CreateUtdDocumentTitleType(bool forBuyer, bool forCorrection);
	static HttpSession InitSession(std::wstring proxyUrl, bool useDefaultProxySettings = true);
	static std::wstring GetVersionString();
	static std::wstring GetUserAgent();
	static std::string GetValueFromDraftResponseLine(const std::string& line);
	void SendRequest(HttpRequest& request, const Bytes_t& requestBody);

	Diadoc::Api::Proto::Organization GetOrganization(const std::wstring& id, const std::wstring& idName);

	std::wstring AuthorizationHeader();

	static Bytes_t ToProtoBytes(const google::protobuf::MessageLite& obj);

	template<class T>
	static T FromProtoBytes(const Bytes_t& bytes);

	template <typename T>
	WebFile GenerateInvoiceXml(const T& info, std::string invoiceTypeStr, std::string logString, bool disableValidation);

	template<class TRequest, class TResponse>
	TResponse PerformHttpRequestWithBoxId(const std::string& action, const std::wstring& boxId, const TRequest& request);

	template<class TRequest, class TResponse>
	TResponse PerformHttpRequest(const std::string& action, const std::wstring& queryString, const TRequest& request);

	template<class TResponse>
	TResponse PerformHttpRequest(const std::string& action, const std::wstring& queryString);

	template<class TResponse>
	TaskResult<TResponse> PerformAsyncHttpRequest(const std::string& action, const std::wstring& queryString, const std::wstring& method);

	static const ULONGLONG TimestampTicksOffset = 504911232000000000;
	static const std::wstring GET;
	static const std::wstring POST;
};

template<class T>
inline T DiadocApi::FromProtoBytes(const DiadocApi::Bytes_t& bytes)
{
	T result;
	if (!result.ParseFromArray(bytes.empty() ? NULL : &bytes[0], bytes.size()))
	{
		std::stringstream buf;
		buf << "protobuf parse error, required fields missing: " << result.InitializationErrorString();
		throw std::runtime_error(buf.str());
	}
	return result;
}
