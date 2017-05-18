#pragma once
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "PatchIndex.h"
#include "PatchFile.h"
#include "rapidxml_utils.hpp"

namespace vrv
{
	namespace patch
	{

		struct IndexInfo
		{
			std::tstring szIndexName;
			unsigned long dwCrc = 0;
			std::streamoff size = 0;
			void serialize(SF::Archive &ar)
			{
				try
				{
					if (ar.isRead())
					{
						SF::IStream *is = ar.getIstream();
						(*is) >> szIndexName >> dwCrc >> size;
					}
					else if (ar.isWrite())
					{
						SF::OStream* os = ar.getOstream();
						(*os) << szIndexName << dwCrc << size;
					}
				}
				catch (...)
				{
					ar.clearState();
				}

			}
		};

		typedef std::shared_ptr<IndexInfo> IndexInfoPtr;
		typedef std::vector<IndexInfoPtr> IndexInfoVec;
		struct PatchInfo
		{
			std::tstring szPatchName;
			std::tstring szKbId;
			std::tstring szMs;
			std::tstring szDescrip;
			std::tstring szPatchSize=_T("0");
			std::tstring szDatePublish;
			std::tstring szRank;
			std::tstring szUpdateId;
			std::tstring szMd5;
			std::tstring szLans;
			std::tstring szUrl;
			std::tstring MakeToolTipText()
			{
				std::tstringstream ss;
				ss << g_lang.GetText(10073) << szPatchName << std::endl
					<< _T("KB:") << szKbId << std::endl
					<< _T("MS:") << szMs << std::endl
					<< g_lang.GetText(10074) << szDescrip << std::endl
					<< g_lang.GetText(10075) << szPatchSize << std::endl
					<< g_lang.GetText(10076) << szDatePublish << std::endl
					<< g_lang.GetText(10077) << szRank << std::endl
					<< _T("UpdateID:") << szUpdateId << std::endl
					<< _T("MD5:") << szMd5 << std::endl
					<< g_lang.GetText(10078) << szLans << std::endl
					<< _T("URL:") << szUrl << std::endl;
				return ss.str();
			}

			void serialize(SF::Archive &ar)
			{
				try
				{
					if (ar.isRead())
					{
						SF::IStream *is = ar.getIstream();
						(*is) >> szPatchName
							>> szKbId
							>> szMs
							>> szDescrip
							>> szPatchSize
							>> szDatePublish
							>> szRank
							>> szUpdateId
							>> szMd5
							>> szLans
							>> szUrl;

					}
					else if (ar.isWrite())
					{
						SF::OStream* os = ar.getOstream();
						(*os) << szPatchName
							<< szKbId
							<< szMs
							<< szDescrip
							<< szPatchSize
							<< szDatePublish
							<< szRank
							<< szUpdateId
							<< szMd5
							<< szLans
							<< szUrl;
					}
				}
				catch (...)
				{
					ar.clearState();
				}

			}
		};
		typedef std::shared_ptr<PatchInfo>	PatchInfoPtr;
		typedef std::vector<PatchInfoPtr>	PatchInfoVec;
		typedef PatchInfoVec::iterator	_patchiter;

		struct PatchIndexVector
		{
			std::vector<PatchIndexPtr> patchindexes;
			int GetIndexCount()
			{
				int x = 0;
				for (size_t idx = 0; idx < patchindexes.size(); ++idx)
				{
					if (!patchindexes[idx]->m_szIndexPath.empty())
						++x;

					if (!patchindexes[idx]->m_szSubIndexPath.empty())
						++x;
				}
				return x;
			}
			typedef std::vector<PatchIndexPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<PatchIndexVector> PatchIndexVectorPtr;

		struct ProductsMap
		{
			std::map<std::tstring, PatchIndexVectorPtr> Products;
			typedef std::map<std::tstring, PatchIndexVectorPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<ProductsMap> ProductsMapPtr;

		struct FamiliesMap
		{
			std::map<std::tstring, ProductsMapPtr> ProductsFamily;
			std::map<std::tstring, ProductsMapPtr> LanguagesFamily;
			typedef std::map<std::tstring, ProductsMapPtr> _Myt;
			typedef std::map<std::tstring, ProductsMapPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<FamiliesMap> FamiliesMapPtr;

		struct PublishersMap
		{
			std::map<std::tstring, FamiliesMapPtr> Publishers;
			typedef std::map<std::tstring, FamiliesMapPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<PublishersMap> PublishersMapPtr;

		class CPatchBus
		{
		public:
			CPatchBus();
			~CPatchBus();
			int CalcIndexCount();
			bool analyze_main_index(IPackIndex *, std::tstring packindexPath);
			PublishersMapPtr GetPatchIndexMap()
			{
				return m_publishers;
			}

			void SetPackSha1(std::tstring &szpacksha)
			{
				m_szPackSha1 = szpacksha;
			}

			std::tstring GetPackSha1()
			{
				return m_szPackSha1;
			}
			bool AnalyzeIndex1xml(std::string &szIndex1xml, std::vector<PatchInfoPtr>& patches)
			{
				using namespace rapidxml;
				xml_document<TCHAR> doc;
				try
				{
					file<TCHAR> fp(szIndex1xml.c_str());
					doc.parse<0>(fp.data());
					auto root = doc.first_node();
					if (root)
					{
						auto child = root->first_node();
						while (child)
						{
							if (_tcsicmp(child->name(), _T("PATCHFILE")) == 0)
							{
								PatchInfoPtr patchptr = std::make_shared<PatchInfo>();
								auto subNode = child->first_node(_T("updateID"));
								if (subNode) patchptr->szUpdateId = subNode->value();

								//subNode = child->first_node("CRC");
								//if (subNode) patchptr->szMd5 = subNode->value();

								subNode = child->first_node(_T("PatchPath"));
								if (subNode) patchptr->szPatchName = subNode->value();

								patches.push_back(patchptr);
							}
							child = child->next_sibling();
						}
					}
					else
					{
						throw parse_error("Root Node is nullptr", NULL);
					}
				}
				catch (parse_error &)
				{
					return false;
				}

				return true;
			}


			vrv::patch::PatchInfoPtr GetPatchInfo(IPatchItem* pPatch);
			PatchIndexVectorPtr FindLanguageIndexVec();
			PatchIndexVectorPtr FindPatchIndexVecByProductName(std::tstring szProduct);
			PatchIndexVectorPtr GetAllPatchIndexes();
		private:
			void getPackages(IPackCompany *, FamiliesMapPtr);
			void getProductPacks(IPACKAGE *, ProductsMapPtr);
			void getPackFiles(IProductPack *, PatchIndexVectorPtr);
		private:
			PublishersMapPtr m_publishers;
			int m_iIndexCount;
			std::tstring m_szPackSha1;
		public:
			IndexInfoVec m_taskErrorIndex;
			PatchInfoVec m_taskErrorPatch;
		};


	}
}


extern vrv::patch::CPatchBus bus;
