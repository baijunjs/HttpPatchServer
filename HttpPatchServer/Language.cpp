#include "stdafx.h"
#include "Language.h"

CLanguage g_lang;

CLanguage::CLanguage()
{
}


CLanguage::~CLanguage()
{
}

void CLanguage::ReadProfile(std::tstring &szProfile, language eLang)
{
	std::tstring szLang = _T("ZHCN");
	if (eLang == zhcn)
		szLang = _T("ZHCN");

	else if (eLang == en)
		szLang = _T("EN");

	TCHAR szKeys[5 * 1024] = { 0 };
	TCHAR szValue[200] = { 0 };
	GetPrivateProfileString(szLang.c_str(), NULL, _T(""), szKeys, 5 * 1024, szProfile.c_str());
	TCHAR *pszKey = nullptr;
	pszKey = szKeys;
	while ( *pszKey != '\0')
	{
		GetPrivateProfileString(szLang.c_str(), pszKey, _T(""), szValue, 200, szProfile.c_str());
		int iKey = _ttoi(pszKey);
		SetText(iKey, szValue);
		pszKey = pszKey + _tcslen(pszKey) + 1;
	}
}


std::tstring & CLanguage::GetText(DWORD dwKey)
{
	return m_langs[dwKey];
}


VOID CLanguage::SetText(DWORD dwKey, const TCHAR* pValue)
{
	m_langs.insert(std::make_pair(dwKey, pValue));
}