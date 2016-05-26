#include "StdAfx.h"
#include "StringHelper.h"
#include "ApiException.h"

std::wstring StringHelper::Utf8ToUtf16(const std::string& utf8str)
{
	return EncodingToUtf16(utf8str, CP_UTF8, 0);
}

std::wstring StringHelper::EncodingToUtf16(const std::string& input, UINT codePage)
{
	return EncodingToUtf16(input, codePage, MB_ERR_INVALID_CHARS | MB_COMPOSITE);
}

std::wstring StringHelper::EncodingToUtf16(const std::string& encStr, UINT codePage, DWORD flags)
{
	if (encStr.empty())
		return std::wstring();
	int realSize = MultiByteToWideChar(codePage, flags, encStr.c_str(), encStr.size(), NULL, 0);
	if (realSize == 0)
		throw ApiException("MultiByteToWideChar error", GetLastError());
	std::vector<wchar_t> buf;
	buf.resize(realSize);
	MultiByteToWideChar(codePage, flags, encStr.c_str(), encStr.size(), &buf[0], buf.size());
	return std::wstring(buf.begin(), buf.end());
}

std::string StringHelper::Utf16ToEncoding(const std::wstring& input, UINT codePage)
{
	if (input.empty())
		return std::string();
	int utf8Size = WideCharToMultiByte(codePage, 0, input.c_str(), input.size(), NULL, 0, NULL, NULL);
	if (utf8Size == 0)
		throw ApiException("WideCharToMultiByte error", GetLastError());
	std::vector<char> buf;
	buf.resize(utf8Size);
	WideCharToMultiByte(codePage, 0, input.c_str(), input.size(), &buf[0], buf.size(), NULL, NULL);
	return std::string(buf.begin(), buf.end());
}

std::string StringHelper::Utf16ToUtf8(const std::wstring& input)
{
	return Utf16ToEncoding(input, CP_UTF8);
}

std::wstring Replace(const std::wstring& orig,const std::wstring& fnd, const std::wstring& repl)
{
    std::wstring ret = orig;
    size_t pos = 0;

	while ( std::wstring::npos != ( pos = ret.find( fnd ) ) )
	{
	 ret.replace( pos, fnd.length( ), repl );
	}

	return ret;
}

std::wstring StringHelper::CanonicalizeUrl(const std::wstring& input)
{
	DWORD dwLength = 100;
	std::vector<wchar_t> buf;
	buf.resize(dwLength);

	// Replacing # - c'z in api we dont have hrefs
	auto safeInput = Replace(input, L"#", L"%23");

	if (!AtlCanonicalizeUrl(input.c_str(), &buf[0], &dwLength))
	{
		buf.resize(dwLength);
		if (!AtlCanonicalizeUrl(input.c_str(), &buf[0], &dwLength))
			throw ApiException("AtlCanonicalizeUrl error", GetLastError());
	}
	return std::wstring(&buf[0]);
}