class ApiException: public std::runtime_error
{
public:
	const DWORD CauseCode;
	ApiException(const std::string& message, DWORD code);
	ApiException(const std::string& message);
	virtual ~ApiException(void) {}

private:
	static std::string FormatExceptionMessage(const std::string& message, DWORD code);
};

class WinHttpException: public ApiException
{
public:
	WinHttpException(const std::string& message, DWORD code);
	WinHttpException(const std::string& message);
	virtual ~WinHttpException(void) {}
};

class CryptoApiException: public ApiException
{
public:
	CryptoApiException(const std::string& message, DWORD code);
	CryptoApiException(const std::string& message);
	virtual ~CryptoApiException(void) {}
};
