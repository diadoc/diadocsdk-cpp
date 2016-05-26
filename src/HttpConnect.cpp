#include "StdAfx.h"
#include "HttpConnect.h"
#include "ApiException.h"

HttpConnect::HttpConnect(IN HINTERNET hSession, IN LPCWSTR pswzServerName, IN INTERNET_PORT nServerPort, IN DWORD dwReserved)
	: _handle(WinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved))
{
	if (_handle == NULL) throw WinHttpException("WinHttpConnect error", GetLastError());
}

HttpConnect::~HttpConnect(void)
{
	if (_handle != NULL)
		WinHttpCloseHandle(_handle);
}

HttpConnect::HttpConnect(HttpConnect&& orig)
{
	_handle = std::move(orig._handle);
	orig._handle = NULL;
}

HttpConnect& HttpConnect::operator= (HttpConnect&& right)
{
	_handle = std::move(right._handle);
	right._handle = NULL;
	return *this;
}

HttpRequest HttpConnect::OpenRequest(IN LPCWSTR pwszVerb, IN LPCWSTR pwszObjectName, IN LPCWSTR pwszVersion, IN LPCWSTR pwszReferrer OPTIONAL,
	IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL, IN DWORD dwFlags) const
{
	return HttpRequest(_handle, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
}
