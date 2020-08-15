#include "StdAfx.h"
#include "OptionEx.h"

COptionEx::COptionEx(CPaintManagerUI* pPaintMgr)
{
	m_pOption = NULL;
	m_pButton = NULL;
	m_pPaintMgr = pPaintMgr;

	CDialogBuilder objBuilder;
	CContainerUI* pContainer = static_cast<CContainerUI*>(objBuilder.Create(_T("tabItem.xml"), 0, NULL, m_pPaintMgr, NULL));
	ASSERT(NULL != pContainer);
	if (NULL == pContainer)
	{
		RemoveAll();
	}
	else
	{
		Add(pContainer);
	}	
}

COptionEx::~COptionEx(void)
{
}

void COptionEx::Init()
{
	m_pOption = (COptionUI*)m_pPaintMgr->FindSubControlByName(this,_T("option"));
	m_pButton = (CButtonUI*)m_pPaintMgr->FindSubControlByName(this,_T("button"));

	ASSERT(NULL != m_pOption);
	ASSERT(NULL != m_pButton);
}