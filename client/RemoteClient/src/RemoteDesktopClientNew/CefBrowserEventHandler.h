#pragma once
#include "include/cef_app.h"
#include "include/cef_client.h"

#include <list>
using namespace std;

typedef CefRefPtr<CefBrowser>		BrowserPtr;
typedef std::vector<BrowserPtr>	BrowserList;

class CUserGameDlg;
class CCefBrowserEventHandler
	: public CefClient
	, public CefDisplayHandler			// 显示变化事件
	, public CefLoadHandler			    // 加载错误事件
	, public CefLifeSpanHandler		    // 声明周期事件
	//, public CefContextMenuHandler	// 上下文菜单事件
	//, public CefDialogHandler			// 对话框事件
	//, public CefDownloadHandler		// 下载事件
	//, public CefDragHandler			// 拖拽事件
	//, public CefFindHandler			// 查找事件
	//, public ...
	//, public CefRequestHandler,
	//, public CefContextMenuHandler,
{
public:
	CCefBrowserEventHandler(CUserGameDlg* pMainFrame);
	virtual ~CCefBrowserEventHandler(void);
	BrowserPtr GetBrowser(HWND hWnd);

public:
	// CefClient 事件处理器,如果没有对应处理器则默认使用内部处理器
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

public:	
	// display handler method
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;
	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,CefRefPtr<CefFrame> frame,const CefString& url) OVERRIDE;

public:
	// load handler method
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;
	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,bool isLoading,bool canGoBack,bool canGoForward) OVERRIDE;

public:
	// display handler meethod
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

public:
	// own method of cef browser event handler
	void CloseAllBrowser(bool bForceClose = true);
	void CloseBrowser(HWND hWnd);

protected:
	BrowserList					m_browser_list;
	CUserGameDlg*				m_pMainFrame;

	IMPLEMENT_REFCOUNTING(CCefBrowserEventHandler);
};
