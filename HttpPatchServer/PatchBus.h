#pragma once
#include <string>
#include <map>
#include <vector>
#include "PatchIndex.h"

namespace vrv
{
	namespace patch
	{

		typedef std::vector<PatchIndexPtr> PatchIndexVector;
		typedef std::map<std::string, PatchIndexVector> PatchIndexMap;
		typedef PatchIndexMap::const_iterator	PatchIndexCIter;
		class CPatchBus
		{
		public:
			CPatchBus();
			~CPatchBus();
			template <typename D = IDownload>
			bool download_main_index(D &);
			bool analyze_main_index(IPackIndex *);
			template <typename D = IDownload>
			bool download_sub_index();


		private:
			void getPackages(IPackCompany *);
			void getProductPacks(IPACKAGE *);
			void getPackFiles(IProductPack *, PatchIndexVector&);

		private:
			std::string szmain_index_url;
			std::string szmain_save_path;
			PatchIndexMap m_patchIndexes;

		};
	}
}


