#pragma once

#include "Certificate.h"

class CryptHelper
{
public:
	typedef std::vector<char> Bytes_t;

	static std::wstring ToBase64(const Bytes_t& input);
	static Bytes_t FromBase64(const std::wstring& input);
	static Bytes_t EncryptBytes(const Bytes_t& input, const std::string& algorithmOid, const Certificate& recipientCert);
	static Bytes_t DecryptBytes(const Bytes_t& input);
	static std::vector<Certificate> GetCertificatesFromStore(__in DWORD dwCertEncodingType, __in DWORD dwFindFlags, __in DWORD dwFindType, __in_opt const void *pvFindPara);
	static Bytes_t FromAsciiHex(const std::wstring& input);
	static Bytes_t BytesFromString(const std::wstring& input, DWORD type);

private:
	static const std::wstring StoreName;
};
