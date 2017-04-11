#pragma once
#include <string>
#include <memory>


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
			template <typename D=IDownload>
			bool download_sub_index(D &);
			bool analyze_sub_index(ILoadIndex *loadindex);

		private:
			std::string m_szIndexName;
			std::string m_szIndexPath;
			std::string m_szSubIndexPath;
			unsigned long dwIndexCrc;
			unsigned long dwSubIndexCrc;
			bool m_bExist;
			bool m_bLanguage;
		};

		typedef std::shared_ptr<CPatchIndex>  PatchIndexPtr;
	}
}


