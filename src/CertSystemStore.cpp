#include "StdAfx.h"
#include "CertSystemStore.h"
#include "ApiException.h"

CertSystemStore::CertSystemStore(__in_opt HCRYPTPROV_LEGACY hProv, __in LPCWSTR szSubsystemProtocol)
	: _handle(CertOpenSystemStore(hProv, szSubsystemProtocol))
{
	if (_handle == NULL) throw CryptoApiException("CertOpenSystemStore error", GetLastError());
}

CertSystemStore::CertSystemStore(__in LPCSTR lpszStoreProvider, __in DWORD dwMsgAndCertEncodingType, __in HCRYPTPROV_LEGACY hCryptProv, __in DWORD dwFlags, __in const void *pvPara)
	: _handle(CertOpenStore(lpszStoreProvider, dwMsgAndCertEncodingType, hCryptProv, dwFlags, pvPara))
{
	if (_handle == NULL) throw CryptoApiException("CertOpenStore error", GetLastError());
}

CertSystemStore::CertSystemStore(bool useLocalMachineStorage)
	: _handle(CertOpenStore(CERT_STORE_PROV_SYSTEM_W, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, useLocalMachineStorage ? CERT_SYSTEM_STORE_LOCAL_MACHINE : CERT_SYSTEM_STORE_CURRENT_USER, L"MY"))
{
	if (_handle == NULL) throw CryptoApiException("CertOpenStore error", GetLastError());
}

CertSystemStore::~CertSystemStore(void)
{
	if (_handle != NULL)
		CertCloseStore(_handle, 0);
}

CertSystemStore::CertSystemStore(CertSystemStore&& orig)
	: _handle(orig._handle)
{
	orig._handle = NULL;
}

CertSystemStore& CertSystemStore::operator= (CertSystemStore&& right)
{
	_handle = std::move(right._handle);
	right._handle = NULL;
	return *this;
}

CertSystemStore::Bytes_t CertSystemStore::Encrypt(const Bytes_t& input, const std::string& algorithmOid, const std::vector<Certificate>& recipientCerts) const
{
	CRYPT_ENCRYPT_MESSAGE_PARA cemp = {0};
	cemp.cbSize = sizeof(cemp);
	cemp.dwMsgEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
	cemp.ContentEncryptionAlgorithm.pszObjId = const_cast<LPSTR>(algorithmOid.c_str());
	DWORD cbEncrypted = 0;
	std::vector<PCCERT_CONTEXT> certs;
	std::transform(recipientCerts.begin(), recipientCerts.end(), std::back_inserter(certs), [](const Certificate& c){ return c._handle; });
	auto cRecipientCert = certs.size();
	auto rgpRecipientCert = &certs[0];
	auto pbToBeEncrypted = reinterpret_cast<const BYTE*>(&input[0]);
	auto cbToBeEncrypted = input.size();
	if (!CryptEncryptMessage(&cemp, cRecipientCert, rgpRecipientCert, pbToBeEncrypted, cbToBeEncrypted, NULL, &cbEncrypted))
		throw CryptoApiException("CryptEncryptMessage error", GetLastError());

	Bytes_t encoded;
	encoded.resize(cbEncrypted);
	auto pbEncryptedBlob = reinterpret_cast<BYTE*>(&encoded[0]);
	if (!CryptEncryptMessage(&cemp, cRecipientCert, rgpRecipientCert, pbToBeEncrypted, cbToBeEncrypted, pbEncryptedBlob, &cbEncrypted))
		throw CryptoApiException("CryptEncryptMessage error", GetLastError());
	encoded.resize(cbEncrypted);
	return encoded;
}

CertSystemStore::Bytes_t CertSystemStore::Encrypt(const Bytes_t& input, const std::string& algorithmOid, const Certificate& recipientCert) const
{
	std::vector<Certificate> recipientCerts;
	recipientCerts.push_back(recipientCert);
	return Encrypt(input, algorithmOid, recipientCerts);
}

CertSystemStore::Bytes_t CertSystemStore::Decrypt(const Bytes_t& input) const
{
	CRYPT_DECRYPT_MESSAGE_PARA cdmp;
	cdmp.cbSize = sizeof(cdmp);
	cdmp.dwMsgAndCertEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
	cdmp.cCertStore = 1;
	cdmp.rghCertStore = const_cast<HCERTSTORE*>(&_handle);

	DWORD cbDecrypted = 0;
	if (!CryptDecryptMessage(&cdmp, reinterpret_cast<const BYTE*>(&input[0]), input.size(), NULL, &cbDecrypted, NULL))
		throw CryptoApiException("CryptDecryptMessage error", GetLastError());
	Bytes_t decoded;
	decoded.resize(cbDecrypted);
	if (!CryptDecryptMessage(&cdmp, reinterpret_cast<const BYTE*>(&input[0]), input.size(), reinterpret_cast<BYTE*>(&decoded[0]), &cbDecrypted, NULL))
	{
		throw CryptoApiException("CryptDecryptMessage error", GetLastError());
	}
	// Почему-то CryptDecryptMessage второй раз выдает размер меньше. WTF??
	decoded.resize(cbDecrypted);
	return decoded;
	
}

std::vector<Certificate> CertSystemStore::GetCertificatesFromStore(__in DWORD dwCertEncodingType, __in DWORD dwFindFlags, __in DWORD dwFindType, __in_opt const void *pvFindPara) const
{
	std::vector<Certificate> certs;
	PCCERT_CONTEXT certHandle = NULL;
	while ((certHandle = CertFindCertificateInStore(_handle, dwCertEncodingType, dwFindFlags, dwFindType, pvFindPara, certHandle)) != NULL)
	{
		auto newCertContext = CertDuplicateCertificateContext(certHandle);
		certs.push_back(Certificate(newCertContext));
	}
	return certs;
}

std::vector<Certificate> CertSystemStore::EnumCertificates() const
{
	std::vector<Certificate> certs;
	PCCERT_CONTEXT certHandle = NULL;
	while ((certHandle = CertEnumCertificatesInStore(_handle, certHandle)) != NULL)
	{
		auto newContext = CertDuplicateCertificateContext(certHandle);
		certs.push_back(Certificate(newContext));
	}
	return certs;
}

Certificate CertSystemStore::GetCertificateByThumbprint(const Bytes_t& thumbprint) const
{
	CRYPT_HASH_BLOB hash;
	hash.cbData = thumbprint.size();
	hash.pbData = reinterpret_cast<BYTE*>(const_cast<char*>(&thumbprint[0]));
	auto certs = GetCertificatesFromStore(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, 0, CERT_FIND_HASH, &hash);
	if (certs.empty())
		throw std::runtime_error("Certificate not found");
	return certs[0];
}