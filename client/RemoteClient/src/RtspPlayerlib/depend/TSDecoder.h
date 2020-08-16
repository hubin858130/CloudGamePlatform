#ifndef TS_DECODER_H
#define TS_DECODER_H

#ifdef DECODER_EXPORTS
#define DECODER_API __declspec(dllexport)
#else
#define DECODER_API __declspec(dllimport)
#endif

DECODER_API HANDLE WINAPI TS_CreateInstance();
DECODER_API void WINAPI TS_ReleaseInstance(HANDLE hStreamPlayer);
DECODER_API BOOL WINAPI TS_InitPlayInstance(HANDLE hStreamPlayer, HWND hWnd);
DECODER_API BOOL WINAPI TS_StartPlayStream(HANDLE hStreamPlayer);
DECODER_API BOOL WINAPI TS_SendOneFrame(HANDLE hStreamPlayer, void* pFrame,
											   int length);
DECODER_API void WINAPI TS_SetVideoSize(HANDLE hStreamPlayer, int nWidth, 
											   int nHeight);
DECODER_API BOOL WINAPI TS_SetVolume(HANDLE hStreamPlayer, LONG volume);
DECODER_API void WINAPI TS_StopPlayStream(HANDLE hStreamPlayer);
DECODER_API BOOL WINAPI TS_GetVolume(HANDLE hStreamPlayer, LONG &volume);

DECODER_API BOOL WINAPI TS_Listen(HANDLE hStreamPlayer, BOOL bListen);

DECODER_API BOOL WINAPI TS_CaptureBitmap(HANDLE hStreamPlayer, LPCTSTR sFileName);

DECODER_API BOOL WINAPI TS_SetDisplayRect(HANDLE hStreamPlayer, RECT  rect);

DECODER_API BOOL WINAPI TS_GetDisplayRect(HANDLE hStreamPlayer, RECT &rect);

DECODER_API BOOL WINAPI TS_SendVideoFrame(LONG hStreamPlayer, BYTE* pData, LONG Length, LONG Timestamp);

DECODER_API BOOL WINAPI TS_SendAudioFrame(LONG hStreamPlayer, BYTE* pData, LONG Length, LONG Timestamp);

DECODER_API BOOL WINAPI TS_InitVideoProperty(LONG hStreamPlayer, LONG nWidth, LONG nHeight, LONG FrameRate, LONG Bitrate);

DECODER_API BOOL WINAPI TS_InitAudioProperty(LONG hStreamPlayer, LONG SampleRate, LONG nChannels, LONG Bitrate);

#endif