#include "stdafx.h"
#include "SqlConfig.h"
#include <sstream>
#include <comutil.h>
#include <comdef.h>

CSqlConfig::CSqlConfig()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	m_pConnection = NULL;
}


CSqlConfig::~CSqlConfig()
{
	if (m_pConnection)
		m_pConnection.Release();

	CoUninitialize();
}


BOOL CSqlConfig::InitDBValue(LPCSTR pszIp, LPCSTR pszDb, LPCSTR pszUser, LPCSTR pszPwd)
{
	std::ostringstream szConnection;
	szConnection << "Provider=SQLOLEDB.1;Password=" << pszPwd
		<< ";Persist Security Info=True;User ID=" << pszUser
		<< ";Initial Catalog=" << pszDb
		<< ";Data Source=" << pszIp;
	try
	{
		HRESULT hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if (SUCCEEDED(hr))
		{
			m_pConnection->PutConnectionTimeout(5);
			//m_pConnection.SetConnectionTimeout = 2;
			hr = m_pConnection->Open(szConnection.str().c_str(), "", "", adModeUnknown);
			if (FAILED(hr))
			{
				vrvlog::SPD_LOG_WARN("Open database failed,con tstring:{0}", szConnection.str().c_str());
				return FALSE;
			}
		}

	}
	catch (_com_error &e)
	{
		vrvlog::SPD_LOG_ERROR("Open database failed:{0},con tstring:{1}", (const char*)_bstr_t(e.ErrorMessage()), szConnection.str().c_str());
		return FALSE;
	}
	return TRUE;
}



std::tstring CSqlConfig::GetPatchPath()
{
	std::tstring szValue;
	_RecordsetPtr	m_pRecord = NULL;

	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DISTRIBUTE__PATCH'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szValue = (TCHAR*)_bstr_t(value);
						if (szValue.back() != '\\')
							szValue.append(_T("\\"));
						szValue.append(_T("Patch"));
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}

	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szValue;
}


BOOL CSqlConfig::EnableUplink()
{
	BOOL bEnable = FALSE;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__UPCLASS'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						bEnable = _ttoi((TCHAR*)_bstr_t(value));
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();

	return bEnable;
}


std::tstring CSqlConfig::UplinkIp()
{
	std::tstring szValue;
	_RecordsetPtr	m_pRecord = NULL;

	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__UPADDRESS'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szValue = (TCHAR*)_bstr_t(value);
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szValue;
}


std::tstring CSqlConfig::UplinkPort()
{
	std::tstring szport;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__UPPORT'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szport = (TCHAR*)_bstr_t(value);
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szport;
}


int CSqlConfig::CycleType()
{
	int iType = 0;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__CYCLETYPE'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						iType = _ttoi((TCHAR*)_bstr_t(value));
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return iType;
}


std::tstring CSqlConfig::GetPeriod()
{
	std::tstring szValue;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__TIME'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szValue = (TCHAR*)_bstr_t(value);
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szValue;
}

std::tstring CSqlConfig::GetTime()
{
	std::tstring szValue;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__DATE'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szValue = (TCHAR*)_bstr_t(value);
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szValue;
}


BOOL CSqlConfig::EnableFluxCtrl()
{
	BOOL bEnable = FALSE;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__FLOWLIMITATIONSWITCH'";

	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						bEnable = _ttoi((TCHAR*)_bstr_t(value));
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return bEnable;
}


std::tstring CSqlConfig::GetFluxValue()
{
	std::tstring szFluxSpeed;
	_RecordsetPtr	m_pRecord = NULL;
	const char* szSql_comment = "SELECT dbo.IniConfig.keyvalue \
								FROM dbo.RegionManage INNER JOIN dbo.IniConfig \
								ON dbo.RegionManage.RegID = dbo.IniConfig.RegORScanID \
								where fullname='REG__DOWNPATCH__FLOWLIMITATION'";
	try
	{
		HRESULT hr = m_pRecord.CreateInstance(__uuidof(Recordset));
		if (SUCCEEDED(hr))
		{
			hr = m_pRecord->Open(szSql_comment, m_pConnection.GetInterfacePtr(), adOpenKeyset, adLockOptimistic, adCmdText);
			if (SUCCEEDED(hr))
			{
				while (!m_pRecord->adoEOF)
				{
					_variant_t value = m_pRecord->GetCollect("keyvalue");
					if (value.vt == VT_BSTR)
					{
						szFluxSpeed = (TCHAR*)_bstr_t(value);
						break;
					}
					m_pRecord->MoveNext();
				}
			}
		}
	}
	catch (_com_error &e)
	{
		//TODO:_com_error handler
		vrvlog::SPD_LOG_ERROR("Database query error:{0},sql:{1}", (const char*)_bstr_t(e.ErrorMessage()), szSql_comment);
	}

	if (m_pRecord)
		m_pRecord.Release();
	return szFluxSpeed;
}