#pragma once
#include <string>
#include <memory>
#include "Clibcurl.h"

namespace vrv
{
	namespace patch
	{
		class CPatchIndex
		{

			friend class CPatchBus;
		public:
			CPatchIndex();
			~CPatchIndex();
			bool load_product_index(ILoadIndex *loadindex);
			bool load_language_index(ILoadIndex *loadindex);

		public:
			std::string m_szIndexName;
			std::string m_szIndexPath;
			std::string m_szSubIndexPath;
			unsigned long dwIndexCrc;
			unsigned long dwSubIndexCrc;
			bool m_bExist;
		};

		typedef std::shared_ptr<CPatchIndex>  PatchIndexPtr;
	}
}


