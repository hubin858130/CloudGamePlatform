#pragma once
#include "include/cef_app.h"
#include "include/cef_print_handler.h"

class CCefBrowserApp
	: public CefApp
	, public CefBrowserProcessHandler
	, public CefRenderProcessHandler
{
public:
	CCefBrowserApp(void);
	virtual ~CCefBrowserApp(void);

public:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE;
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE;
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,CefRefPtr<CefV8Context> context) OVERRIDE;
	virtual void OnWebKitInitialized() OVERRIDE;

public:
	void OnContextInitialized() OVERRIDE;
 	void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line) OVERRIDE;
 	void OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) OVERRIDE;
	void OnScheduleMessagePumpWork(int64 delay) OVERRIDE;

protected:
	IMPLEMENT_REFCOUNTING(CCefBrowserApp);
};
