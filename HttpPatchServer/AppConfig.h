#pragma once
#include <map>
#include <vector>


enum timemode
{
	default_mode = 0,		//ȫʱ������
	period_mode = 1,		//��������
	interval_mode = 2			//�������
};


enum switchmode
{
	http_mode,				//http����ģʽ
	cascade_mode,			//����ģʽ
};



struct patch_option
{

};


struct net_option
{
	std::string m_szIndexUrl;		//������URL
	std::string m_szPatchPath;		//����·��
	std::string m_szPackName;		//����������
	std::string m_szProducts;		//��Ʒ�б�
	std::string m_szLans;			//�����б�

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
	int level;		//������־����
	LANS lang;
};

struct app_config
{
	std::string m_szConfigFile;		//�����ļ�·��
	std::string m_szAppPath;		//Ӧ�ó���·��
	std::string m_szLogPath;		//��־·��
	net_option		m_http_cfg;		//Http����
	cascade_option	m_cascade_cfg;	//��������
	swicth_mode		m_mode_cfg;		//ģʽ�л�
	other_config	m_other_cfg;	//��������
	bool			m_bworking;		//�Ƿ�������
};

extern app_config appconfig;