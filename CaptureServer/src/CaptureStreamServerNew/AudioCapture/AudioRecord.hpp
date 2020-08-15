
/*
*	author: zyb
*   \brief	
*		AudioRecordT<eRender>
*		AudioRecordT<eCapture>
*/


#pragma once

#include "AudioCapture.hpp"
#include <list>

namespace
{
	typedef struct 
	{
		INT		iDataLen;
		LPBYTE	pData;
	}Audio_Data,	*PAudio_Data;

	template<int _iDataFlow>
	struct FileNameT{};

	template<>
	struct FileNameT<eRender>
	{
		static wchar_t* Get()
		{
			return L"./output.wav";
		}
	};

	template<>
	struct FileNameT<eCapture>
	{
		static wchar_t* Get()
		{
			return L"./input.wav";
		}
	};
}

typedef void(*AacDataCallback)(char* szBuffer, int nSize);


template<int _iDataFlow>
class CAudioRecordT : public ICaptureEvent
{
public:
	typedef CAudioCaptureT<_iDataFlow>	CaptureType;
	typedef std::list<Audio_Data>		ListType;
	typedef typename ListType::iterator	IteratorType;
	typedef std::wstring				StrType;

	AacDataCallback						m_AacDataCallback;

public:
	CAudioRecordT();
	~CAudioRecordT();

	bool StartCapture(AacDataCallback dataCallback);
	void StopCapture();
	bool IsCapturing() const;

	void SetFilePath(wchar_t* pFilePath);
	bool SaveFile();

	void GetPcmBaseInfo(int& nSamples, int& nChannels, int& nBitsPerSample);

public:
	virtual void OnCaptureStart(DWORD dwInterval) override;
	virtual void OnCaptureStop() override;
	virtual void OnAdjustCaptureFormat(WAVEFORMATEX *pFormat) override;
	virtual void OnCaptureData(LPBYTE pData, INT iDataLen) override;

private:
	void _ClearData();

private:
	CaptureType		m_Capture;
	WAVEFORMATEX*	m_pFormat;

	ListType		m_DataList;
	INT				m_iDataLen;

	StrType			m_strFilePath;
};

//void Pcm2AacDecordThread(void* pParam)
//{//初始化faac编码器
//	//设置PCM 参数
//	template<int _iDataFlow>
//	CAudioRecordT<_iDataFlow>* pThis = (CAudioRecordT*)pParam;
//	unsigned long   nSampleRate = 48000;
//	unsigned int    nChannels = 2;
//	unsigned int    nPCMBitSize = 16;
//	unsigned long   nInputSamples = 0;
//	unsigned long   nMaxOutputBytes = 0;
//	faacEncHandle   hEncoder = { 0 };
//	//while ()
//	//{
//
//	//}
//
//}

template<int _iDataFlow>
CAudioRecordT<_iDataFlow>::CAudioRecordT() :
m_pFormat(nullptr),
m_iDataLen(0)
{
	m_strFilePath = FileNameT<_iDataFlow>::Get();
}

template<int _iDataFlow>
CAudioRecordT<_iDataFlow>::~CAudioRecordT()
{
	_ClearData();
}

template<int _iDataFlow>
bool CAudioRecordT<_iDataFlow>::StartCapture(AacDataCallback dataCallback)
{
	m_AacDataCallback = dataCallback;

	bool bRet = m_Capture.IsCapturing();

	if (IS_FALSE(bRet))
	{
		bRet = m_Capture.Init(this);
		if (IS_TRUE(bRet))
		{
			bRet = m_Capture.Start();
		}	
	}

	return bRet;
}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::StopCapture()
{
	bool bResult = m_Capture.IsCapturing();
	if (IS_TRUE(bResult))
	{
		m_Capture.Stop();
		m_Capture.UnInit();
	}
}

template<int _iDataFlow>
bool CAudioRecordT<_iDataFlow>::IsCapturing() const
{
	return m_Capture.IsCapturing();
}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::GetPcmBaseInfo(int& nSamples, int& nChannels, int& nBitsPerSample)
{
	m_Capture.GetPcmBaseInfo(nSamples, nChannels, nBitsPerSample);
}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::_ClearData()
{
	LPBYTE p = (LPBYTE)m_pFormat;
	SafDelete_A(p);

	IteratorType itr = m_DataList.begin();
	while (itr != m_DataList.end())
	{
		delete[] itr->pData;
		itr++;
	}

	m_DataList.clear();
	m_iDataLen = 0;
}

template<int _iDataFlow>
void  CAudioRecordT<_iDataFlow>::OnCaptureStart(DWORD dwInterval)
{

}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::OnCaptureStop()
{

}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::OnAdjustCaptureFormat(WAVEFORMATEX *pFormat)
{
	_ClearData();

	int iDataLen = sizeof(WAVEFORMATEX) + pFormat->cbSize;
	LPBYTE pData = new (std::nothrow) BYTE[iDataLen];
	if (NOT_NULLPTR(pData))
	{
		memcpy_s(pData, iDataLen, pFormat, iDataLen);
		m_pFormat = (WAVEFORMATEX*)pData;
	}
}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::OnCaptureData(LPBYTE pData, INT iDataLen)
{
	Audio_Data item;
	item.iDataLen = iDataLen;
	item.pData = new (std::nothrow) BYTE[iDataLen];
	if (NOT_NULLPTR(item.pData))
	{
		memcpy_s(item.pData, iDataLen, pData, iDataLen);
		//m_DataList.push_back(item);//huqb
		//m_iDataLen += iDataLen;
		if (m_AacDataCallback != NULL)
		{
			m_AacDataCallback((char*)item.pData, iDataLen);
		}
		delete[] item.pData;
		item.pData = NULL;
	}
}

template<int _iDataFlow>
void CAudioRecordT<_iDataFlow>::SetFilePath(wchar_t* pFilePath)
{
	if (IS_NULLPTR(pFilePath))
		return;
	m_strFilePath = pFilePath;
}

///////////////////////////////////////////////from msdn///////////////////////////////////////////////
namespace{
	//
	//  WAV file writer.
	//
	//  This is a VERY simple .WAV file writer.
	//

	//
	//  A wave file consists of:
	//
	//  RIFF header:    8 bytes consisting of the signature "RIFF" followed by a 4 byte file length.
	//  WAVE header:    4 bytes consisting of the signature "WAVE".
	//  fmt header:     4 bytes consisting of the signature "fmt " followed by a WAVEFORMATEX 
	//  WAVEFORMAT:     <n> bytes containing a waveformat structure.
	//  DATA header:    8 bytes consisting of the signature "data" followed by a 4 byte file length.
	//  wave data:      <m> bytes containing wave data.
	//
	//
	//  Header for a WAV file - we define a structure describing the first few fields in the header for convenience.
	//
	struct WAVEHEADER
	{
		DWORD   dwRiff;                     // "RIFF"
		DWORD   dwSize;                     // Size
		DWORD   dwWave;                     // "WAVE"
		DWORD   dwFmt;                      // "fmt "
		DWORD   dwFmtSize;                  // Wave Format Size
	};

	//  Static RIFF header, we'll append the format to it.
	const BYTE WaveHeader[] =
	{
		'R', 'I', 'F', 'F', 0x00, 0x00, 0x00, 0x00, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 0x00, 0x00, 0x00, 0x00
	};

	//  Static wave DATA tag.
	const BYTE WaveData[] = { 'd', 'a', 't', 'a' };
}
///////////////////////////////////////////////////////////////////////////////////////////////
int nnnn = 0;
template<int _iDataFlow>
bool CAudioRecordT<_iDataFlow>::SaveFile()
{
	DWORD dwWaveFileSize = sizeof(WAVEHEADER) + sizeof(WAVEFORMATEX) + m_pFormat->cbSize + sizeof(WaveData) + sizeof(DWORD) + m_iDataLen;
	DWORD dwWaveFileNoDataSize = dwWaveFileSize - m_iDataLen;
	BYTE *pWaveFileNoData = new (std::nothrow) BYTE[dwWaveFileSize];
	BYTE *pWaveFileNoDataCopy = pWaveFileNoData;

	if (IS_NULLPTR(pWaveFileNoDataCopy))
	{
		return false;
	}

	WAVEHEADER *pWaveHeader = reinterpret_cast<WAVEHEADER *>(pWaveFileNoDataCopy);
	CopyMemory(pWaveFileNoDataCopy, WaveHeader, sizeof(WaveHeader));
	pWaveFileNoDataCopy += sizeof(WaveHeader);
	pWaveHeader->dwSize = dwWaveFileSize - (2 * sizeof(DWORD));
	pWaveHeader->dwFmtSize = sizeof(WAVEFORMATEX) + m_pFormat->cbSize;

	CopyMemory(pWaveFileNoDataCopy, m_pFormat, sizeof(WAVEFORMATEX) + m_pFormat->cbSize);
	pWaveFileNoDataCopy += sizeof(WAVEFORMATEX) + m_pFormat->cbSize;

	CopyMemory(pWaveFileNoDataCopy, WaveData, sizeof(WaveData));
	pWaveFileNoDataCopy += sizeof(WaveData);
	*(reinterpret_cast<DWORD*>(pWaveFileNoDataCopy)) = static_cast<DWORD>(m_iDataLen);

	HANDLE FileHandle = CreateFile((LPCSTR)(LPCTSTR)m_strFilePath.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		SafDelete_A(pWaveFileNoData)
		return false;
	}

	DWORD dwWritten = 0;
	WriteFile(FileHandle, pWaveFileNoData, dwWaveFileNoDataSize, &dwWritten, nullptr);

	FILE* p = NULL;
	char sz[50];
	sprintf_s(sz, "test_%d.pcm", nnnn++);
	fopen_s(&p, sz, "wb");

	for (IteratorType it = m_DataList.begin(); it != m_DataList.end(); it++)
	{
		fwrite(it->pData, it->iDataLen, 1, p);
		WriteFile(FileHandle, it->pData, it->iDataLen, &dwWritten, nullptr);
	}
	fclose(p);

	CloseHandle(FileHandle);

	SafDelete_A(pWaveFileNoData);

	return true;
}

typedef CAudioRecordT<eCapture>		CInputRecord;
typedef CAudioRecordT<eRender>		COutputRecord;