#include "StdAfx.h"
#include "ApiException.h"

ApiException::ApiException(const std::string& message, DWORD code)
	: std::runtime_error(FormatExceptionMessage(message, code))
	, CauseCode(code)
{
}

ApiException::ApiException(const std::string& message)
	: std::runtime_error(message)
	, CauseCode(-1)
{
}

std::string ApiException::FormatExceptionMessage(const std::string& message, DWORD code)
{
	std::stringstream buf;
	buf << message << " , error = " << code << " (0x" << std::hex << code << std::dec << ")";
	return buf.str();
}


WinHttpException::WinHttpException(const std::string& message, DWORD code) 
	: ApiException(message, code)
{}

WinHttpException::WinHttpException(const std::string& message) 
	: ApiException(message)
{}


CryptoApiException::CryptoApiException(const std::string& message, DWORD code) 
	: ApiException(message, code)
{}

CryptoApiException::CryptoApiException(const std::string& message) 
	: ApiException(message)
{}
