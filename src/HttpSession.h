#pragma once

#include "HttpConnect.h"

class HttpSession
{
public:
	HttpSession(__in_z_opt LPCWSTR pszAgentW, __in DWORD dwAccessType, __in_z_opt LPCWSTR pszProxyW, __in_z_opt LPCWSTR pszProxyBypassW, __in DWORD dwFlags);
	virtual ~HttpSession(void);

	HttpSession(HttpSession&& orig);
	HttpSession& operator= (HttpSession&& right);

	HttpConnect Connect(IN LPCWSTR pswzServerName, IN INTERNET_PORT nServerPort) const;

protected:
	HINTERNET _handle;

private:
	HttpSession(const HttpSession& orig);
	HttpSession& operator=(const HttpSession& right);
};
