#include "StdAfx.h"
#include "CefBrowserEventHandler.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "UserGameDlg.h"

CCefBrowserEventHandler::CCefBrowserEventHandler(CUserGameDlg* pMainFrame)
{
	m_pMainFrame = pMainFrame;
}

CCefBrowserEventHandler::~CCefBrowserEventHandler(void)
{
	
}

CefRefPtr<CefDisplayHandler> CCefBrowserEventHandler::GetDisplayHandler()
{
	return this;
}

CefRefPtr<CefLifeSpanHandler> CCefBrowserEventHandler::GetLifeSpanHandler()
{
	return this;
}

CefRefPtr<CefLoadHandler> CCefBrowserEventHandler::GetLoadHandler()
{
	return this;
}

void CCefBrowserEventHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title)
{
	::SendMessage(m_pMainFrame->GetSafeHwnd(), WM_TITLE_CHANGED, (WPARAM)browser->GetHost()->GetWindowHandle(), (LPARAM)std::wstring(title).c_str());
}

void CCefBrowserEventHandler::OnAddressChange(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,const CefString& url)
{
	::SendMessage(m_pMainFrame->GetSafeHwnd(), WM_URL_CHANGED, (WPARAM)browser->GetHost()->GetWindowHandle(), (LPARAM)(LPCTSTR)url.c_str());
}

void CCefBrowserEventHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, 
										  const CefString& errorText, const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();
	if (ERR_ABORTED == errorCode)
		return ;

	std::stringstream ss;
	ss <<	"<html><body bgcolor=\"white\">"
			"<h2>Failed to load URL " << std::string(failedUrl) <<
			" with error " << std::string(errorText) << " (" << errorCode <<
			").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void CCefBrowserEventHandler::OnLoadingStateChange(CefRefPtr<CefBrowser> browser,bool isLoading,bool canGoBack,bool canGoForward)
{
	::PostMessage(m_pMainFrame->GetSafeHwnd(), WM_LOAD_CHANGED, (WPARAM)browser->GetHost()->GetWindowHandle(), MAKELPARAM(canGoForward, canGoBack));
}

void CCefBrowserEventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();	
	HWND hWnd = browser->GetHost()->GetWindowHandle();
	DWORD dwNewStyle = (::GetWindowLong(hWnd, GWL_STYLE)&~(WS_POPUP|WS_CAPTION|WS_BORDER|WS_SIZEBOX|WS_SYSMENU))|WS_CHILD;
	::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);  
	SetParent(hWnd, m_pMainFrame->GetSafeHwnd());
	
	m_browser_list.push_back(browser);
	::PostMessage(m_pMainFrame->GetSafeHwnd(), WM_CREATE_NEW_PAGE, (WPARAM)browser->GetHost()->GetWindowHandle(), 0);
//	m_pMainFrame->OnCreateNewPage((WPARAM)browser->GetHost()->GetWindowHandle(), 0);
}

BrowserPtr CCefBrowserEventHandler::GetBrowser(HWND hWnd)
{
	BrowserPtr pBrowser = NULL;
	for(size_t i = 0; i < m_browser_list.size(); ++i)
	{
		if (m_browser_list[i] && m_browser_list[i]->GetHost()->GetWindowHandle() == hWnd)
		{
			pBrowser = m_browser_list[i];
			break;
		}
	}
	return pBrowser;
}

bool CCefBrowserEventHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	if (1 == m_browser_list.size())
	{
	}
	return false;
}

void CCefBrowserEventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	for (BrowserList::iterator bit = m_browser_list.begin(); bit != m_browser_list.end(); ++bit) 
	{
		if ((*bit)->IsSame(browser)) {
			m_browser_list.erase(bit);
			break;
		}
	}

	if (m_browser_list.empty()) 
	{
		CefQuitMessageLoop();
	}
}

void CCefBrowserEventHandler::CloseBrowser(HWND hWnd)
{
	BrowserList::const_iterator it = m_browser_list.begin();
	for (; it != m_browser_list.end(); ++it)
	{
		if ((*it)->GetHost()->GetWindowHandle() == hWnd)
		{
			m_browser_list.erase(it);
			break;
		}
	}
}

void CCefBrowserEventHandler::CloseAllBrowser(bool force_close) 
{
	if (!CefCurrentlyOn(TID_UI)) 
	{
		CefPostTask(TID_UI,base::Bind(&CCefBrowserEventHandler::CloseAllBrowser, this, force_close));
		return;
	}

	if (m_browser_list.empty())
		return;

	BrowserList::const_iterator it = m_browser_list.begin();
	for (; it != m_browser_list.end(); ++it)
	{
		(*it)->GetHost()->CloseBrowser(force_close);
	}
}