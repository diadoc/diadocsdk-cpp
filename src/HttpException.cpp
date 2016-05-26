#include "StdAfx.h"
#include "HttpException.h"

HttpException::HttpException(const std::string& message, DWORD statusCode, const std::string& serverMessage)
	: std::runtime_error(message + ": " + serverMessage)
	, StatusCode(statusCode)
	, ServerMessage(serverMessage)
{
}

HttpException::~HttpException(void)
{
}
