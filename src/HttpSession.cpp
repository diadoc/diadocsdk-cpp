#include "StdAfx.h"
#include "HttpSession.h"
#include "ApiException.h"

HttpSession::HttpSession(__in_z_opt LPCWSTR pszAgentW, __in DWORD dwAccessType, __in_z_opt LPCWSTR pszProxyW, __in_z_opt LPCWSTR pszProxyBypassW, __in DWORD dwFlags)
	: _handle(WinHttpOpen(pszAgentW, dwAccessType, pszProxyW, pszProxyBypassW, dwFlags))
{
	if (_handle == NULL) throw WinHttpException("WinHttpOpen error", GetLastError());
}

HttpSession::HttpSession(HttpSession&& orig)
{
	_handle = std::move(orig._handle);
	orig._handle = NULL;
}

HttpSession& HttpSession::operator= (HttpSession&& right)
{
	_handle = std::move(right._handle);
	right._handle = NULL;
	return *this;
}

HttpSession::~HttpSession(void)
{
	if (_handle != NULL)
		WinHttpCloseHandle(_handle);
}

HttpConnect HttpSession::Connect(IN LPCWSTR pswzServerName, IN INTERNET_PORT nServerPort) const
{
	return HttpConnect(_handle, pswzServerName, nServerPort, 0);
}
