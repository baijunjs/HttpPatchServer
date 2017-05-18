#pragma once
#include <map>
#include <vector>


enum timemode
{
	default_mode = 0,		//全时段下载
	period_mode = 1,		//周期下载
	interval_mode = 2			//间隔下载
};


enum switchmode
{
	http_mode,				//http下载模式
	cascade_mode,			//级联模式
};



struct patch_option
{

};


struct net_option
{
	std::tstring m_szIndexUrl;		//主索引URL
	std::tstring m_szPatchPath;		//补丁路径
	std::tstring m_szPackName;		//主索引名称
	std::tstring m_szProducts;		//产品列表
	std::tstring m_szLans;			//语言列表

	timemode mode;
	std::tstring sznettime;
	bool flux;
	int fluxspeed;
	bool proxy;
	std::tstring szip;
	std::tstring szport;
	std::tstring szuser;
	std::tstring szpwd;
};


struct cascade_option
{
	std::tstring szdbip;
	std::tstring szdbsrc;
	std::tstring szdbuser;
	std::tstring szdbpwd;
	bool cascade;
	std::tstring szupserverip;
	std::tstring szupserverport;
	timemode mode;
	std::tstring sznettime;
	bool flux;
	int fluxspeed;
	std::tstring szPatchPath;
	int localserverport;
	bool index1;
};

enum LANS
{
	ZHCN,
	EN,
};

struct swicth_mode
{
	switchmode mode;
};

struct other_config
{
	bool enable;	//
	int level;		//调试日志级别
	LANS lang;
};

struct app_config
{
	std::tstring m_szConfigFile;		//配置文件路径
	std::tstring m_szAppPath;		//应用程序路径
	std::tstring m_szLogPath;		//日志路径
	net_option		m_http_cfg;		//Http配置
	cascade_option	m_cascade_cfg;	//级联配置
	swicth_mode		m_mode_cfg;		//模式切换
	other_config	m_other_cfg;	//其他设置
	bool			m_bworking;		//是否在下载
};

extern app_config appconfig;