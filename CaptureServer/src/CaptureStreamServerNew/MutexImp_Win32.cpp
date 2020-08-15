#include "stdafx.h"
#include "MutexImp_Win32.h"

namespace CS
{
	/****************************************************************************
	*
	* CCritSecImp
	*
	****************************************************************************/
	CCritSecImp::CCritSecImp()
	{ 
		InitializeCriticalSection(&m_CritSec);
	}

	CCritSecImp::~CCritSecImp()
	{
		DeleteCriticalSection(&m_CritSec); 
	}

	void CCritSecImp::Lock()
	{
		EnterCriticalSection(&m_CritSec);
	}

	void CCritSecImp::Unlock()
	{ 
		LeaveCriticalSection(&m_CritSec);
	}

	/****************************************************************************
	*
	* CMutexImp
	*		wait: 无限等待
	****************************************************************************/
	CMutexImp::CMutexImp(char* lpName, bool bInitialOwner)
	{
		if (!lpName)
		{
			m_mutex = ::CreateMutexA(NULL, (BOOL)bInitialOwner, NULL);
		}
		else
		{
			m_strName = lpName;
			m_mutex = ::CreateMutexA(NULL, (BOOL)bInitialOwner, lpName);
		}
	}

	CMutexImp::~CMutexImp(void)
	{
		::CloseHandle(m_mutex);
	}

	const string& CMutexImp::GetName()
	{
		return m_strName;
	}

	void CMutexImp::Lock(void)
	{
		::WaitForSingleObject(m_mutex, INFINITE);
	}  

	void CMutexImp::Unlock(void)
	{ 
		::ReleaseMutex(m_mutex);
	}

	/****************************************************************************
	*
	* CSemaphoreImp
	*		wait: 无限等待或timeout等待
	*		release: 只释放1个
	****************************************************************************/
	CSemaphoreImp::CSemaphoreImp(char* lpName, int nMaxNum, int nInitNum)
	{ 
		if (!lpName)
		{
			m_semaphore = ::CreateSemaphoreA(NULL, nInitNum, nMaxNum, NULL);
		}
		else
		{
			m_strName = lpName;
			m_semaphore = ::CreateSemaphoreA(NULL, nInitNum, nMaxNum, m_strName.c_str());
		}
	}

	CSemaphoreImp::~CSemaphoreImp(void)
	{ 
		::CloseHandle(m_semaphore);
	}

	bool CSemaphoreImp::Wait(int timeout)
	{ 
		if (WAIT_TIMEOUT == ::WaitForSingleObject(m_semaphore, timeout))
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void CSemaphoreImp::Release(void)
	{ 
		::ReleaseSemaphore(m_semaphore, 1, NULL);
	}

	const string& CSemaphoreImp::GetName()
	{
		return m_strName;
	}

	/****************************************************************************
	*
	* CEventImp
	*		default: 手动 不激发
	****************************************************************************/
	CEventImp::CEventImp(bool bManualReset)
	{
		m_hEvent = CreateEvent(NULL, bManualReset, false, NULL);
	}

	CEventImp::~CEventImp()
	{ 
		CloseHandle(m_hEvent);
	}

	bool CEventImp::Set(void) 
	{
		bool bRet = false;
		bRet = ::SetEvent(m_hEvent)?true:false;
		return bRet;
	}

	bool CEventImp::Wait(unsigned long ulTimeout)
	{
		if (ulTimeout == 0)
			ulTimeout = INFINITE;

		bool bRet = false;
		if(WAIT_OBJECT_0 == WaitForSingleObject(m_hEvent, ulTimeout))
			bRet = true;
		return bRet;
	}

	bool CEventImp::Reset(void) 
	{ 
		bool bRet = false;
		bRet = ::ResetEvent(m_hEvent)?true:false;
		return bRet;
	}
}
