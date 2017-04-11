#ifndef EDP_PATCH_BASE_H
#define EDP_PATCH_BASE_H


#define PATCHLEVEFILTER			"2" //补丁级别过滤
#define PATCHIEVERSIONFILTER	"3" //IE版本过滤
#define PATCHCLASSFILTER		"4" //补丁分类过滤
#define PATCHWINVERFILTER		"5" //WINDOWS版本过滤
#define PATCHLANGUAGEFILTER		"6" //语言过滤
#define	PATCHCPUFILTER			"7" //CPU类型过滤
#define PATCHOFFICEFILTER		"8" //OFFICE版本过滤

enum EMPatchItemCode
{
	PATCH_UNKNOWN = 1000,
	PATCH_DETCT,
	PATCH_DETECTION,
	PATCH_INDEXNOEXIST,
	PATCH_FILECHANGE,
	PATCH_REGCHANGE,
	PATCH_EditTime,
	PATCH_EditHandle,
	PATCH_Prerequisites,
	PATCH_ApplicabilityRules,
	PATCH_PatchRule,
	PATCH_SupercededBy,
	PATCH_info1,
	PATCH_info2,
	PATCH_info3,
	PATCH_info4,
	PATCH_info5,
	PATCH_info6,
	PATCH_Affects,
	PATCH_Suggestion,
	PATCH_LangInfo1,						//Class
	PATCH_LangInfo2,						//PATCHCRC
	PATCH_LangInfo3,						//filterinfo
	PATCH_LangInfo4,						//已安装补丁的安装时间
	PATCH_LangInfo5,
	PATCH_LangInfo6
};

enum ePatchDownLoad
{
	DOWNLOAD_TYPE_HTTP		=	20,
	DOWNLOAD_TYPE_HTTPS,
	DOWNLOAD_TYPE_TCP
};

enum ePatchSavePathMode
{
	PATCH_FILE_SAVE_APP_LOCAL			=	30,
	PATCH_FILE_SAVE_APPOINT,
	PATCH_FILE_SAVE_MAX_FREE_DISK
};

#define DOWNLOADINDEX	1000
#define DOWNLOADPATCH	1001

#define PARAMLEN10		10
#define PARAMLEN100		100

class IProduct 
{
public:
	virtual LPCSTR GetInstall() = 0;
	virtual LPCSTR GetName() = 0;
	virtual LPCSTR GetDepend() = 0;
};

class IProductFamily
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IProduct *GetFirst() = 0;
	virtual IProduct *GetNext() = 0;
	virtual IProduct * FindName(LPCSTR lpszName) = 0;
	virtual IProduct * GetItem(int i) = 0;
};

class ICompany
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IProductFamily *GetFirst() = 0;
	virtual IProductFamily *GetNext() = 0;
	virtual IProductFamily * FindName(LPCSTR lpszName) = 0;
	virtual IProductFamily * GetItem(int i) = 0;
};

class ICategories
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual ICompany *GetFirst() = 0;
	virtual ICompany *GetNext() = 0;
	virtual ICompany * FindName(LPCSTR lpszName) = 0;
	virtual ICompany * GetItem(int i) = 0;
};

class IPackFile
{
public:
	virtual LPCSTR GetName() = 0;
	virtual LPCSTR GetPath() = 0;
	virtual DWORD GetCrc() = 0;
	virtual bool IsExist() = 0;
	virtual LPCSTR GetSubPath() = 0;
	virtual DWORD GetSubCrc() = 0;
};

class IProductPack
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IPackFile *GetFirst() = 0;
	virtual IPackFile *GetNext() = 0;
	virtual IPackFile * FindName(LPCSTR lpszName) = 0;
	virtual IPackFile * GetItem(int i) = 0;
};

class IPACKAGE
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IProductPack *GetFirst() = 0;
	virtual IProductPack *GetNext() = 0;
	virtual IProductPack * FindName(LPCSTR lpszName) = 0;
	virtual IProductPack * GetItem(int i) = 0;
};

class IPackCompany
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IPACKAGE *GetFirst() = 0;
	virtual IPACKAGE *GetNext() = 0;
	virtual IPACKAGE * FindName(LPCSTR lpszName) = 0;
	virtual IPACKAGE * GetItem(int i) = 0;
};

class IPatchPack
{
public:
	virtual int GetCount() = 0;
	virtual LPCSTR GetName() = 0;
	virtual IPackCompany *GetFirst() = 0;
	virtual IPackCompany *GetNext() = 0;
	virtual IPackCompany * FindName(LPCSTR lpszName) = 0;
	virtual IPackCompany * GetItem(int i) = 0;
};

class IPackIndex
{
public:
	virtual bool LoadFile(LPCSTR lpFileName) = 0;
	virtual ICategories * GetCategories() = 0;
	virtual void Release() = 0;
	virtual int  GetPackCount(IN LPCSTR lpszCompanyName,
							  IN LPCSTR lpszProductFamily,
							  IN LPCSTR lpszPackageName) = 0;
	virtual bool GetPackFileInfo(IN LPCSTR lpszCompanyName,
								 IN LPCSTR lpszProductFamily,
								 IN LPCSTR lpszPackageName,
								 IN int		nPack,
								 OUT LPSTR lpszFilePath,
								 OUT DWORD &dwFileCrc,
								 OUT bool &bExist,
								 IN int		nSub = 0) = 0;
	virtual IPatchPack * GetPatchPack() = 0;
	virtual bool SaveFile(LPCSTR lpFileName) = 0;
};

class IPatchItem
{
public:
	virtual LPCSTR GetFileName() = 0;
	virtual LPCSTR GetUrl() = 0;
	virtual LPCSTR GetPatchMD5() = 0;
	virtual LPCSTR GetPatchName() = 0;
	virtual LPCSTR GetLeakInfo() = 0;
	virtual LPCSTR GetLeakDescription() = 0;
	virtual LPCSTR GetPatchSize() = 0;
	virtual LPCSTR GetPublishTime() = 0;
	virtual LPCSTR GetBulletins() = 0;
	virtual LPCSTR GetUpdateID() = 0;
	virtual LPCSTR GetPatchKBID() = 0;
	virtual LPCSTR GetPatchLevel() = 0;
	virtual LPCSTR GetPatchType() = 0;
	virtual LPCSTR GetSupportOs() = 0;
	virtual LPCSTR GetLanguages() = 0;
	virtual LPCSTR GetBuildNumber() = 0;
	virtual LPCSTR GetInstallParam() = 0;
	virtual LPCSTR GetSuperced() = 0;
	virtual LPCSTR GetCpuArch() = 0;
	virtual LPCSTR GetInstallResult() = 0;
	virtual LPCSTR GetWebPage() = 0;
	virtual LPCSTR GetMirrorURL() = 0;
	virtual LPCSTR GetNeedsReboot() = 0;
	virtual LPCSTR GetDescription() = 0;
	virtual LPCSTR GetDownFlag() = 0;
	virtual LPCSTR GetSpNumber() = 0;
	virtual LPCSTR GetSuggestion() = 0;
	virtual LPCSTR GetAffects() = 0;
	virtual LPCSTR GetProductType() = 0;
	virtual LPCSTR GetExclusive() = 0;
	virtual LPCSTR GetSupercedBy() = 0;
	virtual LPCSTR GetLocalPatchPath() = 0;
	virtual LPCSTR GetCompanyName() = 0;
	virtual LPCSTR GetProductFamily() = 0;
	virtual LPCSTR GetProductName() = 0;
	virtual LPCSTR GetIndexType() = 0;
	virtual LPCSTR GetIndexExsit() = 0;
	virtual LPCSTR GetSuperedPatch() = 0;
	virtual bool GetValue(ULONG uCode, ...) = 0;
	virtual void SetLocalPatchPath(LPCSTR lpszValue) = 0;
	virtual HRESULT IsInstallable() = 0;
	virtual LPCSTR GetFilterInfo() = 0;
	virtual LPCSTR GetInstallTime() = 0;
};

class IPatchContainer
{
public:
	virtual IPatchItem *GetFirstPatch() = 0;
	virtual IPatchItem *GetNextPatch() = 0;
	virtual IPatchItem *FindPatchByFileName(LPCSTR lpszFileName) = 0;
	virtual IPatchItem *FindPatchByUpdateID(LPCSTR lpszUpdateID) = 0;
	virtual IPatchItem *FindPatchByKBID(LPCSTR lpszKBID) = 0;
	virtual IPatchItem *GetPatchByIndex(int nIndex) = 0;
	virtual IPatchItem *GetPatchFromKBListByIndex(int nIndex) = 0;
	virtual int	GetCount() = 0;
	virtual void Release() = 0;
};

struct TOptionCondition 
{
	TOptionCondition()
	{
		nUseFilter			= 0;
		nUseIntranetPatch	= 0;
		nScanMode			= 0;
		
		nWinVer				= 0;
		nWinSP				= 0;
		nIEVer				= 0;
		nIESP				= 0;
		nPatchType			= 0;
		nCreateSupercede	= 0;
		nJS					= 0;
		nMediaplayer		= 0;
		nDX					= 0;
		nOE					= 0;
		nDataAccess			= 0;
		nFramework			= 0;
		nXML				= 0;
		nMSN				= 0;

		nMinLoad			= 0;
		nDownLoadMode		= 0;
		nPatchSaveMode		= 0;

		nFilterPatchLevel	= 0;
		memset(szFilterIEVer, 0, MAX_PATH);
		memset(szFilterWinVer, 0, MAX_PATH);
		memset(szFilterOffice, 0, MAX_PATH);
		memset(szFilterPatchType, 0, MAX_PATH);
		memset(szFilterLanguage, 0, PARAMLEN100);
		memset(szFilterCpuType, 0, PARAMLEN10);
		
		memset(szBuildNumber, 0, PARAMLEN10);
		memset(szBuildALL, 0, PARAMLEN10);
		memset(szCpuType, 0, PARAMLEN10);
		memset(szLanguage, 0, PARAMLEN10);
		memset(szIEVer, 0, PARAMLEN10);
		memset(szPatchIndexServerUrl, 0, MAX_PATH);
		memset(szRegionManageIP, 0, PARAMLEN100);
		memset(szRegionManagePort, 0, PARAMLEN10);
		memset(szProxyServer, 0, PARAMLEN100);
		memset(szProxyServerPort, 0, PARAMLEN10);
		memset(szProxyUser, 0, PARAMLEN100);
		memset(szProxyPassWord, 0, PARAMLEN100);
		memset(szPatchSavePath, 0, MAX_PATH);
	};

	int nUseFilter;							//1启用过滤条件,0不启用
	int nUseIntranetPatch;					//补丁和索引来源，0公网，1内网
	int nScanMode;							//扫描模式，0不扫描，1未安装, 2已安装, 3未安装和已安装, 4被替代补丁, 7未安装加已安装加被替代补丁,8已安装补丁不需要补丁描述只要KB号，减少内存使用。
	int nWinVer, nWinSP;					//build number
	int nIEVer, nIESP;						//IE版本
	int nPatchType;							//补丁类型，0系统补丁，1IE补丁，2office补丁，4通用补丁,8应用补丁，16第三方补丁
	int nCreateSupercede;					//是否生成替代补丁列表

	int nJS;
	int nMediaplayer;	
	int nDX;			
	int nOE;
	int nDataAccess;
	int nFramework;
	int nXML;
	int nMSN;
	int nMinLoad;							//索引加载模式，200为只加载主索引,100最小加载模式，300为写临时文件模式，600低内存探测。
	int nDownLoadMode;						//补丁下载模式
	int nPatchSaveMode;						//补丁存放模式

	int	 nFilterPatchLevel;					//需要过滤的补丁级别 >= 0-4 定义补丁等级，0为未定义，1低，2中等，3重要，4关键
	char szFilterIEVer[MAX_PATH];			//需要过滤的IE版本 5.0,5.5,6,7,8,9,10,11,12,13,14,15,16
	char szFilterWinVer[MAX_PATH];			//需要过滤的WINDOWS版本 WIN2000,WINXP,WIN2003,VISTA,WIN7,WIN8,WIN8.1,WIN10,WIN2008,WIN2008R2,WIN2012,WIN2012R2
	char szFilterOffice[MAX_PATH];			//需要过滤的OFFICE版本
	char szFilterPatchType[MAX_PATH];		//需要过滤的补丁类别空=ALL,Critical Updates,Feature Packs,Security Updates,Service Packs,Updates,Applications,Definition Updates,Tool,Update Rollups,Drivers
	char szFilterLanguage[PARAMLEN100];		//需要过滤的语言 .zhcn.,.en.
	char szFilterCpuType[PARAMLEN10];		//需要过滤的CPU类型 0=X86，6=IA64, 9=X64

	char szBuildNumber[PARAMLEN10];
	char szBuildALL[PARAMLEN10];
	char szCpuType[PARAMLEN10];				
	char szLanguage[PARAMLEN10];			
	char szIEVer[PARAMLEN10];
	char szPatchIndexServerUrl[MAX_PATH];	//索引服务器下载地址
	char szRegionManageIP[PARAMLEN100];				//区域管理器IP
	char szRegionManagePort[PARAMLEN10];	//区域管理器端口
	char szProxyServer[PARAMLEN100];				//代理服务器地址
	char szProxyServerPort[PARAMLEN10];		//代理服务器端口
	char szProxyUser[PARAMLEN100];					//代理服务器用户
	char szProxyPassWord[PARAMLEN100];				//代理服务器密码
	char szPatchSavePath[MAX_PATH];			//补丁存放路径
};

enum EMPatchEventType {

	ePatch_Error,				// 错误				
	ePatch_ScanBegin,			// Scan 开始		0, Num 
	ePatch_ScanProgress,		// Scan 进度		0, nCurrentItem 

	ePatch_DownloadBegin,		// 下载开始			id  currentnum,	totalnum  
	ePatch_DownloadProcess,	// 下载进度			id, downloadedsize, fullsize
	ePatch_DownloadEnd,		// 下载结束			id, currentnum, down.result
	ePatch_DownloadError,		// 下载失败			id, currentnum, 

	ePatch_InstallBegin,		// 安装开始			id, currentnum,	totalnum 
	ePatch_InstallBeginUser,	// 自定义安装开始	
	ePatch_InstallEnd,			// 安装结束			id, currentnum, install.result 
	ePatch_InstallError,		// 安装失败			id, currentnum
	ePatch_InstallEndNeedReboot,// 安装成功需要重新启动 
	ePatch_InstallFailOther,

	ePatch_Task_Complete,		// 任务完全完成 
	ePatch_Task_Error,			// 任务有错, 可能部分完成 

	ePatch_Download_Check_Error,// 下载下来的补丁数字签名校验失败
};

typedef struct _OBSERVERPARAM
{
	EMPatchEventType evt;
	int nKbId;
	DWORD dwParam1;
	DWORD dwParam2;
	char szStringInfo[1024];
}ObserverParam;

class IPatchStringList
{
public:
	virtual LPCSTR GetItemName(int nIndex) = 0;
	virtual int GetCount() = 0;
};

class IPatchObserver
{
public:
	//virtual void OnPatchEvent(EMPatchEventType evt, int nKbId, DWORD dwParam1, DWORD dwParam2) = 0;
	virtual void OnPatchEvent(ObserverParam Param) = 0;
};

class ILoadIndex
{
public:
	virtual void Reset() = 0;
	virtual void SetObserver(IPatchObserver *pObserver) = 0;

	virtual void SetProductPack(LPCSTR lpszFileName) = 0;
	virtual void SetLanguagePack(LPCSTR lpszFileName) = 0;
	virtual void SetIntranetPack(LPCSTR lpszIntranetName) = 0;
	virtual void ClearProductPack() = 0;
	virtual void ClearLanguagePack() = 0;
	virtual HRESULT LoadFile() = 0;

	virtual HRESULT LoadMainFile(LPCSTR lpszMainIndex) = 0;
	virtual void Cancel() = 0;

	virtual int GetProductPackCount() = 0;
	virtual LPCSTR GetProductPackNameByIndex(int nIndex) = 0;
	virtual int GetLanguagePackCount() = 0;
	virtual LPCSTR GetLanguagePackNameByIndex(int nIndex) = 0;
	virtual LPCSTR GetIntranetPackName( ) = 0;

	virtual int	GetCount() = 0;
	virtual IPatchItem *GetFirstPatch() = 0;
	virtual IPatchItem *GetNextPatch() = 0;
	virtual IPatchItem *FindPatchByFileName(LPCSTR lpszFileName) = 0;
	virtual IPatchItem *FindPatchByUpdateID(LPCSTR lpszUpdateID) = 0;
	virtual IPatchItem *FindPatchByKBID(LPCSTR lpszKBID) = 0;
	virtual IPatchItem *GetPatchByIndex(int nIndex) = 0;
	virtual void SetOption(TOptionCondition TOption) = 0;
	virtual void Release() = 0;
};

class IPatchScan
{
public:
	virtual void SetObserver(IPatchObserver *pObserver) = 0;

	virtual HRESULT Scan(DWORD dwFlags=0) = 0;	// 扫描
	virtual HRESULT Cancel() = 0;
	virtual LPCSTR GetErrorInfo() = 0;

	virtual void SetPackPath(LPCSTR lpszFileName) = 0;
	virtual void SetIntranetPath(LPCSTR lpszFileName) = 0;
	virtual IPatchContainer *GetInstalledPatchList() = 0;
	virtual IPatchContainer *GetInstallableList() = 0;
	
	virtual void SetOption(TOptionCondition Option) = 0;
	virtual void Release() = 0;
};

class IPatchInstall 
{
public:

	virtual HRESULT Reset() = 0;
	virtual HRESULT SetObserver(IPatchObserver *pObserver) = 0;

	virtual HRESULT AddRepairPatch(IPatchScan *pPatchSacn, IPatchStringList *RepairPatchName) = 0;

	virtual HRESULT RepairPath(LPCSTR sDownloadPath, LPCSTR szImportPath, DWORD dwFlags) = 0;
	virtual HRESULT Repair(LPCSTR szPatchFile, LPCSTR szInstallParam, DWORD dwWaiting, DWORD &dwResult) = 0;
	virtual HRESULT StopRepair() = 0;
	virtual HRESULT WaitForRepairDone() = 0;
	virtual HRESULT GetItemFilePath(INT nID, LPCSTR lpszPath) = 0;
	virtual void Release() = 0;
	virtual int GetResult(LPCSTR lpszResult, DWORD iResult) = 0;
};

class IPatchDownLoad
{
public:
	virtual HRESULT Reset() = 0;
	virtual void SetHttpTimeout(DWORD dwTimeout) = 0;
	virtual HRESULT SetObserver(IPatchObserver *pObserver) = 0;

	virtual HRESULT DownLoadFile(LPCSTR lpszUrl) = 0;
	virtual BOOL InitDownLoadServer(int nType) = 0;
	virtual void SetOption(TOptionCondition TOption) = 0;
	virtual void Release() = 0;
	virtual LPCSTR GetDownLoadPath() = 0;
};

class IPatchManage
{
public:
	virtual IPackIndex *GetPackIndex() = 0;
	virtual ILoadIndex *GetLoadIndex() = 0;
	virtual IPatchScan *GetPatchScan() = 0;
	virtual IPatchInstall * GetPatchInstall() = 0;
	virtual IPatchDownLoad *GetPatchDownLoad() = 0;
	virtual void Release() = 0;
};

typedef IPatchManage * (WINAPI *PFNCreatePatchObject)();
typedef IPackIndex * (WINAPI *PFNCreatePackObject)();
typedef ILoadIndex * (WINAPI *PFNCreateLoadObject)();
typedef IPatchScan * (WINAPI *PFNCreateScanObject)();
typedef IPatchInstall * (WINAPI *PFNCreateRepairObject)();
typedef IPatchDownLoad * (WINAPI *PFNCreateDownLoadObject)();
#endif //EDP_PATCH_BASE_H

