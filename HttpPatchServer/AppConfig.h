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
	std::tstring m_szIndexUrl;		//������URL
	std::tstring m_szPatchPath;		//����·��
	std::tstring m_szPackName;		//����������
	std::tstring m_szProducts;		//��Ʒ�б�
	std::tstring m_szLans;			//�����б�

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
	int level;		//������־����
	LANS lang;
};

struct app_config
{
	std::tstring m_szConfigFile;		//�����ļ�·��
	std::tstring m_szAppPath;		//Ӧ�ó���·��
	std::tstring m_szLogPath;		//��־·��
	net_option		m_http_cfg;		//Http����
	cascade_option	m_cascade_cfg;	//��������
	swicth_mode		m_mode_cfg;		//ģʽ�л�
	other_config	m_other_cfg;	//��������
	bool			m_bworking;		//�Ƿ�������
};

extern app_config appconfig;