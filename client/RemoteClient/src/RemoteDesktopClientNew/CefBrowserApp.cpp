#include "StdAfx.h"
#include "CefBrowserApp.h"
#include "V8JsHandler.h"

CCefBrowserApp::CCefBrowserApp(void)
{
}

CCefBrowserApp::~CCefBrowserApp(void)
{
}

CefRefPtr<CefBrowserProcessHandler> CCefBrowserApp::GetBrowserProcessHandler()
{
	return this;
}

CefRefPtr<CefRenderProcessHandler> CCefBrowserApp::GetRenderProcessHandler()
{
	return this;
}

void CCefBrowserApp::OnContextInitialized()
{
	// do nothing here, because we will create browser in my own dialog
}

void CCefBrowserApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,CefRefPtr<CefV8Context> context)
{
	// The var type can accept all object or variable
	CefRefPtr<CefV8Value> window = context->GetGlobal();

	// bind value into window[or you can bind value into window sub node]

	//CefRefPtr<CefV8Value> strValue = CefV8Value::CreateString(_T("say yes"));
	//window->SetValue(_T("say_yes"), strValue, V8_PROPERTY_ATTRIBUTE_NONE);

	// bind function 
	CefRefPtr<CV8JsHandler> pJsHandler(new CV8JsHandler());
	CefRefPtr<CefV8Value> myFunc = CefV8Value::CreateFunction(_T("startgame"), pJsHandler);
	window->SetValue(_T("startgame"), myFunc, V8_PROPERTY_ATTRIBUTE_NONE);

	//CefRefPtr<CV8JsHandler> pJsHandler2(new CV8JsHandler());
	//CefRefPtr<CefV8Value> myFunc2 = CefV8Value::CreateFunction(_T("hehe"), pJsHandler2);
	//window->SetValue(_T("hehe"), myFunc2, V8_PROPERTY_ATTRIBUTE_NONE);
}

void CCefBrowserApp::OnBeforeChildProcessLaunch(
	CefRefPtr<CefCommandLine> command_line) 
{

}

void CCefBrowserApp::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info) 
{

}

void CCefBrowserApp::OnScheduleMessagePumpWork(int64 delay) 
{
}

void CCefBrowserApp::OnWebKitInitialized()
{
	std::string extensionCode =
		"var g_value=\"global value here\";"
		"var test;"
		"if (!test)"
		"  test = {};"
		"(function() {"
		"  test.myfunc = function() {"
		"    native function hehe(int,int);"
		"    return hehe(10, 50);"
		"  };"
		"})();";

	// 声明本地函数 native function hehe();" 如果有参数列表需要写具体的类型,而不能写var类型！与本地声明一直
	// 调用本地函数    return hehe();"

	// Create an instance of my CefV8Handler object.
	CefRefPtr<CefV8Handler> handler = new CV8JsHandler();

	// Register the extension.
	CefRegisterExtension("v8/mycode", extensionCode, handler);	
}
