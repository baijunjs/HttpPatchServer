#pragma once
#include <string>


struct FileTransforRequest
{
	std::string szRequestFilePath;			
	std::string szRequestFileName;
	uint32_t fileRequestPos;
	uint32_t fileRequestLength;
};

struct FileTransforResponse
{
	std::string szResponseFilePath;
	std::string szResponseFileName;
	uint32_t fileResponsePos;
	uint32_t fileResponseLength;
	uint32_t fileLeftLength;
	char data[1];
};
