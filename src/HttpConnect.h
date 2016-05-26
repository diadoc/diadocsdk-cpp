#pragma once

#include "HttpRequest.h"

class HttpConnect
{
public:
	HttpConnect(IN HINTERNET hSession, IN LPCWSTR pswzServerName, IN INTERNET_PORT nServerPort, IN DWORD dwReserved);
	virtual ~HttpConnect(void);

	HttpConnect(HttpConnect&& orig);
	HttpConnect& operator= (HttpConnect&& right);

	HttpRequest OpenRequest(IN LPCWSTR pwszVerb, IN LPCWSTR pwszObjectName, IN LPCWSTR pwszVersion, IN LPCWSTR pwszReferrer OPTIONAL,
		IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL, IN DWORD dwFlags) const;

protected:
	HINTERNET _handle;

private:
	HttpConnect(const HttpConnect& orig);
	HttpConnect& operator=(const HttpConnect& right);
};
