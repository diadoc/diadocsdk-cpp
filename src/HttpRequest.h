#pragma once
class HttpRequest
{
public:
	typedef std::vector<char> Bytes_t;

	HttpRequest(IN HINTERNET hConnect, IN LPCWSTR pwszVerb, IN LPCWSTR pwszObjectName, IN LPCWSTR pwszVersion, IN LPCWSTR pwszReferrer OPTIONAL,
		IN LPCWSTR FAR * ppwszAcceptTypes OPTIONAL, IN DWORD dwFlags);
	virtual ~HttpRequest(void);

	HttpRequest(HttpRequest&& orig);
	HttpRequest& operator= (HttpRequest&& right);

	void SetCredentials(IN DWORD AuthTargets, IN DWORD AuthScheme, IN LPCWSTR pwszUserName, IN LPCWSTR pwszPassword, IN LPVOID pAuthParams) const;
	void Send(__in_ecount_opt(dwHeadersLength) LPCWSTR lpszHeaders, IN DWORD dwHeadersLength, __in_bcount_opt(dwOptionalLength) LPVOID lpOptional,
		IN DWORD dwOptionalLength, IN DWORD dwTotalLength, IN DWORD_PTR dwContext) const;
	void WriteData(__in_bcount_opt(dwNumberOfBytesToWrite) LPCVOID lpBuffer, IN DWORD dwNumberOfBytesToWrite) const;
	void ReadData(__out_bcount_part(dwNumberOfBytesToRead, *lpdwNumberOfBytesRead) __out_data_source(NETWORK) LPVOID lpBuffer, IN DWORD dwNumberOfBytesToRead) const;
	void ReceiveResponse(IN LPVOID lpReserved) const;

	Bytes_t QueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL) const;
	bool TryQueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL, Bytes_t* bytes) const;
	DWORD GetStatusCode() const;
	bool TryGetRetryAfter(int* retryAfter) const;
	std::wstring QueryHeadersString(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL, IN OUT LPDWORD lpdwIndex OPTIONAL) const;
	std::wstring GetContentType() const;

	class ContentDisposition
	{
	public:
		ContentDisposition(const std::wstring& headerStr);
		~ContentDisposition();

		// move
		ContentDisposition(ContentDisposition&& orig);
		ContentDisposition& operator=(ContentDisposition&& right);

		std::wstring GetFileName() const;

	private:
		void ParseParameter(const std::wstring& paramStr);
		std::wstring dispositionType;
		std::map<std::wstring, std::wstring> dispositionParams;
		static const std::wstring FileNameParam;
	};
	ContentDisposition GetContentDisposition() const;

	DWORD QueryDataAvailable() const;
	Bytes_t ReadAllResponse() const;
	void QueryAuthSchemes(OUT LPDWORD lpdwSupportedSchemes, OUT LPDWORD lpdwFirstScheme, OUT LPDWORD pdwAuthTarget) const;
	BOOL QueryOption(__in DWORD dwOption, __out LPVOID lpBuffer, __inout LPDWORD lpdwBufferLength);
	Bytes_t QueryOption(__in DWORD dwOption);

	std::wstring DebugQueryAllHeaders() const;

protected:
	HINTERNET _handle;

private:
	HttpRequest(const HttpRequest& orig);
	HttpRequest& operator=(const HttpRequest& orig);

	void QueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL,
		__out_bcount_part_opt(*lpdwBufferLength, *lpdwBufferLength) __out_data_source(NETWORK) LPVOID lpBuffer,
		IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex OPTIONAL) const;
	bool TryQueryHeaders(IN DWORD dwInfoLevel, IN LPCWSTR pwszName OPTIONAL,
		__out_bcount_part_opt(*lpdwBufferLength, *lpdwBufferLength) __out_data_source(NETWORK) LPVOID lpBuffer,
		IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex OPTIONAL) const;
};
