#pragma once
#include "IDownload.h"



typedef size_t(*pfn_write_callback)(char *pbuf, size_t size, size_t stNum, void * pData);
typedef int(*pfn_progress_callback)(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

class Clibcurl :
	public IDownload
{
public:
	Clibcurl() noexcept(false);
	virtual ~Clibcurl();

public:

	bool setproxy(std::string&, std::string&, std::string&, std::string&);

	bool setUpRate(unsigned long ulrate);

	bool setDownRate(unsigned long ulrate);

	bool downloadfile(std::string& szurl, std::string& szsavepath);

	int startdownload();

	int stopdownload();

	int pausedownload();

	int continuedownload();

private:
	bool getfilesize(std::string& szurl, size_t& size);

	bool setprogressfun(pfn_progress_callback progressfun, void* param);

	bool setwritefun(pfn_write_callback writefun, void* param);
private:
	CURL *m_pCURL;
	task_status st;
	HANDLE m_hEvt;
	//HANDLE m_hExit;
};

