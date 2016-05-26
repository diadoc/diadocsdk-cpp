#include "StdAfx.h"
#include "CryptHelper.h"
#include "ApiException.h"
#include "CertSystemStore.h"

const std::wstring CryptHelper::StoreName(L"MY");

std::wstring CryptHelper::ToBase64(const Bytes_t& input)
{
	if (input.empty())
		throw std::runtime_error("CryptHelper::ToBase64: cannot process empty buffer");

	const BYTE* pbBinary = reinterpret_cast<const BYTE*>(&input[0]);
	DWORD dwSize = 0;
	if (!CryptBinaryToString(pbBinary, input.size(), CRYPT_STRING_BASE64, NULL, &dwSize))
		throw CryptoApiException("CryptBinaryToString error", GetLastError());

	std::vector<WCHAR> buf;
	buf.resize(dwSize);
	if (!CryptBinaryToString(pbBinary, input.size(), CRYPT_STRING_BASE64, &buf[0], &dwSize))
		throw CryptoApiException("CryptBinaryToString error", GetLastError());
	buf.resize(dwSize);

	// remove CR/LF
	buf.erase(std::remove_if(buf.begin(), buf.end(), [](char c){ return c == '\r' || c == '\n'; }), buf.end());
	return std::wstring(buf.begin(), buf.end());
}

CryptHelper::Bytes_t CryptHelper::FromBase64(const std::wstring& input)
{
	return BytesFromString(input, CRYPT_STRING_BASE64);
}

CryptHelper::Bytes_t CryptHelper::FromAsciiHex(const std::wstring& input)
{
	return BytesFromString(input, CRYPT_STRING_HEX_ANY);
}

CryptHelper::Bytes_t CryptHelper::BytesFromString(const std::wstring& input, DWORD type)
{
	DWORD dwSize = 0;
	if (!CryptStringToBinary(input.c_str(), input.size(), type, NULL, &dwSize, NULL, NULL))
		throw CryptoApiException("CryptStringToBinary error", GetLastError());

	Bytes_t bytes;
	bytes.resize(dwSize);
	if (!CryptStringToBinary(input.c_str(), input.size(), type, reinterpret_cast<BYTE*>(&bytes[0]), &dwSize, NULL, NULL))
		throw CryptoApiException("CryptStringToBinary error", GetLastError());
	bytes.resize(dwSize);
	return bytes;
}

CryptHelper::Bytes_t CryptHelper::EncryptBytes(const Bytes_t& input, const std::string& algorithmOid, const Certificate& recipientCert)
{
	CertSystemStore certStore(NULL, StoreName.c_str());
	return certStore.Encrypt(input, algorithmOid, recipientCert);
}

CryptHelper::Bytes_t CryptHelper::DecryptBytes(const Bytes_t& input)
{
	CertSystemStore certStore(NULL, StoreName.c_str());
	return certStore.Decrypt(input);
}

std::vector<Certificate> CryptHelper::GetCertificatesFromStore(__in DWORD dwCertEncodingType, __in DWORD dwFindFlags, __in DWORD dwFindType, __in_opt const void *pvFindPara)
{
	CertSystemStore certStore(NULL, StoreName.c_str());
	return certStore.GetCertificatesFromStore(dwCertEncodingType, dwFindFlags, dwFindType, pvFindPara);
}
