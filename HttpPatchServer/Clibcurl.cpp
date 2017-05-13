#include "stdafx.h"
#include <exception>
#include <fstream>
#include "Clibcurl.h"


size_t Writtenfun(char *pbuf, size_t size, size_t stNum, void * pData)
{
	std::ofstream *pfile = (std::ofstream *)pData;
	if (pfile)
	{
		pfile->write(pbuf, size * stNum);
		return size * stNum;
	}
	return 0;
}


Curl::Curl() noexcept(false)
{
	m_pCURL = curl_easy_init();
	if (m_pCURL == nullptr)
		throw std::exception("curl_easy_init failed!");
	m_pProgress = nullptr;
	m_pProgressParam = nullptr;
	m_pWritten = nullptr;
	m_pWrittenParam = nullptr;
	m_lupspeed = 0;
	m_ldownspeed = 0;
	m_filesize = 0;
	m_curLength = 0;
	m_pProgressCtrl = nullptr;
	m_status = DOWNLOAD_STARTED;
}


Curl::~Curl()
{
	curl_easy_cleanup(m_pCURL);
}


void Curl::SetProgressCallback(_TyProgressCallback progressfun, void* param, void* phwnd)
{
	m_pProgress = progressfun;
	m_pProgressParam = param;
	m_pProgressCtrl = phwnd;
}

void Curl::SetWriteCallback(_TyWrittenCallback writtenfun, void* param)
{
	m_pWritten = writtenfun;
	m_pWrittenParam = param;
}

void Curl::SetProxy(std::string& szip, std::string& szport, std::string& szuser, std::string& szpwd)
{

	m_szProxyip = szip;
	m_szProxyport = szport;
	m_szProxyuser = szuser;
	m_szProxypwd = szpwd;
}


void Curl::SetUploadSpeed(long ulrate)
{
	m_lupspeed = ulrate * 1024;
	curl_easy_setopt(m_pCURL, CURLOPT_MAX_SEND_SPEED_LARGE, curl_off_t(m_lupspeed));
}

void Curl::SetDownloadSpeed(long ulrate)
{
	m_ldownspeed = ulrate * 1024;
	curl_easy_setopt(m_pCURL, CURLOPT_MAX_RECV_SPEED_LARGE, curl_off_t(m_ldownspeed));
}

void Curl::SetUrlFile(std::string szUrl, std::string szFile)
{
	m_szUrl = szUrl;
	m_szFile = szFile;
}


long Curl::GetFileSize(size_t& size)
{

	CURLcode code = CURLE_OK;

	do
	{
		double filesize = 0.0;
		long lRespCode = 0;
		curl_easy_reset(m_pCURL);

		if (!m_szProxyip.empty())
		{
			std::string szproxy = m_szProxyip + ":" + m_szProxyport;
			if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_PROXY, szproxy.c_str())))
				break;
		}

		if (!m_szProxyuser.empty())
		{
			std::string szuserinfo = m_szProxyuser + ":" + m_szProxypwd;
			if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_PROXYUSERPWD, szuserinfo.c_str())))
				break;
		}
		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_CONNECTTIMEOUT, 5L)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_TIMEOUT, 5)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_URL, m_szUrl.c_str())))
			break;

		//BREAKCURL(curl_easy_setopt(handle, CURLOPT_HEADER, 1L));    //只需要header头  
		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_NOBODY, 1L)))    //不需要body  
			break;
																	//BREAKCURL(curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L));
		if (CURLE_OK != (code = curl_easy_perform(m_pCURL)))
		{
			m_status = DOWNLOAD_ERROR;
			break;
		}

		if (CURLE_OK != (code = curl_easy_getinfo(m_pCURL, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize)))
			break;

		if (CURLE_OK != (code = curl_easy_getinfo(m_pCURL, CURLINFO_RESPONSE_CODE, &lRespCode)))
			break;

		if (lRespCode == 200)
		{
			m_filesize = size = (size_t)filesize;
		}
		
	} while (FALSE);

	return code;
}


long Curl::StartDownload()
{
	INT nGetResPonse = 0;
	size_t filesize = 0;
	if (m_filesize == 0)
	{
		long lret = GetFileSize(filesize);
		if (lret != CURLE_OK)
			return lret;
	}

	std::ofstream ofs(m_szFile.c_str(), 
		std::ios_base::out |
		std::ios_base::app |
		std::ios_base::binary);
	if (!ofs.is_open())
		return CURLE_WRITE_ERROR;

	if (m_pWritten == nullptr)
	{
		m_pWritten = Writtenfun;
		m_pWrittenParam = &ofs;
	}

	curl_easy_reset(m_pCURL);
	CURLcode code = CURLE_OK;
	m_status = DOWNLOAD_STARTED;
	do
	{

		if (!m_szProxyip.empty())
		{
			std::string szproxy = m_szProxyip + ":" + m_szProxyport;
			if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_PROXY, szproxy.c_str())))
				break;
		}

		if (!m_szProxyuser.empty())
		{
			std::string szuserinfo = m_szProxyuser + ":" + m_szProxypwd;
			if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_PROXYUSERPWD, szuserinfo.c_str())))
				break;
		}

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_WRITEFUNCTION, m_pWritten)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_WRITEDATA, m_pWrittenParam)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_FAILONERROR, 1L)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_VERBOSE, 1)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_URL, m_szUrl.c_str())))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_HEADER, 0L)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_CONNECTTIMEOUT, 5)))
			break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_TIMEOUT, 5)))
			break;

		//if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_MAX_SEND_SPEED_LARGE, curl_off_t(m_lupspeed))))
			//break;

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_MAX_RECV_SPEED_LARGE, curl_off_t(m_ldownspeed))))
			break;

		if (m_pProgress)
		{
			if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_NOPROGRESS, 0L))
				break;

			if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_XFERINFOFUNCTION, m_pProgress))
				break;

			if (CURLE_OK != curl_easy_setopt(m_pCURL, CURLOPT_XFERINFODATA, m_pProgressParam))
				break;
		}
		
	} while (FALSE);
	
	if (code != CURLE_OK)
		return code;

	do
	{
		m_status = DOWNLOAD_RUNNING;

		ofs.seekp(0, ofs.end);
		m_curLength = ofs.tellp();
		if (m_curLength == m_filesize)
		{
			m_status = DOWNLOAD_DONE;
			break;
		}

		if (CURLE_OK != (code = curl_easy_setopt(m_pCURL, CURLOPT_RESUME_FROM_LARGE, (curl_off_t)m_curLength)))
		{
			m_status = DOWNLOAD_ERROR;
			break;
		}

		if (CURLE_OK == (code = curl_easy_perform(m_pCURL)))
		{
			m_status = DOWNLOAD_DONE;
			break;
		}

		if (m_status == DOWNLOAD_STOPPED)
			break;


		if (code == CURLE_OPERATION_TIMEDOUT)
		{
			continue;
		}
		else
		{
			m_status = DOWNLOAD_ERROR;
			break;
		}



	} while (true);
	
	return code;
}


long Curl::StopDownload()
{
	m_status = DOWNLOAD_STOPPED;
	return curl_easy_pause(m_pCURL, CURLPAUSE_RECV);
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