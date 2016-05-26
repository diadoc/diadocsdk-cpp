#include "StdAfx.h"
#include "Certificate.h"
#include "ApiException.h"
#include <cryptuiapi.h>

const std::string Certificate::OID_GOST_34_11_94("1.2.643.2.2.9");

Certificate::Certificate(PCCERT_CONTEXT handle)
	: _handle(handle)
{
	if (_handle == NULL) throw std::runtime_error("Certificate::Certificate: handle cannot be NULL");
}

Certificate::Certificate(__in DWORD dwCertEncodingType, __in const BYTE *pbCertEncoded, __in DWORD cbCertEncoded)
	: _handle(CertCreateCertificateContext(dwCertEncodingType, pbCertEncoded, cbCertEncoded))
{
	if (_handle == NULL) throw std::runtime_error("Certificate::Certificate: handle cannot be NULL");
}

Certificate::~Certificate(void)
{
	if (_handle != NULL)
		CertFreeCertificateContext(_handle);
}

Certificate::Certificate(Certificate&& orig)
	: _handle(orig._handle)
{
	orig._handle = NULL;
}

Certificate::Certificate(const Certificate& orig)
	: _handle(CertDuplicateCertificateContext(orig._handle))
{
}

Certificate& Certificate::operator= (Certificate&& right)
{
	_handle = right._handle;
	right._handle = NULL;
	return *this;
}

Certificate& Certificate::operator= (const Certificate& right)
{
	if (_handle != NULL)
		CertFreeCertificateContext(_handle);
	_handle = CertDuplicateCertificateContext(right._handle);
	return *this;
}

bool Certificate::IsExpired() const
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	return CompareFileTime(&ft, &_handle->pCertInfo->NotAfter) == 1;
}

bool Certificate::IsTooEarly() const
{
	SYSTEMTIME st;
	FILETIME ft;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	return CompareFileTime(&ft,&_handle->pCertInfo->NotBefore) == -1;
}

Certificate::Bytes_t Certificate::GetBytes() const
{
	Bytes_t certPbData;
	auto begin = _handle->pbCertEncoded;
	auto end = begin + _handle->cbCertEncoded;
	certPbData.insert(certPbData.end(), begin, end);
	return certPbData;
}

Certificate::Bytes_t Certificate::Sign(const Bytes_t& input) const
{
	const BYTE* dataToSign = reinterpret_cast<const BYTE*>(&input[0]);
	DWORD dwSizeToSign = input.size();
	DWORD dwSizeSign = 0;
	CRYPT_SIGN_MESSAGE_PARA signPara;
	memset(&signPara, 0, sizeof(signPara));
	signPara.cbSize = sizeof(signPara);
	signPara.pSigningCert = _handle;
	signPara.cMsgCert = 1;
	signPara.rgpMsgCert = const_cast<PCCERT_CONTEXT*>(&_handle);
	signPara.dwMsgEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
	signPara.HashAlgorithm.pszObjId = const_cast<LPSTR>(OID_GOST_34_11_94.c_str());
	if (!CryptSignMessage(&signPara, TRUE, 1, &dataToSign, &dwSizeToSign, NULL, &dwSizeSign))
		throw CryptoApiException("CryptSignMessage error", GetLastError());
	Bytes_t signBytes;
	signBytes.resize(dwSizeSign);
	if (!CryptSignMessage(&signPara, TRUE, 1, &dataToSign, &dwSizeToSign, reinterpret_cast<BYTE*>(&signBytes[0]), &dwSizeSign))
		throw CryptoApiException("CryptSignMessage error", GetLastError());
	signBytes.resize(dwSizeSign);
	return signBytes;
}

std::wstring Certificate::GetStringValue(DWORD dwType, DWORD dwFlags, void *pvTypePara) const
{
	DWORD nameLength = CertGetNameString(_handle, dwType, dwFlags, pvTypePara, NULL, 0);
	std::vector<wchar_t> buf;
	buf.resize(nameLength);
	if(CertGetNameString(_handle, dwType, dwFlags, pvTypePara, &buf[0], nameLength) != nameLength)
		throw ApiException("CertGetNameString error", GetLastError());
	return std::wstring(&buf[0]);
}

Certificate::Bytes_t Certificate::GetThumbprint() const
{
	DWORD pcbProperty = 0;
	if (!CertGetCertificateContextProperty(_handle, CERT_HASH_PROP_ID, NULL, &pcbProperty))
		throw CryptoApiException("CertGetCertificateContextProperty error", GetLastError());
	Bytes_t data;
	data.resize(pcbProperty);
	if (!CertGetCertificateContextProperty(_handle, CERT_HASH_PROP_ID, &data[0], &pcbProperty))
		throw CryptoApiException("CertGetCertificateContextProperty error", GetLastError());
	return data;
}

std::wstring Certificate::GetName() const
{
	return GetStringValue(CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL);
}

std::wstring Certificate::GetIssuerName() const
{
	return GetStringValue(CERT_NAME_SIMPLE_DISPLAY_TYPE, CERT_NAME_ISSUER_FLAG, NULL);
}

std::wstring Certificate::GetOrganizationName() const
{
	return GetStringValue(CERT_NAME_ATTR_TYPE, 0, szOID_ORGANIZATION_NAME);
}

FILETIME Certificate::GetValidFrom() const
{
	return _handle->pCertInfo->NotBefore;
}

FILETIME Certificate::GetValidTo() const
{
	return _handle->pCertInfo->NotAfter;
}

bool Certificate::HasPrivateKey() const
{
	DWORD cbSize = 0;
	if (!CertGetCertificateContextProperty(_handle, CERT_KEY_PROV_INFO_PROP_ID, NULL, &cbSize) && GetLastError() != ERROR_MORE_DATA)
		return false;
	Bytes_t buf;
	buf.resize(cbSize);
	return CertGetCertificateContextProperty(_handle, CERT_KEY_PROV_INFO_PROP_ID, &buf[0], &cbSize) == TRUE;
}

std::wstring Certificate::GetFriendlyName() const
{
	return GetStringValue(CERT_NAME_FRIENDLY_DISPLAY_TYPE, 0, NULL);
}

void Certificate::ShowCertificateUI(HWND hwnd, LPCWSTR pwszTitle, DWORD dwFlags) const
{
	CryptUIDlgViewContext(CERT_STORE_CERTIFICATE_CONTEXT, _handle, hwnd, pwszTitle, dwFlags, NULL);
}

Certificate::Bytes_t Certificate::GetCertificateHash(ALG_ID algId, DWORD flags) const
{
	DWORD cbSize = 0;
	CertGetCertificateContextProperty(_handle, CERT_KEY_PROV_INFO_PROP_ID, NULL, &cbSize);
	Bytes_t buf;
	buf.resize(cbSize);
	auto status = CertGetCertificateContextProperty(_handle, CERT_KEY_PROV_INFO_PROP_ID, &buf[0], &cbSize);
	if (!status)
		throw ApiException("CertGetCertificateContextProperty", GetLastError());
	CRYPT_KEY_PROV_INFO* keyProvInfo = reinterpret_cast<CRYPT_KEY_PROV_INFO*>(&buf[0]);
	HCRYPTPROV phProv = NULL;
	status = CryptAcquireContext(&phProv, keyProvInfo->pwszContainerName, keyProvInfo->pwszProvName, keyProvInfo->dwProvType, keyProvInfo->dwFlags);
	if (!status)
		throw ApiException("CryptAcquireContext", GetLastError());
	DWORD cbHash = 0;
	CryptHashCertificate(phProv, algId, flags, _handle->pbCertEncoded, _handle->cbCertEncoded, NULL, &cbHash);
	Bytes_t cert;
	cert.resize(cbHash);
	status = CryptHashCertificate(phProv, algId, flags, _handle->pbCertEncoded, _handle->cbCertEncoded, reinterpret_cast<BYTE*>(&cert[0]), &cbHash);
	if (!status)
		throw ApiException("CryptHashCertificate", GetLastError());
	CryptReleaseContext(phProv, 0);
	return cert;
}