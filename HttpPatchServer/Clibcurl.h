#pragma once

enum Task_Status
{
	DOWNLOAD_ERROR = -1,			//下载错误
	DOWNLOAD_STOPPED,				//已停止
	DOWNLOAD_STARTED,				//启动
	DOWNLOAD_RUNNING,				//正在运行
	DOWNLOAD_DONE,					//下载完成
};


typedef size_t (*_TyWrittenCallback)(char *pbuf, size_t size, size_t stNum, void * pData);
typedef int (*_TyProgressCallback)(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);

class Curl
{
public:
	Curl() noexcept(false);
	virtual ~Curl();

public:

	void SetProxy(std::string, std::string, std::string, std::string);

	void SetUploadSpeed(long ulrate);

	void SetDownloadSpeed(long ulrate);

	void SetUrlFile(std::string szUrl, std::string szFile);

	long StartDownload();

	long StopDownload();

	long GetFileSize(size_t &size);

	void SetProgressCallback(_TyProgressCallback progressfun, HWND hWnd, WPARAM wparam, LPARAM lparam);

	void SetWriteCallback(_TyWrittenCallback writefun, void* param);

	Task_Status GetTaskStatus()
	{
		return m_status;
	}
private:
	CURL *m_pCURL;
	Task_Status m_status;
	_TyProgressCallback m_pProgress;
	void *m_pProgressParam;
	_TyWrittenCallback m_pWritten;
	void *m_pWrittenParam;
	std::string m_szProxyip;
	std::string m_szProxyport;
	std::string m_szProxyuser;
	std::string m_szProxypwd;
	long m_lupspeed;
	long m_ldownspeed;
	std::string m_szUrl;
	std::string m_szFile;

public:
	std::streamoff m_curLength;
	HWND m_hWnd;
	WPARAM m_wparam;
	LPARAM m_lparam;
	size_t m_filesize;

};

