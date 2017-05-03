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

		bool CPatchIndex::analyze_sub_index(ILoadIndex *loadindex)
		{
			if (loadindex == nullptr)
				return false;

			//ÓïÑÔ°ü
			if (m_bLanguage == true)
			{
				loadindex->SetLanguagePack(m_szIndexPath.c_str());
			}
			else
			{
				loadindex->SetProductPack(m_szIndexPath.c_str());
				if (!m_szSubIndexPath.empty())
				{
					loadindex->SetProductPack(m_szSubIndexPath.c_str());
				}
			}
			return true;
		}
	}
}
