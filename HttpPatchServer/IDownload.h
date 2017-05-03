#pragma once
#include <functional>



enum task_status
{
	DOWNLOAD_ERROR=-1,				//���ش���
	DOWNLOAD_STOP_PENDING=0,		//����ֹͣ
	DOWNLOAD_STOPPED,				//��ֹͣ
	DOWNLOAD_START_PENDING,			//��������
	DOWNLOAD_STARTED,				//����
	DOWNLOAD_RUNING,				//��������
	DOWNLOAD_PAUSE_PENDING,			//������ͣ
	DOWNLOAD_PAUSED,				//����ͣ
	DOWNLOAD_DONE,					//�������
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
