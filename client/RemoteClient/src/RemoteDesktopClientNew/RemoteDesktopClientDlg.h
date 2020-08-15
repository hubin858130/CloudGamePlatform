
// RemoteDesktopClientDlg.h : 头文件
//

#pragma once
#include "NetConnect.h"
#include "resource.h"
#include "afxwin.h"
#include <map>
using std::map;

// CRemoteDesktopClientDlg 对话框
class CRemoteDesktopClientDlg : public CDialogEx
{
// 构造
public:
	CRemoteDesktopClientDlg(const CString strServIP,const int nResolution,const int nGameType,CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMOTEDESKTOPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	BOOL InitAll();
	void ReleaseAll();
	void PlayRemoteDesktop();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg LRESULT OnInput(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnKybordEvent(WPARAM wParam, LPARAM lParam);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	void SetMouseModel();

	HBITMAP MakeBitmap(HDC hDc, LPBYTE lpBits, long lWidth, long lHeight, WORD wBitCount);
	HCURSOR CreateCursorFromBitmap(HBITMAP hSourceBitmap, COLORREF clrTransparent, DWORD xHotspot,DWORD yHotspot);

	void SetRunTimeStatus(int nStatus){ m_nRunTimeStatus = nStatus; };
	int  GetRunTimeStatus(){ return m_nRunTimeStatus; }
	bool ConnectServer();

	int  PlayScreen();
	void setWindowsMode(int nMode);//0:窗口  2 全屏
	int GetStartProcessID(){ return m_nGameType; };

	bool Getkeystate(int nCode);
	bool AllkeysIsUp();
	void Setkystate(int nCode,bool bStatus);

private:
	
	CString      m_strServIP;
	CRect        m_OldRect;
	DWORD		 m_dwStyle;
	DWORD		 m_dwExStyle;
	int			 m_nDlgSizeType;

	int			 m_nEventStart;
	HCURSOR		 m_hHandCursor;
	
	int			 m_nRunTimeStatus;
	CStatic		 m_staPlayer;

	bool         m_bNetRet;

public:
	CString createMsgBody(int mMsg, int mValue1, int mValue2, long lParam);
	int		sendMsg(CString strMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	int				m_nLastX;
	int				m_nLastY;

	int				m_nBaseX;
	int				m_nBaseY;
	CNetConnect		m_cNet;
	bool			m_bMouseRevel;
	bool            m_bMouseLeave;

	int				m_nResolution;//分辨率 0:720p  1:1080P 2:自动适配服务器的分辨率
	int				m_nWidth;
	int				m_nHeight;
	
	int				m_nGameType;//启动类型

	bool			m_bExitThread;
	HCURSOR			m_hCursor;

	HWND			m_hWndPlayer;

	HBITMAP			m_hBmpback;

	map<int, bool>   m_mapKeyStatus;

	bool			m_bF11Enable;//是否已经受理了F11
	bool			m_bMouseDown;//鼠标是否未匹配就切换消息了
};
