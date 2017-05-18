#include "stdafx.h"
#include "PatchIndex.h"


namespace vrv
{
	namespace patch
	{
		CPatchIndex::CPatchIndex()
		{
		}


		CPatchIndex::~CPatchIndex()
		{
		}

		bool CPatchIndex::load_product_index(ILoadIndex *loadindex)
		{
			if (loadindex)
			{
				std::tstring szindexpath = appconfig.m_http_cfg.m_szPatchPath + _T("\\Tools\\");
				loadindex->SetProductPack((const char*)_bstr_t((szindexpath + m_szIndexPath).c_str()));
				if (!m_szSubIndexPath.empty())
				{
					loadindex->SetProductPack((const char*)_bstr_t((szindexpath + m_szSubIndexPath).c_str()));
				}
				return true;
			}
			return false;
		}

		bool CPatchIndex::load_language_index(ILoadIndex *loadindex)
		{
			if (loadindex)
			{
				std::tstring szindexpath = appconfig.m_http_cfg.m_szPatchPath + _T("\\Tools\\");
				loadindex->SetLanguagePack((const char*)_bstr_t((szindexpath + m_szIndexPath).c_str()));
				return true;
			}
			return false;
		}
	}
}
