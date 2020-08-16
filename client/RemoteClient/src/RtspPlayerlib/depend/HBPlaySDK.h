
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HBPLAYSDK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HBPLAYSDK_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#include "HBxCommon.h"
#include "windef.h"
#include "Multimon.H"

#define  HBAPI	extern"C"

//#define		STREAME_REALTIME			STREAM_OPEN_REALTIME
//#define		STREAME_FILE				STREAM_OPEN_FILE

HBAPI	BOOL	__stdcall	HB_PLAY_InitDDraw(HWND hWnd);

HBAPI	BOOL	__stdcall	HB_PLAY_RealeseDDraw();

HBAPI	BOOL	__stdcall	HB_PLAY_OpenFile(long nChl, char *sFile);

HBAPI	BOOL	__stdcall	HB_PLAY_CloseFile(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_Play(long nChl, HWND hWnd=NULL);

HBAPI	BOOL	__stdcall	HB_PLAY_Pause(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_Stop(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_Fast(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_Slow(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_PlayBySingleFrame(long nChl);
HBAPI	BOOL	__stdcall	HB_PLAY_OneByOne(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_PlayBySingleFrameBack(long nChl);
HBAPI	BOOL	__stdcall	HB_PLAY_OneByOneBack(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetFileTime(long nChl);
HBAPI	DWORD	__stdcall	HB_PLAY_GetFileTimeMilliSec(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetFileFrames(long nChl);
HBAPI	DWORD	__stdcall	HB_PLAY_GetFileTotalFrames(long nChl);

HBAPI	long	__stdcall	HB_PLAY_GetPlayedFrames(long nChl);
HBAPI	long	__stdcall	HB_PLAY_GetPlayedFrameNum(long nChl);

HBAPI	long	__stdcall	HB_PLAY_GetCurrFrameNum(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetPlayedTime(long nChl, DWORD dwTime);

HBAPI	BOOL	__stdcall	HB_PLAY_SetPlayPos(long nChl, float dPos);

HBAPI	float	__stdcall	HB_PLAY_GetPlayPos(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetFileEndMsg(long nChl, HWND hWnd, UINT nMsg);

HBAPI	BOOL	__stdcall	HB_PLAY_OpenSound(long nChl);
HBAPI	BOOL	__stdcall	HB_PLAY_PlaySound(long nChl);
HBAPI	BOOL	__stdcall	HB_PLAY_CloseSound(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_RefreshPlay(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_GetPictureSize(long nChl, long *pWidth, long *pHeight);

HBAPI  BOOL		__stdcall	HB_PLAY_SetDisplayCallBack(long nChl, void (CALLBACK *DisplayCBFun)(long nChl,  char *pBuf, long nSize, long nWidth, long hHeight, long nStamp, long nType, long nReserved));

HBAPI	BOOL	__stdcall	HB_PLAY_ConvertToBMPFile(long nChl, char *pBuf, long nSize, long nWidth, long nHeight, long nType,  char *sFileName);

HBAPI  BOOL		__stdcall	HB_PLAY_SetDecCallBack(long nChl, void (CALLBACK* DecCBFun)(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2,VIDEO_TIME ets),long nOutFormat=0);

HBAPI  BOOL		__stdcall	HB_PLAY_SetDecCallBackEx(long nChl, void (CALLBACK* DecCBFun)(long nPort, char * pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2 ,VIDEO_TIME ets),long nReserved1, long nReserved2,long nOutFormat);

//add by cui for 成朗08.2.26
HBAPI	BOOL	__stdcall	HB_PLAY_SetParseCallBack(long nChl, void (CALLBACK *SrcDataParseCBFun)(long nChl,char *SrcDataBuf,long nFrameType,long nReserved1,long nReserved2,VIDEO_TIME ets),long nReserved1,long nReserved2 = 0);
HBAPI	BOOL	__stdcall HB_PLAY_SetParseOnly(long nChl,BOOL bParseOnly);

HBAPI  BOOL		__stdcall	HB_PLAY_SetPlayOption(long nChl, long bEnableDisplay, long bEnableSound);

HBAPI	BOOL	__stdcall	HB_PLAY_SetPicQuality(long nChl, BOOL bHighQuality);

HBAPI	BOOL	__stdcall	HB_PLAY_GetPicQuality(long nChl, BOOL *bHighQuality);

HBAPI	BOOL	__stdcall	HB_PLAY_SetVolume(long nChl, WORD nVolume);

HBAPI	WORD	__stdcall	HB_PLAY_GetVolume(long nChl);
	
HBAPI	BOOL	__stdcall	HB_PLAY_SetOverlayMode(long nChl, BOOL bOverlayMode, COLORREF colorKey);

HBAPI	DWORD	__stdcall	HB_PLAY_GetColorKey(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_GetOverlayMode(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetPlayTime(long nChl, DWORD dwTime);
	
HBAPI	DWORD	__stdcall	HB_PLAY_GetPlayTime(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetCurrFrameRate(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetFileHeadLength(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetCurrentFrameNum(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetCurrentFrameNum(long nChl, DWORD dwFrameNum);

HBAPI	BOOL	__stdcall	HB_PLAY_GetKeyFramePos(long nChl, DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

HBAPI	BOOL	__stdcall	HB_PLAY_GetPriorKeyFramePos(long nChl, DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

HBAPI	BOOL	__stdcall	HB_PLAY_GetNextKeyFramePos(long nChl, DWORD nValue, DWORD nType, PFRAME_POS pFramePos);

HBAPI	BOOL	__stdcall	HB_PLAY_SetDisplayRegion(long nChl, DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);

HBAPI	BOOL	__stdcall	HB_PLAY_OpenStream(long nChl, char *pFileHeadBuf, DWORD nSize, DWORD nBufPoolSize);

HBAPI	long	__stdcall	HB_PLAY_OpenStreamEx(char *pFileHeadBuf, DWORD nSize, DWORD nBufPoolSize);

HBAPI	BOOL	__stdcall	HB_PLAY_SetStreamOpenMode(long nChl, DWORD nMode);

HBAPI	BOOL	__stdcall	HB_PLAY_InputData(long nChl, char *pBuf, DWORD nSize, DWORD nDataType=0);

HBAPI	BOOL	__stdcall	HB_PLAY_InputVideoData(long nChl,char * pBuf,DWORD nSize);

HBAPI	BOOL	__stdcall	HB_PLAY_InputAudioData(long nChl,char * pBuf,DWORD nSize);

HBAPI	BOOL	__stdcall	HB_PLAY_CloseStream(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetStreamOpenMode(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetSourceBufferRemain(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_ResetSourceBuffer(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetSourceBufferCB(long nChl, DWORD nThreShold,void (CALLBACK * SourceBufCallBack)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);

HBAPI	BOOL	__stdcall	HB_PLAY_ResetSourceBufFlag(long nChl);
	
HBAPI	BOOL	__stdcall	HB_PLAY_SetMsgWnd(long nChl, HWND hWnd);

HBAPI	DWORD	__stdcall	HB_PLAY_GetLastError(long nChl);

HBAPI	DWORD	__stdcall	HB_PLAY_GetSdkVersion(long nChl);

HBAPI	BOOL	__stdcall	HB_PLAY_SetPlaySpeed(long nChl, long dwSpeed, BOOL bSlow=false);
HBAPI	BOOL	__stdcall	HB_PLAY_SnapShot(long nChl, char *sFile);
HBAPI	double	__stdcall	HB_PLAY_GetDynamicBPS(long nChl);
HBAPI	double	__stdcall	HB_PLAY_GetAverageBPS(long nChl);

HBAPI	void	__stdcall	HB_PLAY_EnableIndexThread(BOOL bEnable);

HBAPI	BOOL	__stdcall	HB_PLAY_GetFileStartTime(long nChl, char *pSystemTime);
HBAPI	BOOL	__stdcall	HB_PLAY_SetStreamSpeed(long nChl, int iSpeed, BOOL bFast);
HBAPI	void	__stdcall	HB_PLAY_SetEndlessStream(long	nChl, BOOL	bEndless);

// for zhuan
typedef	void*	HDRAW;	 
typedef	void*	H_WAVE;

HBAPI	long	__stdcall	HB_PLAY_OpenFileEx(char *sFile);

// special interfaces.
// 1500 
HBAPI	void*	__stdcall	HB_PLAY_DecInit(int width,int height);
HBAPI	void*	__stdcall	HB_PLAY_DecInitEx(int width,int height,int out_fmt);
HBAPI	int		__stdcall	HB_PLAY_DecFrame(void* handle,void* stream,int size, void* image, int quality);
HBAPI	int		__stdcall	HB_PLAY_DecFrameEx(void* handle,void* stream,int size, void* image, int quality);
HBAPI	void	__stdcall	HB_PLAY_DecFree(void *handle);

// 1800
HBAPI	void*	__stdcall	HB_PLAY_DecInit18(int width,int height);
HBAPI	int		__stdcall	HB_PLAY_DecFrame18(void* handle,void* stream,int size, void* image, int quality);
HBAPI	void	__stdcall	HB_PLAY_DecFree18(void *handle);

HBAPI	void*	__stdcall	HB_PLAY_DecInit18Ex(int width,int height, int colorspace);
HBAPI	int		__stdcall	HB_PLAY_DecFrame18Ex(void* handle,void* stream, int size, void* image, int quality);

// display
HBAPI	HDRAW	__stdcall	HB_PLAY_InitDirectDraw(long width, long height);
HBAPI	BOOL	__stdcall	HB_PLAY_ShowPicture(void *hdraw,long hwnd, unsigned char *image, long width, long height);
HBAPI	BOOL	__stdcall	HB_PLAY_ShowPictureEx(void *hdraw,unsigned char *image, long width,long height);
HBAPI	BOOL	__stdcall	HB_PLAY_AddWindow(void *hdraw, long hwnd, long x, long y, long cx, long cy);
HBAPI	BOOL	__stdcall	HB_PLAY_DelWindow(void *hdraw, long hwnd);

HBAPI	void	__stdcall	HB_PLAY_RestoreSurface(void *hdraw);
HBAPI	void	__stdcall	HB_PLAY_ReleaseDDraw(void *hdraw);

// audio
HBAPI	H_WAVE	__stdcall	HB_PLAY_WaveOpen();
// 0 <= volume <= 0xffff
HBAPI	void	__stdcall	HB_PLAY_WaveSetVolume(H_WAVE *h, long volume);
HBAPI	void	__stdcall	HB_PLAY_WaveGetVolume(H_WAVE *h, long &volume);
HBAPI	BOOL	__stdcall	HB_PLAY_WaveWrite(H_WAVE *h, char *buff, long size);
HBAPI	BOOL	__stdcall	HB_PLAY_WaveReset(H_WAVE *h);
HBAPI	BOOL	__stdcall	HB_PLAY_WaveClose(H_WAVE *h);


// 2006-8-23 for 九鼎
HBAPI	BOOL	__stdcall	HB_PLAY_GetKeyFramePosJD(long nChl, long lTime, long *iFilePos, long *iFrameSize);

HBAPI	BOOL	__stdcall	HB_PLAY_GetNextFramePosJD(long nChl, long *iFilePos, long *iFrameSize, long *iType);

// 获得流格式类型
HBAPI	UINT	__stdcall	HB_PLAY_GetProductID(long nChl);


// for 飞龙
HBAPI	BOOL __stdcall	HB_PLAY_DecodeAudioFrame(long nChl, char *pBuff, DWORD dwSize);
HBAPI	BOOL __stdcall	HB_PLAY_DecodeOneFrame(long nChl, char *pBuff, DWORD dwSize,UINT nQuality);
HBAPI	BOOL __stdcall	HB_PLAY_PlayEx(long nChl, HWND hWnd/*=NULL*/);


HBAPI	long __stdcall	HB_PLAY_CheckFrameInfo(char *stream, long streamsize, long *pFrameType, long *pFrameSize);
HBAPI	void __stdcall	HB_PLAY_SetWindowClip(long nChl, BOOL bEnable, int left, int right, int top, int bottom);

HBAPI	UINT __stdcall	HB_PLAY_GetStreamType(long nChl);


HBAPI	BOOL __stdcall	HB_PLAY_SetDCCallBack( long nChl, long ( __stdcall * CallBack )( long lType, long lPara1, long lPara2) );

HBAPI	BOOL __stdcall	HB_PLAY_SnapPicture(long nChl, char *pBuff, long *plSize, long *plWidth, long *plHeight, long *plType);

HBAPI	BOOL __stdcall HB_PLAY_RegisterDrawDCFun(long nChl,void (CALLBACK* DrawDCFun)(long nChl,HDC hDc,long nReserved),long nReserved);

HBAPI	BOOL __stdcall	HB_PLAY_GetFrameInfo(char *stream, long streamsize, long *width, long *height);

HBAPI	BOOL __stdcall HB_PLAY_UnionFiles(char *pFileDestination, char *pFileSource);
HBAPI	int	 __stdcall HB_PLAY_SplitFiles(char *pFileSource, char *pFileDestination, 
									   unsigned int StartTime, unsigned int Length);


//for 华为

//初始化,产生唯一个句柄，多次调用返回句柄不同，多路视频会多次调用
HANDLE WINAPI HBGK_CreateInstance(char *pFileHeadBuf = NULL, DWORD nSize = 0);

//释放句柄，解码库释放资源
void WINAPI HBGK_ReleaseInstance(HANDLE hStreamPlayer);

//初始化播放，指定播放界面句柄
BOOL WINAPI HBGK_InitPlayInstance(HANDLE hStreamPlayer,HWND hWnd);

//开始播放
BOOL WINAPI HBGK_StartPlayStream(HANDLE hStreamPlayer);

//停止播放
void WINAPI HBGK_StopPlayStream(HANDLE hStreamPlayer);

//向解码器中输入一个帧，音频视频皆通过此接口传入
BOOL WINAPI HBGK_SendOneFrame(HANDLE hStreamPlayer,void * pFrame, int length);

//抓图
BOOL WINAPI HBGK_CaptureBitmap(HANDLE hStreamPlayer,LPCTSTR sFileName);

//指定播放区域，用于数字缩放
//RECT全0表示恢复视频大小
BOOL WINAPI HBGK_SetDisplayRect(HANDLE hStreamPlayer,RECT  rect);

//获取播放区域
//获取播放区域，即上述函数设置后调用可以获取
BOOL WINAPI HBGK_GetDisplayRect(HANDLE hStreamPlayer,RECT &rect);

//播放声音
BOOL WINAPI HBGK_Listen(HANDLE hStreamPlayer,BOOL bListen);

//设置音量，声音大小0到100
BOOL WINAPI HBGK_SetVolume(HANDLE hStreamPlayer,LONG volume);

//获取当前音量
BOOL WINAPI HBGK_GetVolume(HANDLE hStreamPlayer,LONG &volume);

