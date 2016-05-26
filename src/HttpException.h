#pragma once

class HttpException: public std::runtime_error
{
public:
	HttpException(const std::string& message, DWORD statusCode, const std::string& serverMessage);
	virtual ~HttpException(void);

	DWORD StatusCode;
	std::string ServerMessage;
};
