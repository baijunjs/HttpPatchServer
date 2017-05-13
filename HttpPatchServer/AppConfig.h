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
	std::string m_szIndexUrl;		//主索引URL
	std::string m_szPatchPath;		//补丁路径
	std::string m_szPackName;		//主索引名称
	std::string m_szProducts;		//产品列表
	std::string m_szLans;			//语言列表

	timemode mode;
	std::string sznettime;
	bool flux;
	int fluxspeed;
	bool proxy;
	std::string szip;
	std::string szport;
	std::string szuser;
	std::string szpwd;
};


struct cascade_option
{
	std::string szdbip;
	std::string szdbsrc;
	std::string szdbuser;
	std::string szdbpwd;
	bool cascade;
	std::string szupserverip;
	std::string szupserverport;
	timemode mode;
	std::string sznettime;
	bool flux;
	int fluxspeed;
	std::string szPatchPath;
	int localserverport;
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
	std::string m_szConfigFile;		//配置文件路径
	std::string m_szAppPath;		//应用程序路径
	std::string m_szLogPath;		//日志路径
	net_option		m_http_cfg;		//Http配置
	cascade_option	m_cascade_cfg;	//级联配置
	swicth_mode		m_mode_cfg;		//模式切换
	other_config	m_other_cfg;	//其他设置
	bool			m_bworking;		//是否在下载
};

extern app_config appconfig;