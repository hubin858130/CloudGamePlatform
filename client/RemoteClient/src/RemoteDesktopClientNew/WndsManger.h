#pragma once
#include "RemoteDesktopClientDlg.h"
#include "UserGameDlg.h"
class CWndsManger
{
public:
	static CWndsManger& getWndsMangerInstance();
	~CWndsManger();

	void setMainDlg(CRemoteDesktopClientDlg* pDlg);
	CRemoteDesktopClientDlg* getMainDlg();

	//gamedailog
	void setUserGameDlg(CUserGameDlg* pDlg);
	CUserGameDlg* getUserGameDlog();


	void  DestoryHookDlg();

protected:
	CWndsManger();
	static CWndsManger*			s_pWndsMangerIns;

	CRemoteDesktopClientDlg*	m_pMaindlg;

	CUserGameDlg*				m_pUserGameDlg;

};

