#pragma once
#include <string>



class CPatchFile
{
public:
	CPatchFile() {};
	~CPatchFile() {};
	std::tstring		szPatchName;		//补丁名
	std::tstring		szPatchURL;			//补丁URL
	std::tstring		szPatchSize;		//补丁文件大小，字节为单位
	std::tstring		szUpdateID;			//UpDataID，吴哥定义生成的
	std::tstring		szPatchKB;			//KB号
	std::tstring		szPatchRank;		//风险等级
	std::tstring		szPatchMS;			//补丁MS号，有的补丁没有
	std::tstring		szLanguage;			//补丁语言属性
	std::tstring		szMD5;				//补丁MD5
	std::tstring		szDescription;		//不知道是啥玩意，调试看看是啥再写上备注
	std::tstring		szDatePublish;		//不知道是啥玩意，调试看看是啥再写上备注
};

typedef std::shared_ptr<CPatchFile>  PatchFilePtr;