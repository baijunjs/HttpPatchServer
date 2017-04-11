#pragma once
#include "RCF\\RCF.hpp"


class CRcfClient 
	: public IDownload
{
public:
	CRcfClient();
	~CRcfClient();

public:
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

