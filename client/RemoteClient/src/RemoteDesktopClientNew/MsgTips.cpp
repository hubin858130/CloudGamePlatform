// MsgTips.cpp : 实现文件
//

#include "stdafx.h"
#include "RemoteDesktopClient.h"
#include "MsgTips.h"
#include "afxdialogex.h"

CMsgTips*  CMsgTips::s_pMsgTipsDlg = NULL;

CMsgTips& CMsgTips::getMsgTipsInstance()
{
	if (s_pMsgTipsDlg == NULL)
	{
		s_pMsgTipsDlg = new CMsgTips();
		s_pMsgTipsDlg->Create(IDD_DLG_TIPS);
		s_pMsgTipsDlg->ShowWindow(SW_HIDE);
	}
	return *s_pMsgTipsDlg;
}
// CMsgTips 对话框

IMPLEMENT_DYNAMIC(CMsgTips, CDialogEx)

CMsgTips::CMsgTips(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMsgTips::IDD, pParent)
{

}

CMsgTips::~CMsgTips()
{
}

void CMsgTips::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIP, m_editTips);
}

BEGIN_MESSAGE_MAP(CMsgTips, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CMsgTips::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CFont* font;
	font = m_editTips.GetFont();//获取CFont对象
	LOGFONT lf;
	font->GetLogFont(&lf);//获取LOGFONT结构体
	lf.lfHeight = 35;    //修改字体大小
	lf.lfItalic = FALSE;        //倾斜
	lf.lfWeight = 30;   //修改字体的粗细
	m_newFont.CreateFontIndirect(&lf);//创建一个新的字体
	m_editTips.SetFont(&m_newFont);
	
	return TRUE;
}
// CMsgTips 消息处理程序

void CMsgTips::SetTipText(CString strTips)
{
	if (s_pMsgTipsDlg != NULL)
	{
		s_pMsgTipsDlg->ShowWindow(SW_SHOW);
		m_editTips.SetWindowText(strTips);
		SetTimer(1, 3000, NULL);
		CRemoteDesktopClientDlg* pMainDlg = CWndsManger::getWndsMangerInstance().getMainDlg();
		if (pMainDlg != NULL)
		{
			CRect rcMain, rcTips;
			pMainDlg->GetWindowRect(&rcMain);
			this->GetWindowRect(rcTips);

			int nX = rcMain.left + (rcMain.Width() - rcTips.Width()) / 2;
			if (nX < 0)
				nX = 1;
			int nY = rcMain.top+40;
			int nW = rcTips.Width();
			int nH = rcTips.Height();

			s_pMsgTipsDlg->MoveWindow(nX, nY, nW, nH);
		}
	}
	GetDlgItem(IDC_EDIT_TIP)->PostMessage(WM_KILLFOCUS, 0, 0);
}

void CMsgTips::CloseTipsDlg()
{
	if (s_pMsgTipsDlg != NULL)
	{
		s_pMsgTipsDlg->DestroyWindow();
		delete s_pMsgTipsDlg;
		s_pMsgTipsDlg = NULL;
	}
}

void CMsgTips::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		if (s_pMsgTipsDlg != NULL)
		{
			s_pMsgTipsDlg->ShowWindow(SW_HIDE);
			KillTimer(1);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

HBRUSH CMsgTips::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_EDIT_TIP == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkColor(RGB(4, 40, 80));
		pDC->SetTextColor(RGB(240, 240, 240));
	}
	switch (nCtlColor)

	{
	case CTLCOLOR_DLG:
		HBRUSH aBrush;
		aBrush = CreateSolidBrush(RGB(4, 40, 80));
		hbr = aBrush;
	break;

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
