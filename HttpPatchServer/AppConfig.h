#pragma once
#include <map>
#include <vector>


typedef struct _tag_products
{
	std::vector<std::string> _inner_products;
} v_products;		//产品列表

typedef struct _tag_m_products
{
	std::map<std::string, v_products>	_inner_familys;		//产品集合(产品名称--产品列表)
} m_familys;

typedef struct _tag_op_product
{
	std::map<std::string, m_familys>	_inner_companys;	//系统集合(系统厂商--产品集合)
} m_publishers;


enum time_mode
{
	default_mode = -1,
	period_mode = 0,		//周期下载
	interval_mode			//间隔下载
};


struct interval_param
{
	char hour_start;
	char min_start;
	char hour_end;
	char min_end;
};

struct period_param
{
	int period_min;	//周期间隔(分钟)
};

struct proxy_param
{
	unsigned short uPort;
	std::string szIp;
	std::string szUser;
	std::string szPwd;
};


struct download_config
{
	time_mode tmode;		//下载时间方式
	struct
	{
		interval_param interval;
		period_param period;
	} time;
	int rate;				//下载速率
	bool bproxy;			//是否启用代理
	proxy_param proxyparam;	//代理参数

};

struct patch_option
{
	std::string m_szPatchPath;		//补丁路径
	std::string m_szIndexPath;		//索引路径
	std::string szUrl;				//主索引URL
	std::string szPackIndex;		//主索引名称
	m_publishers m_inst_products;	//产品配置
};


struct app_config
{
	std::string m_szAppTitle;		//
	std::string m_szConfigFile;		//配置文件路径
	std::string m_szAppPath;		//应用程序路径
	std::string m_szLogPath;		//日志路径
	download_config m_downloadcfg;	//下载配置
	patch_option	m_patch_opt;	//补丁配置
};

extern app_config appconfig;