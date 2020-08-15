#include "StdAfx.h"
#include "V8JsHandler.h"

CV8JsHandler::CV8JsHandler(void)
{
}

CV8JsHandler::~CV8JsHandler(void)
{
}

bool CV8JsHandler::Execute(const CefString& func_name,
							 CefRefPtr<CefV8Value> object,
							 const CefV8ValueList& arguments,
							 CefRefPtr<CefV8Value>& retval,
							 CefString& exception)
{
	if (func_name == _T("startgame"))
	{
		int32 nRet = 0;
		int32 nGameType = 0;
		for (size_t i = 0; i < arguments.size(); ++i)
		{
			if (arguments[i]->IsInt())
			{
				nGameType = arguments[i]->GetIntValue();
				//postmessage:
				CWndsManger::getWndsMangerInstance().getUserGameDlog()->PostMessage(WM_START_REMOTE, nGameType, 0);
				break;
			}
				
		}
		retval = CefV8Value::CreateInt(nRet);
		return true;
	}
	//else if (func_name == _T("hehe"))
	//{
	//	retval = CefV8Value::CreateString(_T("hehe hehe!"));
	//	return true;
	//}
	else
	{
		return false;
	}
}