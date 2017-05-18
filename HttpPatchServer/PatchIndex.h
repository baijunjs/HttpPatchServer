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
			std::tstring m_szIndexName;
			std::tstring m_szIndexPath;
			std::tstring m_szSubIndexPath;
			unsigned long dwIndexCrc;
			unsigned long dwSubIndexCrc;
			bool m_bExist;
		};

		typedef std::shared_ptr<CPatchIndex>  PatchIndexPtr;
	}
}


