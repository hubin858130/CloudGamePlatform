#pragma once
#include "UIlib.h"
using namespace DuiLib;

class COptionEx 
	: public CContainerUI
{
public:
	COptionEx(CPaintManagerUI* pPaintMgr);
	virtual ~COptionEx(void);

public:
	void Init();

public:
	COptionUI*		 m_pOption;
	CButtonUI*		 m_pButton;
	CPaintManagerUI* m_pPaintMgr;
};
