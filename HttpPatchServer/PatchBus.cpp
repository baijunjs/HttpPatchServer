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

		bool CPatchBus::analyze_main_index(IPackIndex *packindex, std::string szPackIndex)
		{
			if (packindex == nullptr)
				return false;

			if (!packindex->LoadFile(szPackIndex.c_str()))
			{
				return false;
			}

			IPatchPack* pack = packindex->GetPatchPack();
			if (pack == nullptr) return false;

			m_iIndexCount = 0;
			m_publishers = std::make_shared<PublishersMap>();
			std::string szPackName = pack->GetName();
			int count = pack->GetCount();
			for (int index = 0; index < count; index++)
			{
				IPackCompany* pCompany = pack->GetItem(index);
				if (pCompany)
				{
					std::string szCompany = pCompany->GetName();
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
						std::string szPackage = pPackage->GetName();
						FamiliesMap::_iterator iter;
						if (_stricmp(szPackage.c_str(), "Languages") == 0)
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
						std::string szProduct = pProduct->GetName();
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
					packinfo->m_szIndexName = pPackFile->GetName();
					packinfo->m_szIndexPath = pPackFile->GetPath();
					packinfo->m_szSubIndexPath = pPackFile->GetSubPath();
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


		PatchIndexVectorPtr CPatchBus::FindPatchIndexVecByProductName(std::string szProduct)
		{
			vrv::patch::PublishersMap::_iterator iter = m_publishers->Publishers.begin();
			for (; iter != m_publishers->Publishers.end(); ++iter)
			{
				std::string szPublisher = iter->first;
				vrv::patch::FamiliesMapPtr families = iter->second;
				vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
				for (; _iter != families->ProductsFamily.end(); ++_iter)
				{
					std::string szFamily = _iter->first;
					vrv::patch::ProductsMapPtr products = _iter->second;
					vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
					for (; _iter_ != products->Products.end(); ++_iter_)
					{
						std::string szProductName = _iter_->first;
						if (szProductName == szProduct)
							return _iter_->second;
					}
				}
			}
			return std::make_shared<PatchIndexVector>();
		}

		PatchIndexVectorPtr CPatchBus::FindLanguageIndexVec()
		{
			PatchIndexVectorPtr PatchIndexes = std::make_shared<PatchIndexVector>();
			vrv::patch::PublishersMap::_iterator iter = m_publishers->Publishers.begin();
			for (; iter != m_publishers->Publishers.end(); ++iter)
			{
				std::string szPublisher = iter->first;
				vrv::patch::FamiliesMapPtr families = iter->second;
				vrv::patch::FamiliesMap::_iterator _iter = families->LanguagesFamily.begin();
				for (; _iter != families->LanguagesFamily.end(); ++_iter)
				{
					std::string szFamily = _iter->first;
					vrv::patch::ProductsMapPtr products = _iter->second;
					vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
					for (; _iter_ != products->Products.end(); ++_iter_)
					{
						std::string szProductName = _iter_->first;
						PatchIndexVectorPtr tmp = _iter_->second;
						PatchIndexes->patchindexes.insert(PatchIndexes->patchindexes.end(),
							tmp->patchindexes.begin(), tmp->patchindexes.end());
					}
				}
			}
			return PatchIndexes;
		}

		vrv::patch::PatchInfoPtr CPatchBus::GetPatchInfo(IPatchItem* pPatch)
		{
			vrv::patch::PatchInfoPtr patch = std::make_shared<vrv::patch::PatchInfo>();
			patch->szPatchName = pPatch->GetFileName();
			patch->szKbId = pPatch->GetPatchKBID();
			patch->szMs = pPatch->GetBulletins();
			patch->szDescrip = pPatch->GetLeakDescription();
			patch->szPatchSize = pPatch->GetPatchSize();
			patch->szDatePublish = pPatch->GetPublishTime();
			patch->szRank = pPatch->GetPatchLevel();
			patch->szUpdateId = pPatch->GetUpdateID();
			patch->szMd5 = pPatch->GetPatchMD5();
			patch->szLans = pPatch->GetLanguages();
			patch->szUrl = pPatch->GetUrl();
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
						std::string szPublisher = iter->first;
						vrv::patch::FamiliesMapPtr families = iter->second;
						vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
						for (; _iter != families->ProductsFamily.end(); ++_iter)
						{
							std::string szFamily = _iter->first;
							vrv::patch::ProductsMapPtr products = _iter->second;
							vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
							for (; _iter_ != products->Products.end(); ++_iter_)
							{
								std::string szProductName = _iter_->first;
								PatchIndexVectorPtr tmp = _iter_->second;
								PatchIndexes->patchindexes.insert(PatchIndexes->patchindexes.end(),
									tmp->patchindexes.begin(), tmp->patchindexes.end());
							}
						}

						_iter = families->LanguagesFamily.begin();
						for (; _iter != families->LanguagesFamily.end(); ++_iter)
						{
							std::string szFamily = _iter->first;
							vrv::patch::ProductsMapPtr products = _iter->second;
							vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
							for (; _iter_ != products->Products.end(); ++_iter_)
							{
								std::string szProductName = _iter_->first;
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

