#include "stdafx.h"
#include "WndsManger.h"
CWndsManger*   CWndsManger::s_pWndsMangerIns = NULL;
CWndsManger&   CWndsManger::getWndsMangerInstance()
{
	if (s_pWndsMangerIns == NULL)
	{
		s_pWndsMangerIns = new CWndsManger;
	}
	return *s_pWndsMangerIns;
}

CWndsManger::CWndsManger()
: m_pMaindlg(NULL)
, m_pUserGameDlg(NULL)
{
}

CWndsManger::~CWndsManger()
{
}

void CWndsManger::setMainDlg(CRemoteDesktopClientDlg* pDlg)
{
	m_pMaindlg = pDlg;
}

CRemoteDesktopClientDlg* CWndsManger::getMainDlg()
{
	return m_pMaindlg;
}

void CWndsManger::setUserGameDlg(CUserGameDlg* pDlg)
{
	m_pUserGameDlg = pDlg;
}

CUserGameDlg* CWndsManger::getUserGameDlog()
{
	//if (m_pUserGameDlg == NULL)
	//{
	//	m_pUserGameDlg = new CUserGameDlg();
	//	m_pUserGameDlg->Create(IDD_DLG_USERGAME, CWnd::FromHandle(GetDesktopWindow()));
	//}
	return m_pUserGameDlg;
}
