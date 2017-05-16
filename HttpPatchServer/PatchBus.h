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
			std::string szIndexName;
			unsigned long dwCrc = 0;
			size_t size = 0;
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
			std::string szPatchName;
			std::string szKbId;
			std::string szMs;
			std::string szDescrip;
			std::string szPatchSize="0";
			std::string szDatePublish;
			std::string szRank;
			std::string szUpdateId;
			std::string szMd5;
			std::string szLans;
			std::string szUrl;
			std::string MakeToolTipText()
			{
				std::stringstream ss;
				ss << "补丁名称:" << szPatchName << std::endl
					<< "KB:" << szKbId << std::endl
					<< "MS:" << szMs << std::endl
					<< "描述:" << szDescrip << std::endl
					<< "大小:" << szPatchSize << std::endl
					<< "日期:" << szDatePublish << std::endl
					<< "等级:" << szRank << std::endl
					<< "UpdateID:" << szUpdateId << std::endl
					<< "MD5:" << szMd5 << std::endl
					<< "语言:" << szLans << std::endl
					<< "URL:" << szUrl << std::endl;
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
			std::map<std::string, PatchIndexVectorPtr> Products;
			typedef std::map<std::string, PatchIndexVectorPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<ProductsMap> ProductsMapPtr;

		struct FamiliesMap
		{
			std::map<std::string, ProductsMapPtr> ProductsFamily;
			std::map<std::string, ProductsMapPtr> LanguagesFamily;
			typedef std::map<std::string, ProductsMapPtr> _Myt;
			typedef std::map<std::string, ProductsMapPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<FamiliesMap> FamiliesMapPtr;

		struct PublishersMap
		{
			std::map<std::string, FamiliesMapPtr> Publishers;
			typedef std::map<std::string, FamiliesMapPtr>::iterator _iterator;
		};
		typedef std::shared_ptr<PublishersMap> PublishersMapPtr;

		class CPatchBus
		{
		public:
			CPatchBus();
			~CPatchBus();
			int CalcIndexCount();
			bool analyze_main_index(IPackIndex *, std::string packindexPath);
			PublishersMapPtr GetPatchIndexMap()
			{
				return m_publishers;
			}

			void SetPackSha1(std::string &szpacksha)
			{
				m_szPackSha1 = szpacksha;
			}

			std::string GetPackSha1()
			{
				return m_szPackSha1;
			}
			bool AnalyzeIndex1xml(std::string &szIndex1xml, std::vector<PatchInfoPtr>& patches)
			{
				using namespace rapidxml;
				xml_document<> doc;
				try
				{
					file<> fp(szIndex1xml.c_str());
					doc.parse<0>(fp.data());
					auto root = doc.first_node();
					if (root)
					{
						auto child = root->first_node();
						while (child)
						{
							if (_stricmp(child->name(), "PATCHFILE") == 0)
							{
								PatchInfoPtr patchptr = std::make_shared<PatchInfo>();
								auto subNode = child->first_node("updateID");
								if (subNode) patchptr->szUpdateId = subNode->value();

								//subNode = child->first_node("CRC");
								//if (subNode) patchptr->szMd5 = subNode->value();

								subNode = child->first_node("PatchPath");
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
				catch (parse_error & e)
				{
					return false;
				}

				return true;
			}


			vrv::patch::PatchInfoPtr GetPatchInfo(IPatchItem* pPatch);
			PatchIndexVectorPtr FindLanguageIndexVec();
			PatchIndexVectorPtr FindPatchIndexVecByProductName(std::string szProduct);
			PatchIndexVectorPtr GetAllPatchIndexes();
		private:
			void getPackages(IPackCompany *, FamiliesMapPtr);
			void getProductPacks(IPACKAGE *, ProductsMapPtr);
			void getPackFiles(IProductPack *, PatchIndexVectorPtr);
		private:
			PublishersMapPtr m_publishers;
			int m_iIndexCount;
			std::string m_szPackSha1;
		public:
			IndexInfoVec m_taskErrorIndex;
			PatchInfoVec m_taskErrorPatch;
		};


	}
}


extern vrv::patch::CPatchBus bus;
