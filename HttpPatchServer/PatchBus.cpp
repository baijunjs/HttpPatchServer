#include "stdafx.h"
#include "PatchBus.h"
#include <algorithm>
#include <regex>


vrv::patch::CPatchBus bus;

namespace vrv
{
	namespace patch
	{
		CPatchBus::CPatchBus()
		{
			m_iIndexCount = 0;
		}


		CPatchBus::~CPatchBus()
		{
		}

		bool CPatchBus::analyze_main_index(IPackIndex *packindex, std::tstring szPackIndex)
		{
			if (packindex == nullptr)
				return false;

			if (!packindex->LoadFile((const char*)_bstr_t(szPackIndex.c_str())))
			{
				return false;
			}

			IPatchPack* pack = packindex->GetPatchPack();
			if (pack == nullptr) return false;

			m_iIndexCount = 0;
			m_publishers = std::make_shared<PublishersMap>();
			std::tstring szPackName = (const TCHAR*)_bstr_t(pack->GetName());
			int count = pack->GetCount();
			for (int index = 0; index < count; index++)
			{
				IPackCompany* pCompany = pack->GetItem(index);
				if (pCompany)
				{
					std::tstring szCompany = (const TCHAR*)_bstr_t(pCompany->GetName());
					PublishersMap::_iterator iter = m_publishers->Publishers.find(szCompany);
					if (iter == m_publishers->Publishers.end())
					{
						std::pair<PublishersMap::_iterator, bool> rpair = m_publishers->Publishers.insert(std::make_pair(szCompany, std::make_shared<FamiliesMap>()));
						iter = rpair.first;
					}
					getPackages(pCompany, iter->second);
				}

			}

			return true;
		}

		void CPatchBus::getPackages(IPackCompany *pPackCompany, FamiliesMapPtr family)
		{
			if (pPackCompany)
			{
				int count = pPackCompany->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IPACKAGE *pPackage = pPackCompany->GetItem(loop);
					if (pPackage)
					{
						std::tstring szPackage = (const TCHAR*)_bstr_t(pPackage->GetName());
						FamiliesMap::_iterator iter;
						if (_tcsicmp(szPackage.c_str(), _T("Languages")) == 0)
						{
							iter = family->LanguagesFamily.find(szPackage);
							if (iter == family->LanguagesFamily.end())
							{
								std::pair<FamiliesMap::_iterator, bool> rpair =
									family->LanguagesFamily.insert(std::make_pair(szPackage, std::make_shared<ProductsMap>()));
								iter = rpair.first;
							}
						}
						else
						{
							iter = family->ProductsFamily.find(szPackage);
							if (iter == family->ProductsFamily.end())
							{
								std::pair<FamiliesMap::_iterator, bool> rpair =
									family->ProductsFamily.insert(std::make_pair(szPackage, std::make_shared<ProductsMap>()));
								iter = rpair.first;
							}
						}

						getProductPacks(pPackage, iter->second);
					}
				}
			}
		}

		void CPatchBus::getProductPacks(IPACKAGE *pPackage, ProductsMapPtr products)
		{
			if (pPackage)
			{
				int count = pPackage->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					IProductPack *pProduct = pPackage->GetItem(loop);
					if (pProduct)
					{
						std::tstring szProduct = (const TCHAR*)_bstr_t(pProduct->GetName());
						ProductsMap::_iterator iter = products->Products.find(szProduct);
						if (iter == products->Products.end())
						{
							std::pair<ProductsMap::_iterator, bool> rpair =
								products->Products.insert(std::make_pair(szProduct, std::make_shared<PatchIndexVector>()));
							iter = rpair.first;
						}
						getPackFiles(pProduct, iter->second);
					}
				}
			}
		}

		void CPatchBus::getPackFiles(IProductPack *pProductPack, PatchIndexVectorPtr patchindexvec)
		{
			if (pProductPack)
			{
				int count = pProductPack->GetCount();
				for (int loop = 0; loop < count; loop++)
				{
					m_iIndexCount++;
					PatchIndexPtr packinfo = std::make_shared<CPatchIndex>();
					IPackFile *pPackFile = pProductPack->GetItem(loop);
					packinfo->m_szIndexName = (const TCHAR*)_bstr_t(pPackFile->GetName());
					packinfo->m_szIndexPath = (const TCHAR*)_bstr_t(pPackFile->GetPath());
					packinfo->m_szSubIndexPath = (const TCHAR*)_bstr_t(pPackFile->GetSubPath());
					packinfo->dwIndexCrc = pPackFile->GetCrc();
					packinfo->dwSubIndexCrc = pPackFile->GetSubCrc();
					packinfo->m_bExist = pPackFile->IsExist();
					patchindexvec->patchindexes.push_back(packinfo);
				}
			}
		}

		int CPatchBus::CalcIndexCount()
		{
			return m_iIndexCount;
		}


		PatchIndexVectorPtr CPatchBus::FindPatchIndexVecByProductName(std::tstring szProduct)
		{
			if (m_publishers)
			{
				vrv::patch::PublishersMap::_iterator iter = m_publishers->Publishers.begin();
				for (; iter != m_publishers->Publishers.end(); ++iter)
				{
					std::tstring szPublisher = iter->first;
					vrv::patch::FamiliesMapPtr families = iter->second;
					vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
					for (; _iter != families->ProductsFamily.end(); ++_iter)
					{
						std::tstring szFamily = _iter->first;
						vrv::patch::ProductsMapPtr products = _iter->second;
						vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
						for (; _iter_ != products->Products.end(); ++_iter_)
						{
							std::tstring szProductName = _iter_->first;
							if (szProductName == szProduct)
								return _iter_->second;
						}
					}
				}
			}
			
			return std::make_shared<PatchIndexVector>();
		}

		PatchIndexVectorPtr CPatchBus::FindLanguageIndexVec()
		{
			PatchIndexVectorPtr PatchIndexes = std::make_shared<PatchIndexVector>();
			if (m_publishers)
			{
				vrv::patch::PublishersMap::_iterator iter = m_publishers->Publishers.begin();
				for (; iter != m_publishers->Publishers.end(); ++iter)
				{
					std::tstring szPublisher = iter->first;
					vrv::patch::FamiliesMapPtr families = iter->second;
					vrv::patch::FamiliesMap::_iterator _iter = families->LanguagesFamily.begin();
					for (; _iter != families->LanguagesFamily.end(); ++_iter)
					{
						std::tstring szFamily = _iter->first;
						vrv::patch::ProductsMapPtr products = _iter->second;
						vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
						for (; _iter_ != products->Products.end(); ++_iter_)
						{
							std::tstring szProductName = _iter_->first;
							PatchIndexVectorPtr tmp = _iter_->second;
							PatchIndexes->patchindexes.insert(PatchIndexes->patchindexes.end(),
								tmp->patchindexes.begin(), tmp->patchindexes.end());
						}
					}
				}
			}
			
			return PatchIndexes;
		}

		vrv::patch::PatchInfoPtr CPatchBus::GetPatchInfo(IPatchItem* pPatch)
		{
			vrv::patch::PatchInfoPtr patch = std::make_shared<vrv::patch::PatchInfo>();
			patch->szPatchName = _bstr_t(pPatch->GetFileName());
			patch->szKbId = _bstr_t(pPatch->GetPatchKBID());
			patch->szMs = _bstr_t(pPatch->GetBulletins());
			patch->szDescrip = _bstr_t(pPatch->GetLeakDescription());
			patch->szPatchSize = _bstr_t(pPatch->GetPatchSize());
			patch->szDatePublish = _bstr_t(pPatch->GetPublishTime());
			patch->szRank = _bstr_t(pPatch->GetPatchLevel());
			patch->szUpdateId = _bstr_t(pPatch->GetUpdateID());
			patch->szMd5 = _bstr_t(pPatch->GetPatchMD5());
			patch->szLans = _bstr_t(pPatch->GetLanguages());
			patch->szUrl = _bstr_t(pPatch->GetUrl());
			return patch;
		}


		PatchIndexVectorPtr CPatchBus::GetAllPatchIndexes()
		{
			PatchIndexVectorPtr PatchIndexes = std::make_shared<PatchIndexVector>();
			if (m_publishers)
			{
				vrv::patch::PublishersMap::_iterator iter = m_publishers->Publishers.begin();
				if (m_publishers)
				{
					for (; iter != m_publishers->Publishers.end(); ++iter)
					{
						std::tstring szPublisher = iter->first;
						vrv::patch::FamiliesMapPtr families = iter->second;
						vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
						for (; _iter != families->ProductsFamily.end(); ++_iter)
						{
							std::tstring szFamily = _iter->first;
							vrv::patch::ProductsMapPtr products = _iter->second;
							vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
							for (; _iter_ != products->Products.end(); ++_iter_)
							{
								std::tstring szProductName = _iter_->first;
								PatchIndexVectorPtr tmp = _iter_->second;
								PatchIndexes->patchindexes.insert(PatchIndexes->patchindexes.end(),
									tmp->patchindexes.begin(), tmp->patchindexes.end());
							}
						}

						_iter = families->LanguagesFamily.begin();
						for (; _iter != families->LanguagesFamily.end(); ++_iter)
						{
							std::tstring szFamily = _iter->first;
							vrv::patch::ProductsMapPtr products = _iter->second;
							vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
							for (; _iter_ != products->Products.end(); ++_iter_)
							{
								std::tstring szProductName = _iter_->first;
								PatchIndexVectorPtr tmp = _iter_->second;
								PatchIndexes->patchindexes.insert(PatchIndexes->patchindexes.end(),
									tmp->patchindexes.begin(), tmp->patchindexes.end());
							}
						}

					}
				}
			}
			return PatchIndexes;
		}
	}
}

