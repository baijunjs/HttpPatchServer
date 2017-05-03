#include "stdafx.h"
#include "PatchBus.h"
#include <algorithm>

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


		//template <typename D>
		//bool CPatchBus::download_main_index(D &downloader)
		//{
		//	//TODO:
		//	//downloader.setprogressfun();
		//	return true;
		//}

		bool CPatchBus::analyze_main_index(IPackIndex *packindex)
		{
			assert(packindex);
			if (packindex == nullptr) return false;

			if (!packindex->LoadFile(szmain_save_path.c_str()))
				return false;

			IPatchPack* pack = packindex->GetPatchPack();
			if (pack == nullptr) return false;

			m_patchIndexes.clear();

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
				bool blanuage = false;
				if (_stricmp(szPackage.c_str(), "Languages") == 0)
					blanuage = true;

				int count = pPackage->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IProductPack *pProduct = pPackage->GetItem(loop);
					getPackFiles(pProduct, blanuage);
				}
			}
		}

		void CPatchBus::getPackFiles(IProductPack *pProductPack, bool blanuage)
		{
			if (pProductPack)
			{
				std::string szProduct = pProductPack->GetName();
				std::transform(szProduct.begin(), szProduct.end(), szProduct.begin(), toupper);
				PatchIndexCIter finditer = m_patchIndexes.find(szProduct);
				if (finditer == m_patchIndexes.end())
				{
					auto pairib = m_patchIndexes.insert(std::make_pair(szProduct, PatchIndexVector()));
					finditer = pairib.first;
				}

				PatchIndexVector & patchindexvec = const_cast<PatchIndexVector&>(finditer->second);

				int count = pProductPack->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					PatchIndexPtr packinfo = std::make_shared<CPatchIndex>();
					IPackFile *pPackFile = pProductPack->GetItem(loop);
					packinfo->m_szIndexName = pPackFile->GetName();
					packinfo->m_szIndexPath = pPackFile->GetPath();
					packinfo->m_szSubIndexPath = pPackFile->GetSubPath();
					packinfo->dwIndexCrc = pPackFile->GetCrc();
					packinfo->dwSubIndexCrc = pPackFile->GetSubCrc();
					packinfo->m_bExist = pPackFile->IsExist();
					packinfo->m_bLanguage = blanuage;
					patchindexvec.push_back(packinfo);
				}
			}
		}

		bool CPatchBus::loadLanuageIndex(ILoadIndex *loadobject)
		{
			//TODO:获取选择的语言列表
			std::string lanuages = "en;zhcn";
			char *token = nullptr, *next = nullptr;
			token = strtok_s(const_cast<char*>(lanuages.c_str()), ";", &next);
			while (token)
			{
				std::string szLanuage = token;
				std::transform(szLanuage.begin(), szLanuage.end(), szLanuage.begin(), toupper);
				PatchIndexCIter finditer = m_patchIndexes.find(szLanuage);
				if (finditer != m_patchIndexes.end())
				{
					for (size_t index = 0; index < finditer->second.size(); ++index)
					{
						if (finditer->second[index]->m_bLanguage == true)
						{
							std::string szIndexName = finditer->second[index]->m_szIndexPath;
							//索引目录
							std::string szIndexPath = R"(E:\Project\svn\HttpPatchDownLoader\Tools\)";
							std::string szlocalIndex = szIndexPath + szIndexName;
							loadobject->SetLanguagePack(szlocalIndex.c_str());
						}
					}
				}

				token = strtok_s(NULL, ";", &next);
			}
			return true;
		}

		bool CPatchBus::loadProductIndex(ILoadIndex *loadobject)
		{
			//TODO:获取选择的产品列表
			std::string products = "Win7;Win8;";

			char *token = nullptr, *next = nullptr;
			token = strtok_s(const_cast<char*>(products.c_str()), ";", &next);
			while (token)
			{
				std::string szProduct = token;
				std::transform(szProduct.begin(), szProduct.end(), szProduct.begin(), toupper);
				PatchIndexCIter finditer = m_patchIndexes.find(szProduct);
				if (finditer != m_patchIndexes.end())
				{
					for (size_t index = 0; index < finditer->second.size(); ++index)
					{
						if (finditer->second[index]->m_bLanguage == false)
						{
							std::string szIndexName = finditer->second[index]->m_szIndexPath;
							std::string szSubIndexName = finditer->second[index]->m_szSubIndexPath;
							//索引目录
							std::string szIndexPath = R"(E:\Project\svn\HttpPatchDownLoader\Tools\)";
							std::string szlocalIndex = szIndexPath + szIndexName;
							loadobject->SetProductPack(szlocalIndex.c_str());
							if (!szSubIndexName.empty())
							{
								std::string szlocalSubIndex = szIndexPath + szSubIndexName;
								loadobject->SetProductPack(szlocalSubIndex.c_str());
							}
						}
					}
				}

				token = strtok_s(NULL, ";", &next);
			}
			return true;
		}

		bool CPatchBus::fetchPatchFile(ILoadIndex *loadobject)
		{
			TOptionCondition option;
			option.nUseIntranetPatch = 0;
			option.nMinLoad = 100;

			loadobject->SetOption(option);
			DWORD hResult = loadobject->LoadFile();
			if (S_OK != hResult) return false;

			INT nPatchCount = loadobject->GetCount();

			for (INT nCountIndex = 0; nCountIndex < nPatchCount; ++nCountIndex)
			{
				IPatchItem *pItem = loadobject->GetPatchByIndex(nCountIndex);
				if (pItem)
				{
					PatchFilePtr patch = std::make_shared<CPatchFile>();
					patch->szPatchName = pItem->GetFileName();
					patch->szPatchKB = pItem->GetPatchKBID();
					patch->szPatchMS = pItem->GetBulletins();
					patch->szDescription = pItem->GetLeakDescription();
					patch->szPatchSize = pItem->GetPatchSize();
					patch->szDatePublish = pItem->GetPublishTime();
					patch->szPatchRank = pItem->GetPatchLevel();
					patch->szUpdateID = pItem->GetUpdateID();
					patch->szMD5 = pItem->GetPatchMD5();
					patch->szLanguage = pItem->GetLanguages();
					patch->szPatchURL = pItem->GetUrl();
					m_patches.push_back(patch);
				}
			}
			return true;
		}
	}
}

