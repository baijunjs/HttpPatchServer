#pragma once

enum language
{
	zhcn,
	en
};

class CLanguage
{
public:
	CLanguage();
	~CLanguage();
	void ReadProfile(std::tstring &szProfile, language eLang);
	std::tstring & GetText(DWORD dwKey);
	VOID SetText(DWORD dwKey, const TCHAR* pValue);
private:
	std::map<DWORD, std::tstring> m_langs;
};

extern CLanguage g_lang;
