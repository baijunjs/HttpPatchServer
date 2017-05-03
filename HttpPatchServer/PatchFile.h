#pragma once
#include <string>



class CPatchFile
{
public:
	CPatchFile();
	~CPatchFile();
	std::string		szPatchName;		//������
	std::string		szPatchURL;			//����URL
	std::string		szPatchSize;		//�����ļ���С���ֽ�Ϊ��λ
	std::string		szUpdateID;			//UpDataID����綨�����ɵ�
	std::string		szPatchKB;			//KB��
	std::string		szPatchRank;		//���յȼ�
	std::string		szPatchMS;			//����MS�ţ��еĲ���û��
	std::string		szLanguage;			//������������
	std::string		szMD5;				//����MD5
	std::string		szDescription;		//��֪����ɶ���⣬���Կ�����ɶ��д�ϱ�ע
	std::string		szDatePublish;		//��֪����ɶ���⣬���Կ�����ɶ��д�ϱ�ע
};

typedef std::shared_ptr<CPatchFile>  PatchFilePtr;