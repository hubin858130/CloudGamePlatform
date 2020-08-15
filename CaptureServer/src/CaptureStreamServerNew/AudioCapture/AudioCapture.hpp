
/*
*	author: zyb		
*	\brief:   
*		CAudioCaptureT<eRender>		: Capture Audio Output Stream
*		CAudioCaptureT<eCapture>	: Capture Audio Input Stream
*/

#pragma once

#include "CaptureEvent.h"
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <process.h>
#include <avrt.h>

#pragma comment(lib,"Avrt.lib")

namespace
{
	typedef struct
	{
		HANDLE hEventStarted;
		HANDLE hEventStop;
		ICaptureEvent *pEventHandle;
		IMMDevice *pDevice;
	}capture_thread_data;

	template<int _iDataFlow>
	struct TaskNameT{};

	template<>
	struct TaskNameT<eRender>
	{
		static wchar_t * Get()
		{
			return L"Capture";
		}
	};

	template<>
	struct TaskNameT<eCapture>
	{
		static wchar_t * Get()
		{
			return L"Audio";
		}
	};

	template<int _iDataFlow>
	struct StreamFlagT{};

	template<>
	struct StreamFlagT<eRender>
	{
		static int Get()
		{
			return AUDCLNT_STREAMFLAGS_LOOPBACK;
		}
	};

	template<>
	struct StreamFlagT<eCapture>
	{
		static int Get()
		{
			return 0;
		}
	};
}

template<int _iDataFlow>
class CAudioCaptureT
{
public:
	CAudioCaptureT();
	~CAudioCaptureT();

	bool Init(ICaptureEvent *pHandler);
	void UnInit();
	bool Start();
	void Stop();

	bool IsCapturing() const;
	bool IsInit() const;

	void GetPcmBaseInfo(int& nSamples, int& nChannels, int& nBitsPerSample);
private:
	static IMMDevice * _GetDefaultDevice();
	static UINT _CaptureAudio(IMMDevice *pDevice, HANDLE hEventStarted, HANDLE hEventStop, ICaptureEvent *pEventHandle);
	static UINT __stdcall _CaptureThreadProc(LPVOID param);

private:
	bool   m_bInited;
	int		m_nSamplesPerSec;
	int		m_nChannel;
	int		m_nBitsPerSample;

	HANDLE m_hEventStarted;
	HANDLE m_hEventStop;
	HANDLE m_hThreadCapture;

	IMMDevice *m_pDevice;
	ICaptureEvent *m_pEventHandler;
};

template<int _iDataFlow>
CAudioCaptureT<_iDataFlow>::CAudioCaptureT() :
m_bInited(false),
m_hEventStarted(nullptr),
m_hEventStop(nullptr),
m_hThreadCapture(nullptr),
m_pDevice(nullptr),
m_pEventHandler(nullptr)
{
}

template<int _iDataFlow>
CAudioCaptureT<_iDataFlow>::~CAudioCaptureT()
{
	UnInit();
}

template<int _iDataFlow>
bool CAudioCaptureT<_iDataFlow>::Init(ICaptureEvent *pHandler)
{
	if (m_bInited)
		return true;

#define checkRet(ret)	if(IS_NULLPTR(ret)) break;

	if (IS_NULLPTR(pHandler))
		return false;
	m_pEventHandler = pHandler;

	do
	{
		m_pDevice = _GetDefaultDevice();
		checkRet(m_pDevice);

		m_hEventStarted = CreateEvent(nullptr, true, false, nullptr);
		checkRet(m_hEventStarted);

		m_hEventStop = CreateEvent(nullptr, true, false, nullptr);
		checkRet(m_hEventStop);

		m_bInited = true;

	} while (0);

	if (IS_FALSE(m_bInited))
		UnInit();

	return m_bInited;
}

template<int _iDataFlow>
void CAudioCaptureT<_iDataFlow>::UnInit()
{
	m_pEventHandler = nullptr;
	SafRelease(m_pDevice);
	SafCloseHandle(m_hEventStarted);
	SafCloseHandle(m_hEventStop);
	m_bInited = false;
}

template<int _iDataFlow>
bool CAudioCaptureT<_iDataFlow>::IsCapturing() const
{
	return NOT_NULLPTR(m_hThreadCapture);
}

template<int _iDataFlow>
bool CAudioCaptureT<_iDataFlow>::IsInit() const
{
	return m_bInited;
}

template<int _iDataFlow>
void CAudioCaptureT<_iDataFlow>::GetPcmBaseInfo(int& nSamples, int& nChannels, int& nBitsPerSample)
{
	nSamples = 48000;// m_nSamplesPerSec;
	nChannels = 2;// m_nChannel;
	nBitsPerSample = 32;// m_nBitsPerSample;
}

template<int _iDataFlow>
bool CAudioCaptureT<_iDataFlow>::Start()
{
	if (IS_FALSE(m_bInited))
		return false;
	if (NOT_NULLPTR(m_hThreadCapture))
		return true;

	capture_thread_data data;
	data.hEventStarted = m_hEventStarted;
	data.hEventStop = m_hEventStop;
	data.pEventHandle = m_pEventHandler;
	data.pDevice = m_pDevice;

	m_hThreadCapture = (HANDLE)_beginthreadex(nullptr, 0, &_CaptureThreadProc, &data, 0, nullptr);
	if (IS_NULLPTR(m_hThreadCapture))
		return false;

	HANDLE ahWaits[2] = { m_hEventStarted, m_hThreadCapture };
	DWORD dwWaitResult = WaitForMultipleObjects(sizeof(ahWaits) / sizeof(ahWaits[0]), ahWaits, false, INFINITE);
	if (WAIT_OBJECT_0 != dwWaitResult)
	{
		Stop();
		return false;
	}

	return true;
}

template<int _iDataFlow>
void CAudioCaptureT<_iDataFlow>::Stop()
{
	if (IS_FALSE(m_bInited))
		return;

	if (NOT_NULLPTR(m_hEventStop) &&
		NOT_NULLPTR(m_hThreadCapture))
	{
		SetEvent(m_hEventStop);
		SafCloseHandle(m_hThreadCapture);
	}
}

template<int _iDataFlow>
IMMDevice * CAudioCaptureT<_iDataFlow>::_GetDefaultDevice()
{
	IMMDevice *pDevice = nullptr;

	IMMDeviceEnumerator *pMMDeviceEnumerator = nullptr;
	HRESULT hr = CoCreateInstance(
		__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pMMDeviceEnumerator);
	if (FAILED(hr))
		return nullptr;

	hr = pMMDeviceEnumerator->GetDefaultAudioEndpoint((EDataFlow)_iDataFlow, eConsole, &pDevice);
	SafRelease(pMMDeviceEnumerator);

	return pDevice;
}

template<int _iDataFlow>
UINT CAudioCaptureT<_iDataFlow>::_CaptureAudio(IMMDevice *pDevice, HANDLE hEventStarted, HANDLE hEventStop, ICaptureEvent *pEventHandle)
{
	HRESULT hr;
	IAudioClient *pAudioClient = nullptr;
	WAVEFORMATEX *pWfx = nullptr;
	REFERENCE_TIME hnsDefaultDevicePeriod(0);
	HANDLE hTimerWakeUp = nullptr;
	IAudioCaptureClient *pAudioCaptureClient = nullptr;
	DWORD nTaskIndex = 0;
	HANDLE hTask = nullptr;
	bool bStarted(false);

	do
	{
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&pAudioClient);
		if (FAILED(hr))
			break;
		hr = pAudioClient->GetDevicePeriod(&hnsDefaultDevicePeriod, nullptr);
		if (FAILED(hr))
			break;
		hr = pAudioClient->GetMixFormat(&pWfx);
		if (FAILED(hr))
			break;
		hTimerWakeUp = CreateWaitableTimer(nullptr, false, nullptr);
		if (IS_NULLPTR(hTimerWakeUp))
			break;
		SetEvent(hEventStarted);

		pEventHandle->OnAdjustCaptureFormat(pWfx);
		hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, StreamFlagT<_iDataFlow>::Get(), 0, 0, pWfx, 0);
		if (FAILED(hr))
			break;
		//m_nSamplesPerSec = pWfx->nSamplesPerSec;
		//m_nChannel = pWfx->nChannels;
		//m_nBitsPerSample = pWfx->wBitsPerSample;

		hr = pAudioClient->GetService(__uuidof(IAudioCaptureClient), (void**)&pAudioCaptureClient);
		if (FAILED(hr))
			break;
		hTask = AvSetMmThreadCharacteristics(/*(LPCSTR)(LPCTSTR)TaskNameT<_iDataFlow>::Get()*/"Capture", &nTaskIndex);
		if (IS_NULLPTR(hTask))
			break;

		LARGE_INTEGER liFirstFire;
		liFirstFire.QuadPart = -hnsDefaultDevicePeriod / 2;
		LONG lTimeBetweenFires = (LONG)hnsDefaultDevicePeriod / 2 / (10 * 1000);
#pragma warning(disable:4800)
		bool bOk = (bool)SetWaitableTimer(hTimerWakeUp, &liFirstFire, lTimeBetweenFires, nullptr, nullptr, false);
		if (IS_FALSE(bOk))
			break;
		hr = pAudioClient->Start();
		if (FAILED(hr))
			break;

		pEventHandle->OnCaptureStart(lTimeBetweenFires);
		bStarted = true;

		HANDLE ahWait[2] = { hEventStop, hTimerWakeUp };
		DWORD  dwWaitResult;
		UINT32 uiNextPacketSize(0);
		BYTE *pData = nullptr;
		UINT32 uiNumFramesToRead;
		DWORD dwFlags;
		
		while (true)
		{
			dwWaitResult = WaitForMultipleObjects(sizeof(ahWait) / sizeof(ahWait[0]), ahWait, false, INFINITE);
			if (WAIT_OBJECT_0 + 1 != dwWaitResult)
				break;				
			hr = pAudioCaptureClient->GetNextPacketSize(&uiNextPacketSize);
			if (FAILED(hr))
				break;
			if (0 == uiNextPacketSize)
				continue;
			hr = pAudioCaptureClient->GetBuffer(
				&pData,
				&uiNumFramesToRead,
				&dwFlags,
				nullptr,
				nullptr);
			if (FAILED(hr))
				break;
			if (0 != uiNumFramesToRead)
			{
				pEventHandle->OnCaptureData(pData, uiNumFramesToRead * pWfx->nBlockAlign);
			}

			pAudioCaptureClient->ReleaseBuffer(uiNumFramesToRead);
		}

	} while (0);

	if (NOT_NULLPTR(hTask))
	{
		AvRevertMmThreadCharacteristics(hTask);
		hTask = nullptr;
	}

	SafRelease(pAudioCaptureClient);

	if (NOT_NULLPTR(pWfx))
	{
		CoTaskMemFree(pWfx);
		pWfx = nullptr;
	}

	if (NOT_NULLPTR(hTimerWakeUp))
	{
		CancelWaitableTimer(hTimerWakeUp);
		CloseHandle(hTimerWakeUp);
		hTimerWakeUp = nullptr;
	}

	if (NOT_NULLPTR(pAudioClient))
	{
		if (IS_TRUE(bStarted))
		{
			pAudioClient->Stop();
			pEventHandle->OnCaptureStop();
		}
		pAudioClient->Release();
		pAudioClient = nullptr;
	}

	return 0;
}

template<int _iDataFlow>
UINT __stdcall CAudioCaptureT<_iDataFlow>::_CaptureThreadProc(LPVOID param)
{

	capture_thread_data *pData = (capture_thread_data*)param;

	CoInitialize(nullptr);

	UINT uiRet = _CaptureAudio(
		pData->pDevice,
		pData->hEventStarted,
		pData->hEventStop,
		pData->pEventHandle);

	CoUninitialize();
	return uiRet;
}
