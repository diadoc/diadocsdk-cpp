#pragma once

#include "Certificate.h"

class CertSystemStore
{
public:
	typedef std::vector<char> Bytes_t;

	explicit CertSystemStore(bool useLocalMachineStorage);
	CertSystemStore(__in_opt HCRYPTPROV_LEGACY hProv, __in LPCWSTR szSubsystemProtocol);
	CertSystemStore(__in LPCSTR lpszStoreProvider, __in DWORD dwMsgAndCertEncodingType, __in HCRYPTPROV_LEGACY hCryptProv, __in DWORD dwFlags, __in const void *pvPara);
	virtual ~CertSystemStore(void);
	CertSystemStore(CertSystemStore&& orig);
	CertSystemStore& operator= (CertSystemStore&& right);

	Bytes_t Encrypt(const Bytes_t& input, const std::string& algorithmOid, const std::vector<Certificate>& recipientCerts) const;
	Bytes_t Encrypt(const Bytes_t& input, const std::string& algorithmOid, const Certificate& recipientCert) const;
	Bytes_t Decrypt(const Bytes_t& input) const;
	std::vector<Certificate> GetCertificatesFromStore(__in DWORD dwCertEncodingType, __in DWORD dwFindFlags, __in DWORD dwFindType, __in_opt const void *pvFindPara) const;
	std::vector<Certificate> EnumCertificates() const;

	Certificate GetCertificateByThumbprint(const Bytes_t& thumbprint) const;

protected:
	HCERTSTORE _handle;
};
