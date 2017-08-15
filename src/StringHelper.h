#pragma once

class StringHelper
{
public:
	static std::wstring Utf8ToUtf16(const std::string& utf8str);
	static std::wstring EncodingToUtf16(const std::string& encStr, UINT codePage);
	static std::string Utf16ToEncoding(const std::wstring& utf16str, UINT codePage);
	static std::string Utf16ToUtf8(const std::wstring& utf16str);

	template<class T>
	static std::vector<std::basic_string<T>> Split(const std::basic_string<T>& input, T delim);

	template<class T>
	static std::basic_string<T> LTrim(const std::basic_string<T>& input, T trimChar);

	template<class T>
	static std::basic_string<T> RTrim(const std::basic_string<T>& input, T trimChar);

	template<class T>
	static std::basic_string<T> Trim(const std::basic_string<T>& input, T trimChar);
	static std::wstring CanonicalizeUrl(const std::wstring& input);

private:
	static std::wstring EncodingToUtf16(const std::string& encStr, UINT codePage, DWORD flags);
};

template<class T>
inline std::vector<std::basic_string<T>> StringHelper::Split(const std::basic_string<T>& input, T delim)
{
	std::vector<std::basic_string<T>> result;
	std::basic_string<T> item;
	std::basic_istringstream<T> buf(input);
	while (std::getline(buf, item, delim))
	{
		result.push_back(item);
	}
	return result;
}

template<class T>
inline std::basic_string<T> StringHelper::LTrim(const std::basic_string<T>& input, T trimChar)
{
	std::basic_string<T> inputCopy(input);
	inputCopy.erase(inputCopy.begin(), std::find_if(inputCopy.begin(), inputCopy.end(), [=](T c){ return c != trimChar; }));
	return inputCopy;
}

template<class T>
inline std::basic_string<T> StringHelper::RTrim(const std::basic_string<T>& input, T trimChar)
{
	std::basic_string<T> inputCopy(input);
	inputCopy.erase(std::find_if(inputCopy.rbegin(), inputCopy.rend(), [=](T c){ return c != trimChar; }).base(), inputCopy.end());
	return inputCopy;
}

template<class T>
inline std::basic_string<T> StringHelper::Trim(const std::basic_string<T>& input, T trimChar)
{
	return LTrim(RTrim(input, trimChar), trimChar);
}
