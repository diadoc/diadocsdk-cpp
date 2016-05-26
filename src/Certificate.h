#pragma once
class Certificate
{
	friend class CertSystemStore;

public:
	typedef std::vector<char> Bytes_t;

	Certificate(PCCERT_CONTEXT handle);
	Certificate(__in DWORD dwCertEncodingType, __in const BYTE *pbCertEncoded, __in DWORD cbCertEncoded);
	virtual ~Certificate(void);

	Certificate(Certificate&& orig);
	Certificate& operator=(Certificate&& right);

	Certificate(const Certificate& orig);
	Certificate& operator=(const Certificate& right);

	bool IsExpired() const;
	bool IsTooEarly() const;
	std::wstring GetStringValue(DWORD dwType, DWORD dwFlags, void *pvTypePara) const;

	Bytes_t GetBytes() const;

	Bytes_t Sign(const Bytes_t& input) const;

	bool HasPrivateKey() const;
	std::wstring GetFriendlyName() const;
	void ShowCertificateUI(IN OPTIONAL HWND hwnd, IN OPTIONAL LPCWSTR pwszTitle, IN DWORD dwFlags) const;
	Bytes_t GetCertificateHash(ALG_ID algId, DWORD flags) const;
	
	Bytes_t GetThumbprint() const;
	std::wstring GetName() const;
	std::wstring GetIssuerName() const;
	std::wstring GetOrganizationName() const;
	FILETIME GetValidFrom() const;
	FILETIME GetValidTo() const;
	

private:
	PCCERT_CONTEXT _handle;
	static const std::string OID_GOST_34_11_94;
};
