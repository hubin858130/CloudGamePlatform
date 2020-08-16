///////////////////////////////////////////////////////////////////
//File:			HikPlayMpeg4.h
//Date:			2003-12-06
//Description:	Interface for HikPlayM4.dll
//Copyright:	Copyright(C)HangZhou Hikvision Digital Technology Co,.Ltd 2002-2008. All rights reserved.
///////////////////////////////////////////////////////////////////
#ifndef _HIK_PLAY_M4
#define _HIK_PLAY_M4

#if defined( _WINDLL)
	#define HIK_PLAYM4_API  extern "C"__declspec(dllexport) 
#else 
	#define HIK_PLAYM4_API  extern "C" //__declspec(dllimport) 
#endif

//Max channel numbers
#define HIK_PLAYM4_MAX_SUPPORTS 100
//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100
//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 
//BUFFER TYPE
#define BUF_VIDEO_SRC 1
#define BUF_AUDIO_SRC 2
#define BUF_VIDEO_RENDER 3
#define BUF_AUDIO_RENDER 4
//Error code
#define  HIK_PLAYM4_NOERROR					0	//no error
#define	 HIK_PLAYM4_PARA_OVER				1	//input parameter is invalid;
#define  HIK_PLAYM4_ORDER_ERROR				2	//The order of the function to be called is error.
#define	 HIK_PLAYM4_TIMER_ERROR				3	//Create multimedia clock failed;
#define  HIK_PLAYM4_DEC_VIDEO_ERROR			4	//Decode video data failed.
#define  HIK_PLAYM4_DEC_AUDIO_ERROR			5	//Decode audio data failed.
#define	 HIK_PLAYM4_ALLOC_MEMORY_ERROR		6	//Allocate memory failed.
#define  HIK_PLAYM4_OPEN_FILE_ERROR			7	//Open the file failed.
#define  HIK_PLAYM4_CREATE_OBJ_ERROR		8	//Create thread or event failed
#define  HIK_PLAYM4_CREATE_DDRAW_ERROR		9	//Create DirectDraw object failed.
#define  HIK_PLAYM4_CREATE_OFFSCREEN_ERROR 10	//failed when creating off-screen surface.
#define  HIK_PLAYM4_BUF_OVER			   11	//buffer is overflow
#define  HIK_PLAYM4_CREATE_SOUND_ERROR	   12	//failed when creating audio device.	
#define	 HIK_PLAYM4_SET_VOLUME_ERROR	   13	//Set volume failed
#define  HIK_PLAYM4_SUPPORT_FILE_ONLY	   14	//The function only support play file.
#define  HIK_PLAYM4_SUPPORT_STREAM_ONLY	   15	//The function only support play stream.
#define  HIK_PLAYM4_SYS_NOT_SUPPORT		   16	//System not support.
#define  HIK_PLAYM4_FILEHEADER_UNKNOWN     17	//No file header.
#define  HIK_PLAYM4_VERSION_INCORRECT	   18	//The version of decoder and encoder is not adapted.  
#define  HIK_PALYM4_INIT_DECODER_ERROR     19	//Initialize decoder failed.
#define  HIK_PLAYM4_CHECK_FILE_ERROR	   20	//The file data is unknown.
#define  HIK_PLAYM4_INIT_TIMER_ERROR	   21	//Initialize multimedia clock failed.
#define	 HIK_PLAYM4_BLT_ERROR			   22	//Blt failed.
#define  HIK_PLAYM4_UPDATE_ERROR		   23	//Update failed.
#define  HIK_PLAYM4_OPEN_FILE_ERROR_MULTI  24   //openfile error, streamtype is multi
#define  HIK_PLAYM4_OPEN_FILE_ERROR_VIDEO  25   //openfile error, streamtype is video
#define  HIK_PLAYM4_JPEG_COMPRESS_ERROR    26   //JPEG compress error
#define  HIK_PLAYM4_EXTRACT_NOT_SUPPORT    27	//Don't support the version of this file.
#define  HIK_PLAYM4_EXTRACT_DATA_ERROR     28	//extract video data failed.

//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7
//capability
#define SUPPORT_DDRAW		1 
#define SUPPORT_BLT         2 
#define SUPPORT_BLTFOURCC   4 
#define SUPPORT_BLTSHRINKX  8 
#define SUPPORT_BLTSHRINKY  16
#define SUPPORT_BLTSTRETCHX 32
#define SUPPORT_BLTSTRETCHY 64
#define SUPPORT_SSE         128
#define SUPPORT_MMX			256 

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
	long nWidth;
	long nHeight;
	long nStamp;
	long nType;
	long nFrameRate;
}FRAME_INFO;

//Frame 
typedef struct{
	char *pDataBuf;
	long  nSize;
	long  nFrameNum;
	BOOL  bIsAudio;
	long  nReserved;
}FRAME_TYPE;
//////////////////////////////////////////////////////////////////////////////
//API
//////////////////////////////////////////////////////////////////////////////

////////////////ver 1.0///////////////////////////////////////
//Initialize DirecDraw.Now invalid.
HIK_PLAYM4_API BOOL __stdcall  Hik_PlayM4_InitDDraw(HWND hWnd);
//Release directDraw; Now invalid.
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_RealeseDDraw();

HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_OpenFile(LONG nPort,LPSTR sFileName);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_CloseFile(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_Play(LONG nPort, HWND hWnd);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_Stop(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_Pause(LONG nPort,DWORD nPause);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_Fast(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_Slow(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_OneByOne(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetPlayPos(LONG nPort,float fRelativePos);
HIK_PLAYM4_API float __stdcall Hik_PlayM4_GetPlayPos(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetVolume(LONG nPort,WORD nVolume);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_StopSound();
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_PlaySound(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_CloseStream(LONG nPort);
HIK_PLAYM4_API int  __stdcall  Hik_PlayM4_GetCaps();
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetFileTime(LONG nPort);
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetPlayedTime(LONG nPort);
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetPlayedFrames(LONG nPort);

////////////////ver 2.0 added///////////////////////////////////////
HIK_PLAYM4_API BOOL __stdcall	Hik_PlayM4_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
HIK_PLAYM4_API BOOL __stdcall	Hik_PlayM4_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved));
HIK_PLAYM4_API BOOL __stdcall	Hik_PLayM4_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
HIK_PLAYM4_API BOOL __stdcall   Hik_PlayM4_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetFileTotalFrames(LONG nPort);
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetCurrentFrameRate(LONG nPort);
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetPlayedTimeEx(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall	Hik_PlayM4_SetPlayedTimeEx(LONG nPort,DWORD nTime);
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetCurrentFrameNum(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall	Hik_PlayM4_SetStreamOpenMode(LONG nPort,DWORD nMode);
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetFileHeadLength();
HIK_PLAYM4_API DWORD __stdcall	Hik_PlayM4_GetSdkVersion();

////////////////ver 2.2 added///////////////////////////////////////
HIK_PLAYM4_API DWORD __stdcall  Hik_PlayM4_GetLastError(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_RefreshPlay(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetPicQuality(LONG nPort,BOOL bHighQuality);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_PlaySoundShare(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_StopSoundShare(LONG nPort);

////////////////ver 2.4 added///////////////////////////////////////
HIK_PLAYM4_API LONG __stdcall Hik_PlayM4_GetStreamOpenMode(LONG nPort);
HIK_PLAYM4_API LONG __stdcall Hik_PlayM4_GetOverlayMode(LONG nPort);
HIK_PLAYM4_API COLORREF __stdcall Hik_PlayM4_GetColorKey(LONG nPort);
HIK_PLAYM4_API WORD __stdcall Hik_PlayM4_GetVolume(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetSourceBufferRemain(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_ResetSourceBuffer(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBufCallBack)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_ResetSourceBufFlag(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDisplayBuf(LONG nPort,DWORD nNum);
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetDisplayBuf(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_OneByOneBack(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetFileRefCallBack(LONG nPort, void (__stdcall *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
#if (WINVER > 0x0400)
//Note: These funtion must be builded under win2000 or above with Microsoft Platform sdk.
//	    You can download the sdk from "http://www.microsoft.com/msdownload/platformsdk/sdkupdate/";
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_InitDDrawDevice();
HIK_PLAYM4_API void __stdcall Hik_PlayM4_ReleaseDDrawDevice();
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetDDrawDeviceTotalNums();
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,HMONITOR *hhMonitor);
HIK_PLAYM4_API int  __stdcall  Hik_PlayM4_GetCapsEx(DWORD nDDrawDeviceNum);
#endif
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_ThrowBFrameNum(LONG nPort,DWORD nNum);

////////////////ver 2.5 added///////////////////////////////////////
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDisplayType(LONG nPort,LONG nType);
HIK_PLAYM4_API long __stdcall Hik_PlayM4_GetDisplayType(LONG nPort);

////////////////ver 3.0 added///////////////////////////////////////
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDecCBStream(LONG nPort,DWORD nStream);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
#if (WINVER > 0x0400)
//Note: The funtion must be builded under win2000 or above with Microsoft Platform sdk.
//	    You can download the sdk from http://www.microsoft.com/msdownload/platformsdk/sdkupdate/;
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
#endif
/////////////////v3.2 added/////////////////////////////////////////

HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_CloseStreamEx(LONG nPort);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_RegisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
//////////////////v3.4/////////////////////////////////////////////////////
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_ResetBuffer(LONG nPort,DWORD nBufType);
HIK_PLAYM4_API DWORD __stdcall Hik_PlayM4_GetBufferValue(LONG nPort,DWORD nBufType);
//////////////////V3.6/////////////////////////////////////////////////////////
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (__stdcall * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetAudioCallBack(LONG nPort, void (__stdcall * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort,long nUser),long nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetOriginalFrameCallBack(LONG nPort, BOOL bIsChange,BOOL bNormalSpeed,long nStartFrameNum,long nStartStamp,long nFileHeader,void(CALLBACK *funGetOrignalFrame)(long nPort,FRAME_TYPE *frameType, long nUser),long nUser);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetFileSpecialAttr(LONG nPort, DWORD *pTimeStamp,DWORD *pFileNum ,DWORD *pReserved);
//////////////////V4.7.0.0/////////////////////////////////////////////////////////
//convert yuv to jpeg
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_ConvertToJpegFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetJpegQuality(long nQuality);
//set deflash
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_SetDeflash(LONG nPort,BOOL bDeflash);
//input filehead
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_InputFileHead(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize);
//////////////////V4.8.0.0/////////////////////////////////////////////////////////
//check discontinuous frame number as error data?
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_CheckDiscontinuousFrameNum(LONG nPort, BOOL bCheck);
//get bmp or jpeg
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetBMP(LONG nPort,PBYTE pBitmap,DWORD nBufSize,DWORD* pBmpSize);
HIK_PLAYM4_API BOOL __stdcall Hik_PlayM4_GetJPEG(LONG nPort,PBYTE pJpeg,DWORD nBufSize,DWORD* pJpegSize);
//dec call back mend
HIK_PLAYM4_API BOOL __stdcall	Hik_PlayM4_SetDecCallBackMend(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2), long nUser);

#endif
