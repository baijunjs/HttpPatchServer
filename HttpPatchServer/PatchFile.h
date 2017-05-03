#pragma once
#include <string>



class CPatchFile
{
public:
	CPatchFile();
	~CPatchFile();
	std::string		szPatchName;		//补丁名
	std::string		szPatchURL;			//补丁URL
	std::string		szPatchSize;		//补丁文件大小，字节为单位
	std::string		szUpdateID;			//UpDataID，吴哥定义生成的
	std::string		szPatchKB;			//KB号
	std::string		szPatchRank;		//风险等级
	std::string		szPatchMS;			//补丁MS号，有的补丁没有
	std::string		szLanguage;			//补丁语言属性
	std::string		szMD5;				//补丁MD5
	std::string		szDescription;		//不知道是啥玩意，调试看看是啥再写上备注
	std::string		szDatePublish;		//不知道是啥玩意，调试看看是啥再写上备注
};

typedef std::shared_ptr<CPatchFile>  PatchFilePtr;