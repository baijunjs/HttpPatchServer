#pragma once
#include <string>

class CSqlConfig
{
public:
	CSqlConfig();
	~CSqlConfig();
public:
	BOOL InitDBValue(LPCSTR pszIp, LPCSTR pszDb, LPCSTR pszUser, LPCSTR pszPwd);
	std::string GetPatchPath();
	BOOL EnableUplink();
	std::string UplinkIp();
	std::string UplinkPort();
	int CycleType();
	std::string GetPeriod();
	std::string GetTime();
	BOOL EnableFluxCtrl();
	std::string GetFluxValue();
private:
	_ConnectionPtr	m_pConnection;
};

