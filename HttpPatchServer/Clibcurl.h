#pragma once
#include "IDownload.h"

class Clibcurl :
	public IDownload
{
public:
	Clibcurl() noexcept(false);
	virtual ~Clibcurl();

public:
	bool setprogressfun(pfn_progress_callback progressfun, void* param);

	bool setwritefun(pfn_write_callback writefun, void* param);

	bool setproxy(std::string, std::string, std::string, std::string);

	bool setUpRate(unsigned long ulrate);

	bool setDownRate(unsigned long ulrate);

	bool downloadfile(std::string szurl, std::string szsavepath);

	int startdownload();

	int stopdownload();

	int pausedownload();

	int continuedownload();

private:
	bool getfilesize(std::string& szurl, size_t& size);

private:
	CURL *m_pCURL;
	task_status st;
	HANDLE m_hEvt;
	//HANDLE m_hExit;
};

