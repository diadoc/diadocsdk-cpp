#include "stdafx.h" 

void
	WppTraceDebugOut(
	__in    const WCHAR *pszFmt,
	...
	)
{
	va_list pArgs;

	va_start(pArgs, pszFmt);

	WCHAR buf[MAX_PATH];

	if (SUCCEEDED(StringCchVPrintf(buf,
		MAX_PATH,
		pszFmt,
		pArgs)) &&
		SUCCEEDED(StringCchCat(buf,
		MAX_PATH,
		L"\n")))
	{
		OutputDebugString(buf);
	}

	va_end(pArgs);
}

void
	WppTraceDebugOut(
	__in    const CHAR *pszFmt,
	...
	)
{
	va_list pArgs;

	va_start(pArgs, pszFmt);

	CHAR buf[MAX_PATH];

	if (SUCCEEDED(StringCchVPrintfA(buf,
		MAX_PATH,
		pszFmt,
		pArgs)) &&
		SUCCEEDED(StringCchCatA(buf,
		MAX_PATH,
		"\n")))
	{
		OutputDebugStringA(buf);
	}

	va_end(pArgs);
}

