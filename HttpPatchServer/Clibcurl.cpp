#include "stdafx.h"
#include <exception>
#include <fstream>
#include "Clibcurl.h"


size_t write_callback(char *pbuf, size_t size, size_t stNum, void * pData)
{
	std::ofstream *pfile = (std::ofstream *)pData;
	if (pfile)
	{
		pfile->write(pbuf, size * stNum);
		return size * stNum;
	}
	return 0;
}


Clibcurl::Clibcurl() noexcept(false)
{
	m_pCURL = curl_easy_init();
	if (m_pCURL == nullptr)
	{
		throw std::exception("curl_easy_init failed!");
	}

	m_hEvt = CreateEventA(NULL, TRUE, TRUE, NULL);
	//m_hExit = CreateEventA(NULL, FALSE, FALSE, NULL);
}


Clibcurl::~Clibcurl()
{
	curl_easy_cleanup(m_pCURL);
	CloseHandle(m_hEvt);
	//CloseHandle(m_hExit);
}


bool Clibcurl::setprogressfun(pfn_progress_callback progressfun, void* param)
{
	if (progressfun)
	{
		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_NOPROGRESS, 0L))
		{
			return false;
		}

		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_XFERINFOFUNCTION, progressfun))
		{
			return false;
		}

		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_XFERINFODATA, param))
		{
			return false;
		}
	}
	else
	{
		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_NOPROGRESS, 1L))
		{
			return false;
		}
	}

	return true;
}

bool Clibcurl::setwritefun(pfn_write_callback writefun, void* param)
{
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, writefun))
	{
		return false;
	}

	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, param))
	{
		return false;
	}

	return true;
}

bool Clibcurl::setproxy(std::string& szip, std::string& szport, std::string& szuser, std::string& szpwd)
{
	if (!szip.empty())
	{
		std::string szproxy = szip + ":" + szport;
		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_PROXY, szproxy.c_str()))
			return false;
	}

	if (!szuser.empty())
	{
		std::string szuserinfo = szuser + ":" + szpwd;
		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_PROXYUSERPWD, szuserinfo.c_str()))
			return false;
	}
	return true;
}


bool Clibcurl::setUpRate(unsigned long ulrate)
{
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_MAX_SEND_SPEED_LARGE, curl_off_t(ulrate)))
	{
		return false;
	}
	return true;
}

bool Clibcurl::setDownRate(unsigned long ulrate)
{
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_MAX_RECV_SPEED_LARGE, curl_off_t(ulrate)))
	{
		return false;
	}
	return true;
}


bool Clibcurl::getfilesize(std::string& szurl, size_t& size)
{
	bool bret = false;
	double filesize = 0.0;
	CURL* easy_handle = curl_easy_init();
	if (easy_handle == nullptr)
	{
		return false;
	}

	do
	{
		if (CURLE_OK != curl_easy_setopt(easy_handle, CURLOPT_URL, szurl.c_str()))
			break;

		//BREAKCURL(curl_easy_setopt(handle, CURLOPT_HEADER, 1L));    //只需要header头  
		if (CURLE_OK != curl_easy_setopt(easy_handle, CURLOPT_NOBODY, 1L))    //不需要body  
			break;
																	//BREAKCURL(curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L));
		if (CURLE_OK != curl_easy_perform(easy_handle))
			break;

		if (CURLE_OK != curl_easy_getinfo(easy_handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize))
			break;
		size = (size_t)filesize;
		bret = true;
	} while (FALSE);
	curl_easy_cleanup(easy_handle);
	return bret;
}


bool Clibcurl::downloadfile(std::string& szurl, std::string& szsavepath)
{
	int loop = 0;
	st = DOWNLOAD_START_PENDING;
	INT nGetResPonse = 0;
	size_t filesize = 0;

	std::ofstream ofs(szsavepath.c_str(), std::ios_base::out | std::ios_base::app | std::ios_base::binary);
	if (!ofs.is_open()) goto _ERROR_;

	if (!getfilesize(szurl, filesize)) goto _ERROR_;

	if (!setwritefun(write_callback, &ofs)) goto _ERROR_;

	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_FAILONERROR, 1L)) goto _ERROR_;
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_VERBOSE, 1)) goto _ERROR_;
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_URL, szurl.c_str())) goto _ERROR_;
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_HEADER, 0L)) goto _ERROR_;
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_CONNECTTIMEOUT, 4000)) goto _ERROR_;
	if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_TIMEOUT, 4000)) goto _ERROR_;

	do
	{
		st = DOWNLOAD_RUNING;
		ofs.seekp(0, ofs.end);
		std::streamoff currentlength = ofs.tellp();
		if (currentlength == filesize) goto _OK_;

		if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_RESUME_FROM_LARGE, (curl_off_t)currentlength))
			goto _ERROR_;

		int retcode = startdownload();

		if (CURLE_OK == retcode) goto _OK_;

		if (DOWNLOAD_STOP_PENDING == st) goto _STOP_;

		else if (DOWNLOAD_PAUSE_PENDING == st)
		{
			st = DOWNLOAD_PAUSED;
			DWORD waitResult = WaitForSingleObject(m_hEvt, INFINITE);
			if (WAIT_OBJECT_0 == waitResult) continue;
			else goto _STOP_;
		}
		else
		{
			if (loop++ > 100) goto _ERROR_;
			Sleep(20);
		}

	} while (true);

_OK_:
	st = DOWNLOAD_DONE;
	curl_easy_getinfo(m_pCURL, CURLINFO_RESPONSE_CODE, &nGetResPonse);
	return true;

_ERROR_:
	st = DOWNLOAD_ERROR;
	curl_easy_getinfo(m_pCURL, CURLINFO_RESPONSE_CODE, &nGetResPonse);
	return false;

_STOP_:
	st = DOWNLOAD_STOPPED;
	curl_easy_getinfo(m_pCURL, CURLINFO_RESPONSE_CODE, &nGetResPonse);
	return false;
}


int Clibcurl::startdownload()
{
	return (int)curl_easy_perform(m_pCURL);
}


int Clibcurl::stopdownload()
{
	CloseHandle(m_hEvt);
	m_hEvt = NULL;
	st = DOWNLOAD_STOP_PENDING;
	return curl_easy_pause(m_pCURL, CURLPAUSE_RECV);
}

int Clibcurl::pausedownload()
{
	ResetEvent(m_hEvt);
	st = DOWNLOAD_PAUSE_PENDING;
	return curl_easy_pause(m_pCURL, CURLPAUSE_RECV);
}

int Clibcurl::continuedownload()
{
	CURLcode code = curl_easy_pause(m_pCURL, CURLPAUSE_RECV_CONT);
	st = DOWNLOAD_STARTED;
	SetEvent(m_hEvt);
	return code;
}

//int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
//{
//	CURL *easy_handle = static_cast<CURL *>(clientp);
//	char timeFormat[9] = "Unknow";
//
//	// Defaults to bytes/second  
//	double speed;
//	string unit = "B";
//
//	curl_easy_getinfo(easy_handle, CURLINFO_SPEED_DOWNLOAD, &speed); // curl_get_info必须在curl_easy_perform之后调用  
//
//	if (speed != 0)
//	{
//		// Time remaining  
//		double leftTime = (downloadFileLength - dlnow - resumeByte) / speed;
//		int hours = leftTime / 3600;
//		int minutes = (leftTime - hours * 3600) / 60;
//		int seconds = leftTime - hours * 3600 - minutes * 60;
//
//#ifdef _WIN32  
//		sprintf_s(timeFormat, 9, "%02d:%02d:%02d", hours, minutes, seconds);
//#else  
//		sprintf(timeFormat, "%02d:%02d:%02d", hours, minutes, seconds);
//#endif  
//	}
//
//	if (speed > 1024 * 1024 * 1024)
//	{
//		unit = "G";
//		speed /= 1024 * 1024 * 1024;
//	}
//	else if (speed > 1024 * 1024)
//	{
//		unit = "M";
//		speed /= 1024 * 1024;
//	}
//	else if (speed > 1024)
//	{
//		unit = "kB";
//		speed /= 1024;
//	}
//
//	printf("speed:%.2f%s/s", speed, unit.c_str());
//
//	if (dltotal != 0)
//	{
//		double progress = (dlnow + resumeByte) / downloadFileLength * 100;
//		printf("\t%.2f%%\tRemaing time:%s\n", progress, timeFormat);
//	}
//
//	return 0;
//}