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
				std::string szindexpath = appconfig.m_http_cfg.m_szPatchPath + "\\Tools\\";
				loadindex->SetProductPack((szindexpath + m_szIndexPath).c_str());
				if (!m_szSubIndexPath.empty())
				{
					loadindex->SetProductPack((szindexpath + m_szSubIndexPath).c_str());
				}
				return true;
			}
			return false;
		}

		bool CPatchIndex::load_language_index(ILoadIndex *loadindex)
		{
			if (loadindex)
			{
				std::string szindexpath = appconfig.m_http_cfg.m_szPatchPath + "\\Tools\\";
				loadindex->SetLanguagePack((szindexpath + m_szIndexPath).c_str());
				return true;
			}
			return false;
		}
	}
}
