#pragma once
#include <string>
#include <map>
#include <vector>
#include "PatchIndex.h"
#include "PatchFile.h"

namespace vrv
{
	namespace patch
	{

		typedef std::vector<PatchIndexPtr> PatchIndexVector;
		typedef std::map<std::string, PatchIndexVector> PatchIndexMap;
		typedef PatchIndexMap::const_iterator	PatchIndexCIter;
		typedef std::vector<PatchFilePtr>		PatchFileVec;
		class CPatchBus
		{
		public:
			CPatchBus();
			~CPatchBus();
			template <typename D>
			bool download_main_index(D& d)
			{
#ifdef _DEBUG
				szmain_index_url = "http://www.vrvsoft.com/update/patch/newpatch/PackIndex.dat";
				szmain_save_path = R"(E:\Project\svn\HttpPatchDownLoader\Tools\PackIndex.dat)";
#endif
				std::string sztmplocalpath = szmain_save_path + "~";
				d.setDownRate(100 * 1024);
				if (!d.downloadfile(szmain_index_url, sztmplocalpath))
					return false;

				MoveFileEx(sztmplocalpath.c_str(), szmain_save_path.c_str(), MOVEFILE_REPLACE_EXISTING);
				return true;
			}

			bool analyze_main_index(IPackIndex *);

			/*template <typename D>
			bool download_sub_index()
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
							patchinfo->download_sub_index<D>();
						}
					}
				}
				return true;
			}*/

			bool loadProductIndex(ILoadIndex *);
			bool loadLanuageIndex(ILoadIndex *);
			bool fetchPatchFile(ILoadIndex *);

		private:
			void getPackages(IPackCompany *);
			void getProductPacks(IPACKAGE *);
			void getPackFiles(IProductPack *, bool);
		private:
			std::string szmain_index_url;
			std::string szmain_save_path;
			PatchIndexMap m_patchIndexes;
			PatchFileVec  m_patches;
		};
	}
}


