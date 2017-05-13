// PatchSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "HttpPatchServer.h"
#include "PatchSetting.h"
#include "afxdialogex.h"
#include "PatchBus.h"
#include "Clibcurl.h"
#include <regex>
#include "MessageBox.h"
#include "PatchViewStatics.h"

// CPatchSetting 对话框

IMPLEMENT_DYNAMIC(CPatchSetting, CDialogEx)

CPatchSetting::CPatchSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PATCHSETTING, pParent)
{

}

CPatchSetting::~CPatchSetting()
{
}

void CPatchSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPatchSetting, CDialogEx)
	ON_WM_CREATE()
	ON_MESSAGE(DUISM_LBUTTONUP, &CPatchSetting::OnButtonDispatcher)
	ON_MESSAGE(DUITREE_CHECKITEM, &CPatchSetting::OnTreeCheckItem)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CPatchSetting 消息处理程序


bool CPatchSetting::InitDui()
{
	m_pDuiPatchSetting = (ISkinObjResBase*)AfxGetDuiRes()->CreateDirectUI("DUIPatchCfg", HandleToLong(m_hWnd));
	ASSERT(m_pDuiPatchSetting);

	m_pEditUrl = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditUrl", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pEditUrl);

	m_pEditPath = (IDUIEditCtrl*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "EditPath", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pEditPath);

	m_pCmdBtnTest = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnTest", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pCmdBtnTest);

	m_pCmdBtnBrowser = (ICmdButton*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "BtnBrowser", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pCmdBtnBrowser);

	m_pProductsTree = (IDUISimpleTree*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "ProductTree", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pProductsTree);

	m_pLansTree = (IDUISimpleTree*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "LanTree", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pLansTree);

	m_pWarnStatic = (IDUIStatic*)AfxGetDuiRes()->GetResObject(DUIOBJTYPE_PLUGIN, "WarnStatic", m_pDuiPatchSetting, TRUE);
	ASSERT(m_pWarnStatic);

	return true;
}

int CPatchSetting::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitDui())
		return -1;

	return 0;
}


BOOL CPatchSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_pEditUrl->SetText(appconfig.m_patch_opt.m_szIndexUrl);
	m_pEditPath->SetText(appconfig.m_patch_opt.m_szPatchPath);

	RedrawSimpleTree();
	RestoreTreeCheckItems(producttree);
	RestoreTreeCheckItems(languagetree);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPatchSetting::RedrawSimpleTree()
{

	std::string szpackindex = m_pEditPath->GetText() + "\\Tools\\PackIndex.dat";
	if (PathFileExistsA(szpackindex.c_str()))
	{
		if (!CPackInterface::init())
			return;

		IPackIndex *packindex = CPackInterface::getPackIndexObject();
		if (!bus.analyze_main_index(packindex, szpackindex))
			vrvlog::SPD_LOG_ERROR("{0} 解析失败", szpackindex.c_str());

		else
			vrvlog::SPD_LOG_INFO("{0} 解析成功", szpackindex.c_str());
		CPackInterface::FreePackIndexObject(packindex);
	}

	RedrawTreeImpl(producttree);
	RedrawTreeImpl(languagetree);
}


void CPatchSetting::RedrawTreeImpl(tree whichtree)
{
	IDUISimpleTree *pTree = NULL;

	if (producttree == whichtree)
		pTree = m_pProductsTree;

	else if (languagetree == whichtree)
		pTree = m_pLansTree;

	pTree->DeleteAllItem();
	OLE_HANDLE hroot = pTree->GetRootItem(NULL);

	vrv::patch::PublishersMapPtr publishers = bus.GetPatchIndexMap();
	if (!publishers || publishers->Publishers.empty())
	{
		pTree->AppendChild(hroot, "请点击\"测试连接\"", FALSE);
		return;
	}
	vrv::patch::PublishersMap::_iterator iter = publishers->Publishers.begin();
	for (; iter != publishers->Publishers.end(); ++iter)
	{
		std::string szPublisher = iter->first;
		OLE_HANDLE hpublisher = pTree->AppendChild(hroot, szPublisher, FALSE);
		vrv::patch::FamiliesMapPtr families = iter->second;
		if (pTree == m_pProductsTree)
		{
			vrv::patch::FamiliesMap::_iterator _iter = families->ProductsFamily.begin();
			for (; _iter != families->ProductsFamily.end(); ++_iter)
			{
				std::string szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::string szProduct = _iter_->first;
					OLE_HANDLE hproduct = pTree->AppendChild(hfamily, szProduct, FALSE);
					pTree->SetItemData(hproduct, (OLE_HANDLE)&_iter_->second);
				}
				pTree->Expand(hfamily, FALSE);
			}
		}
		else if (pTree == m_pLansTree)
		{
			vrv::patch::FamiliesMap::_iterator _iter = families->LanguagesFamily.begin();
			for (; _iter != families->LanguagesFamily.end(); ++_iter)
			{
				std::string szFamily = _iter->first;
				OLE_HANDLE hfamily = pTree->AppendChild(hpublisher, szFamily, FALSE);
				vrv::patch::ProductsMapPtr products = _iter->second;
				vrv::patch::ProductsMap::_iterator _iter_ = products->Products.begin();
				for (; _iter_ != products->Products.end(); ++_iter_)
				{
					std::string szProduct = _iter_->first;
					OLE_HANDLE hproduct = pTree->AppendChild(hfamily, szProduct, FALSE);
					pTree->SetItemData(hproduct, (OLE_HANDLE)&_iter_->second);
				}
				pTree->Expand(hfamily, FALSE);
			}
		}
		pTree->Expand(hpublisher, FALSE);
	}
	pTree->RedrawWindow(TRUE);
}


LRESULT CPatchSetting::OnButtonDispatcher(WPARAM wparam, LPARAM lparam)
{
	if (m_pCmdBtnTest == (ICmdButton*)wparam)
	{
		return OnButtonTest(wparam, lparam);
	}
	else if (m_pCmdBtnBrowser == (ICmdButton*)wparam)
	{
		return OnButtonBrowser(wparam, lparam);
	}

	return 0;
}

LRESULT CPatchSetting::OnTreeCheckItem(WPARAM wparam, LPARAM lparam)
{
	IDUISimpleTree *pTree = (IDUISimpleTree*)lparam;
	if (wparam != NULL)
	{
		CheckChildItem(pTree, wparam);
	}
	return 0;
}


void CPatchSetting::CheckChildItem(IDUISimpleTree *tree, OLE_HANDLE hParent)
{
	OLE_HANDLE hChild = tree->GetChildItem(hParent);
	while (hChild)
	{
		tree->CheckItem(hChild, tree->IsCheckItem(hParent));
		hChild = tree->GetNextSiblingItem(hChild);
	}
}

LRESULT CPatchSetting::OnButtonTest(WPARAM wparam, LPARAM lparam)
{
	std::string szurl = m_pEditUrl->GetText();
	std::string szpatchpath = m_pEditPath->GetText();
	std::regex rgx("^[A-Za-z]:[\\\\\\w]*");
	std::smatch sm;
	if (!std::regex_match(szpatchpath, sm, rgx))
	{
		CMessageBox msgbox;
		msgbox.ShowMessage("请选择有效的\"本地补丁路径\"");
		return 0;
	}

	std::string szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::string::npos)
	{
		szPackName = szurl.substr(pos + 1);
	}

	std::string sztoolpath = szpatchpath + "\\Tools\\";
	std::string szpackindex = sztoolpath + szPackName;
	std::string sztmppackindex = szpackindex + "~";
	Clibcurl curl;
	if (appconfig.m_http_cfg.proxy)
		curl.setproxy(
			appconfig.m_http_cfg.szip,
			appconfig.m_http_cfg.szport,
			appconfig.m_http_cfg.szuser,
			appconfig.m_http_cfg.szpwd);

	if (curl.downloadfile(szurl, sztmppackindex))
	{
		MoveFileExA(sztmppackindex.c_str(), szpackindex.c_str(), MOVEFILE_REPLACE_EXISTING);
		vrvlog::SPD_LOG_INFO("{0} 下载成功", szpackindex.c_str());
		RedrawSimpleTree();
		RestoreTreeCheckItems(producttree);
		RestoreTreeCheckItems(languagetree);
	}
	else
	{
		vrvlog::SPD_LOG_ERROR("{0} 下载失败", szpackindex.c_str());
		CMessageBox msg;
		msg.ShowMessage("测试连接失败,请检查网络或者URL配置");
	}

	return 0;
}


LRESULT CPatchSetting::OnButtonBrowser(WPARAM wparam, LPARAM lparam)
{
	CHAR szPath[MAX_PATH] = { 0 };
	BROWSEINFOA bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = _T("请选择补丁文件存放路径");
	bi.ulFlags = CSIDL_DRIVES;
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST lpIDList = SHBrowseForFolderA(&bi);
	if (NULL != lpIDList)
	{
		SHGetPathFromIDListA(lpIDList, szPath);
		m_pEditPath->SetText(szPath);
		CreateDirectoryA(szPath, NULL);
		strcat_s(szPath, MAX_PATH, "\\Tools");
		CreateDirectoryA(szPath, NULL);
		CoTaskMemFree(lpIDList);
	}

	return 0;
}

void CPatchSetting::OnApply()
{

	std::string &szurl = appconfig.m_patch_opt.m_szIndexUrl = m_pEditUrl->GetText();
	std::string &szpath = appconfig.m_patch_opt.m_szPatchPath = m_pEditPath->GetText();
	std::string &szproducts = appconfig.m_patch_opt.m_szProducts = GetCheckedItemString(m_pProductsTree);
	std::string &szlans = appconfig.m_patch_opt.m_szLans = GetCheckedItemString(m_pLansTree);
	std::string &szcfgpath = appconfig.m_szConfigFile;
	WritePrivateProfileStringA("PATCH", "URL", szurl.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "PATH", szpath.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "PRODUCTS", szproducts.c_str(), szcfgpath.c_str());
	WritePrivateProfileStringA("PATCH", "LAN", szlans.c_str(), szcfgpath.c_str());

	std::string szPackName;
	size_t pos = szurl.find_last_of('/');
	if (pos != std::string::npos)
		appconfig.m_patch_opt.m_szPackName = szurl.substr(pos + 1);
	std::string szPackPath = szpath + "\\Tools\\" + appconfig.m_patch_opt.m_szPackName;
	std::string szPackSha;

	if (GetFileSHA1(szPackPath, szPackSha))
	{
		if (szPackSha != bus.GetPackSha1())
		{
			CPatchViewStatics *pView = (CPatchViewStatics*)GetDlgItem(IDD_DIALOG_STATICS);
			pView->InsertIndexItem();
			pView->InitProductsItems();

		}
	}
}

std::string CPatchSetting::GetCheckedItemString(IDUISimpleTree* pTree)
{
	std::string szChecked = ";";
	short schecked = pTree->GetCheckItemCount();

	IDUITreeItem *item = pTree->GetFirstCheckItem();
	while (item)
	{
		OLE_HANDLE hData = pTree->GetItemData(item->GetTreeNode());
		if (hData)
		{
			std::string szItemText = pTree->GetItemText(item->GetTreeNode());
			szChecked.append(szItemText);
			szChecked.append(";");
		}
		item = pTree->GetNextCheckItem(item);
	}

	return szChecked;
}

void CPatchSetting::OnRestore()
{
	m_pEditUrl->SetText(appconfig.m_patch_opt.m_szIndexUrl);
	m_pEditPath->SetText(appconfig.m_patch_opt.m_szPatchPath);
	RestoreTreeCheckItems(producttree);
	RestoreTreeCheckItems(languagetree);
}


void CPatchSetting::RestoreTreeCheckItems(tree whichtree)
{
	IDUISimpleTree *pTree = NULL;
	std::string szXX;
	if (producttree == whichtree)
	{
		pTree = m_pProductsTree;
		szXX = appconfig.m_patch_opt.m_szProducts;
	}
	else if (languagetree == whichtree)
	{
		pTree = m_pLansTree;
		szXX = appconfig.m_patch_opt.m_szLans;
	}

	if (pTree == NULL || szXX.empty())
		return;

	OLE_HANDLE hroot = pTree->GetRootItem(NULL);
	OLE_HANDLE hchild = pTree->GetChildItem(hroot);
	//pTree->CheckItem(hchild, FALSE);

	while (hchild)
	{
		TravelTree(pTree, hchild, szXX);
		hchild = pTree->GetNextSiblingItem(hchild);
	}

	pTree->RedrawWindow(TRUE);
}

void CPatchSetting::TravelTree(IDUISimpleTree* pTree, OLE_HANDLE hParent, std::string& szChecked)
{
	std::string szItemText = pTree->GetItemText(hParent);
	szItemText.append(";").insert(0, ";");
	if (szChecked.find(szItemText) != std::string::npos)
	{
		pTree->CheckItem(hParent, TRUE);
	}
	else
	{
		pTree->CheckItem(hParent, FALSE);
	}
	OLE_HANDLE hchild = pTree->GetChildItem(hParent);
	while (hchild)
	{
		TravelTree(pTree, hchild, szChecked);
		hchild = pTree->GetNextSiblingItem(hchild);
	}
}

BOOL CPatchSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message)
	{
		if (VK_RETURN == pMsg->wParam)
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPatchSetting::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码

	//程序正在下载索引或补丁，界面不允许配置
	if (bShow)
	{
		if (appconfig.m_bworking)
		{
			m_pWarnStatic->SetVisible(TRUE, TRUE, TRUE);
			EnableWindow(FALSE);
		}
		else
		{
			m_pWarnStatic->SetVisible(FALSE, TRUE, TRUE);
			EnableWindow(TRUE);
		}
	}
}
