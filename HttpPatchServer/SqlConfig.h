#pragma once
#include <string>

class CSqlConfig
{
public:
	CSqlConfig();
	~CSqlConfig();
public:
	BOOL InitDBValue(LPCSTR pszIp, LPCSTR pszDb, LPCSTR pszUser, LPCSTR pszPwd);
	std::tstring GetPatchPath();
	BOOL EnableUplink();
	std::tstring UplinkIp();
	std::tstring UplinkPort();
	int CycleType();
	std::tstring GetPeriod();
	std::tstring GetTime();
	BOOL EnableFluxCtrl();
	std::tstring GetFluxValue();
private:
	_ConnectionPtr	m_pConnection;
};

