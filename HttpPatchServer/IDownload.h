#pragma once
#include <functional>



enum task_status
{
	DOWNLOAD_ERROR=-1,				//下载错误
	DOWNLOAD_STOP_PENDING=0,		//正在停止
	DOWNLOAD_STOPPED,				//已停止
	DOWNLOAD_START_PENDING,			//正在启动
	DOWNLOAD_STARTED,				//启动
	DOWNLOAD_RUNING,				//正在运行
	DOWNLOAD_PAUSE_PENDING,			//正在暂停
	DOWNLOAD_PAUSED,				//已暂停
	DOWNLOAD_DONE,					//下载完成
};


typedef size_t ( *pfn_write_callback)(char *pbuf, size_t size, size_t stNum, void * pData);
typedef int ( * pfn_progress_callback)(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

__interface IDownload
{
	bool setprogressfun(pfn_progress_callback, void*);

	bool setwritefun(pfn_write_callback, void*);

	bool setproxy(std::string, std::string, std::string, std::string);

	bool setUpRate(unsigned long ulrate);

	bool setDownRate(unsigned long ulrate);

	bool startdownload(std::string, std::string);

	int startdownload();

	int stopdownload();

	int pausedownload();

	int continuedownload();
}; 
