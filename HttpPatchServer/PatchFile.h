#pragma once
#include <string>



class CPatchFile
{
public:
	CPatchFile() {};
	~CPatchFile() {};
	std::tstring		szPatchName;		//������
	std::tstring		szPatchURL;			//����URL
	std::tstring		szPatchSize;		//�����ļ���С���ֽ�Ϊ��λ
	std::tstring		szUpdateID;			//UpDataID����綨�����ɵ�
	std::tstring		szPatchKB;			//KB��
	std::tstring		szPatchRank;		//���յȼ�
	std::tstring		szPatchMS;			//����MS�ţ��еĲ���û��
	std::tstring		szLanguage;			//������������
	std::tstring		szMD5;				//����MD5
	std::tstring		szDescription;		//��֪����ɶ���⣬���Կ�����ɶ��д�ϱ�ע
	std::tstring		szDatePublish;		//��֪����ɶ���⣬���Կ�����ɶ��д�ϱ�ע
};

typedef std::shared_ptr<CPatchFile>  PatchFilePtr;