#pragma once
#include <map>
#include <vector>


typedef struct _tag_products
{
	std::vector<std::string> _inner_products;
} v_products;		//��Ʒ�б�

typedef struct _tag_m_products
{
	std::map<std::string, v_products>	_inner_familys;		//��Ʒ����(��Ʒ����--��Ʒ�б�)
} m_familys;

typedef struct _tag_op_product
{
	std::map<std::string, m_familys>	_inner_companys;	//ϵͳ����(ϵͳ����--��Ʒ����)
} m_publishers;


enum time_mode
{
	default_mode = -1,
	period_mode = 0,		//��������
	interval_mode			//�������
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
	int period_min;	//���ڼ��(����)
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
	time_mode tmode;		//����ʱ�䷽ʽ
	struct
	{
		interval_param interval;
		period_param period;
	} time;
	int rate;				//��������
	bool bproxy;			//�Ƿ����ô���
	proxy_param proxyparam;	//�������

};

struct patch_option
{
	std::string m_szPatchPath;		//����·��
	std::string m_szIndexPath;		//����·��
	std::string szUrl;				//������URL
	std::string szPackIndex;		//����������
	m_publishers m_inst_products;	//��Ʒ����
};


struct app_config
{
	std::string m_szAppTitle;		//
	std::string m_szConfigFile;		//�����ļ�·��
	std::string m_szAppPath;		//Ӧ�ó���·��
	std::string m_szLogPath;		//��־·��
	download_config m_downloadcfg;	//��������
	patch_option	m_patch_opt;	//��������
};

extern app_config appconfig;