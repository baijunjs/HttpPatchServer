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


__interface IDownload
{

	bool setproxy(std::string&, std::string&, std::string&, std::string&);

	bool setUpRate(unsigned long ulrate);

	bool setDownRate(unsigned long ulrate);

	bool downloadfile(std::string&, std::string&);

	int startdownload();

	int stopdownload();

	int pausedownload();

	int continuedownload();
}; 
