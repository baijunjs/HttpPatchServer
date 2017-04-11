#include "stdafx.h"
#include "PatchBus.h"

namespace vrv
{
	namespace patch
	{
		CPatchBus::CPatchBus()
		{
		}


		CPatchBus::~CPatchBus()
		{
		}

		template <typename D>
		bool CPatchBus::download_main_index(D &downloader)
		{
			//TODO:
			//downloader.setprogressfun();
		}

		bool CPatchBus::analyze_main_index(IPackIndex *packindex)
		{
			assert(packindex);
			if (packindex == nullptr)
			{
				return false;
			}

			if (!packindex->LoadFile(szmain_save_path.c_str()))
			{
				return false;
			}

			IPatchPack* pack = packindex->GetPatchPack();
			if (pack == nullptr)
			{
				return false;
			}

			int count = pack->GetCount();
			for (int index = 0; index < count; index++)
			{
				IPackCompany* pCompany = pack->GetItem(index);
				getPackages(pCompany);
			}

			return true;
		}

		void CPatchBus::getPackages(IPackCompany *pPackCompany)
		{
			if (pPackCompany)
			{
				std::string szCompany = pPackCompany->GetName();
				int count = pPackCompany->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IPACKAGE *pPackage = pPackCompany->GetItem(loop);
					getProductPacks(pPackage);
				}
			}
		}

		void CPatchBus::getProductPacks(IPACKAGE *pPackage)
		{
			if (pPackage)
			{
				std::string szPackage = pPackage->GetName();

				PatchIndexCIter finditer = m_patchIndexes.find(szPackage);
				if (finditer == m_patchIndexes.end())
				{
					auto pairib = m_patchIndexes.insert(std::make_pair(szPackage, PatchIndexVector()));
					finditer = pairib.first;
				}

				const PatchIndexVector & patchindexvec = finditer->second;
				int count = pPackage->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IProductPack *pProduct = pPackage->GetItem(loop);
					getPackFiles(pProduct, const_cast<PatchIndexVector &>(patchindexvec));
				}
			}
		}

		void CPatchBus::getPackFiles(IProductPack *pProductPack, PatchIndexVector& patchindexvec)
		{
			if (pProductPack)
			{
				std::string szPackage = pProductPack->GetName();
				int count = pProductPack->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IPackFile *pPackFile = pProductPack->GetItem(loop);
					PatchIndexPtr packinfo = std::make_shared<CPatchIndex>();
					packinfo->m_szIndexName = pPackFile->GetName();
					packinfo->m_szIndexPath = pPackFile->GetPath();
					packinfo->m_szSubIndexPath = pPackFile->GetSubPath();
					packinfo->dwIndexCrc = pPackFile->GetCrc();
					packinfo->dwSubIndexCrc = pPackFile->GetSubCrc();
					packinfo->m_bExist = pPackFile->IsExist();
					patchindexvec.push_back(packinfo);
				}
			}
		}

		template <typename D>
		bool CPatchBus::download_sub_index()
		{
			PatchIndexCIter itb = m_patchIndexes.begin();
			for (; itb != m_patchIndexes.end(); ++itb)
			{
				const PatchIndexVector &patchindexvec = itb->second;

				for (size_t index = 0; index < patchindexvec.size(); ++index)
				{
					PatchIndexPtr patchinfo = patchindexvec[index];
					if (patchinfo)
					{
						D *downloader = new D();
						patchinfo->download_sub_index(downloader);
					}
				}
			}
			return true;
		}
	}
}

