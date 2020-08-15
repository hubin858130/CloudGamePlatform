#pragma once
#include "include/cef_v8.h"

class CV8JsHandler :
	public CefV8Handler
{
public:
	CV8JsHandler(void);
	virtual ~CV8JsHandler(void);

public:
	virtual bool Execute(const CefString& name,
						  CefRefPtr<CefV8Value> object,
						  const CefV8ValueList& arguments,
						  CefRefPtr<CefV8Value>& retval,
						  CefString& exception) OVERRIDE;

	IMPLEMENT_REFCOUNTING(CV8JsHandler);
};
