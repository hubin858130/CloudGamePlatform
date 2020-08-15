
// RemoteDesktopClient.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "RemoteDesktopClient.h"
#include "RemoteDesktopClientDlg.h"
#include "LoginDlg.h"
#include "HttpUtil.h"
#include "CefBrowserApp.h"
#include "Util.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//
//#include<string>
//using std::string;
// CRemoteDesktopClientApp


bool CheckProccessRunInstance()
{
	HANDLE hProcessHandle = ::CreateMutex(NULL, FALSE, "Global\\REMOTEDESKTOPCLIENT");

	int nLastError = GetLastError();
	if (ERROR_ALREADY_EXISTS == nLastError || ERROR_ACCESS_DENIED == nLastError)
	{
		//		MessageBox("Applictaion is running !");
		return false;
	}

	return true;
}

BEGIN_MESSAGE_MAP(CRemoteDesktopClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRemoteDesktopClientApp 构造

CRemoteDesktopClientApp::CRemoteDesktopClientApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRemoteDesktopClientApp 对象

CRemoteDesktopClientApp theApp;


// CRemoteDesktopClientApp 初始化

BOOL CRemoteDesktopClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	bool bOnly = CheckProccessRunInstance();
	if (!bOnly)
	{
		AfxMessageBox("已经启动客户端，无法重现启动!");
		return TRUE;
	}

//	freopen(".\\log.txt", "w", stderr);
	//CString str = (CString)AfxGetApp()->m_lpCmdLine;
	//AfxMessageBox(str);

	//非网吧版本：huqb
	// CEF Init
	//CefEnableHighDPISupport();
	//CefSettings settings;
	//settings.no_sandbox = true;
	//settings.multi_threaded_message_loop = true;
	//settings.single_process = true;
	//CefRefPtr<CCefBrowserApp> objApp(new CCefBrowserApp());
	//CefMainArgs mainArgs(AfxGetInstanceHandle());
	//CefInitialize(mainArgs, settings, objApp.get() /*NULL*/, NULL);


	CString strRemoteIP = "";
	int     nResolution = 0;
	int nGameType = 1;

//测试版本
	CLoginDlg dlgLogin;
	INT_PTR nRes = dlgLogin.DoModal();
	if (nRes == IDOK)
	{
		strRemoteIP = dlgLogin.getRemoteIP();
		nResolution = dlgLogin.getRemoteResolution();
	}
	else
	{
		CefShutdown();
		return FALSE;
	}//测试版本

	/*
	HTTP/1.1 200
	Content-Type: application/json;charset=UTF-8
	Transfer-Encoding: chunked
	Date: Wed, 27 Jun 2018 04:43:37 GMT

	c3
	{"id":"5B321375002948238F8375047284BE72","rmIp":"","ip":"192.168.1.14","port":"554","description":"","net":0,"runState":1,"areaId":2,"lastStateTime":1530074599709,"lastConsumeTime":1530074617530}
	0
	*/

	//手动配置IP的版本，直接获取IP b
	/*string strExePath = GetExeFileExistDir() + "/Server.ini";
	char *strConfigFilePath = (char*)strExePath.c_str();
	char szIP[50];
	memset(szIP, 0, 50);
	GetPrivateProfileString("info", "ip", NULL, szIP, 50, strConfigFilePath);
	strRemoteIP = szIP;
	if (strRemoteIP.IsEmpty())
	{
		AfxMessageBox("配置异常，请与管理员联系!");
		return TRUE;
	}*/
	//手动配置IP的版本，直接获取IP e

	//自动获取IP b
	//string strExePath = GetExeFileExistDir() + "/Server.ini";
	//char *strConfigFilePath = (char*)strExePath.c_str();
	//char szGuid[50];
	//memset(szGuid, 0, 50);
	//GetPrivateProfileString("info", "id", NULL, szGuid, 50, strConfigFilePath);

	//CString strRes;
	//CHttpUtil cGetUtil;
	//CString strAreaID = szGuid;
	////int nRet = cGetUtil.getVmInfo("116.62.205.17", 80, 2, strAreaID, strRes);
	//int nRet = cGetUtil.getVmInfo("116.62.205.17", 80, strAreaID, strRes);
	//if (nRet != 0)
	//{
	//	AfxMessageBox("请检测网络是否通畅或者远程服务是否开启！");
	//	return FALSE;
	//}
	//
	////简单解析
	//int nPos = strRes.Find("\"ip\":\"");//Find("\"ip\":\"");
	//if (nPos > 0)
	//{
	//	CString strIP = strRes.Right(strRes.GetLength() - nPos - 6);
	//	nPos = strIP.Find("\",");
	//	if (nPos > 0)
	//	{
	//		strRemoteIP = strIP.Left(nPos);
	//	}
	//	else
	//	{
	//		AfxMessageBox("机器解析出错，请联系管理员！");
	//	}
	//}
	//else
	//{
	//	AfxMessageBox("暂无有空闲机器，请稍后重试或联系管理员！");
	//	return FALSE;
	//}
	//自动获取IP e
	
	//非网吧版本：huqb
	//CUserGameDlg dlgGame(strRemoteIP, nResolution);
	//m_pMainWnd = &dlgGame;
	//CWndsManger::getWndsMangerInstance().setUserGameDlg(&dlgGame);
	//INT_PTR nResponse = dlgGame.DoModal();

	CRemoteDesktopClientDlg dlg(strRemoteIP, nResolution, nGameType);
	m_pMainWnd = &dlg;
	CWndsManger::getWndsMangerInstance().setMainDlg(&dlg);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
//	CefShutdown();

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

