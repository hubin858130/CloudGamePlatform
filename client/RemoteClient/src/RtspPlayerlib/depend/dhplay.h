    /********************************************************************
 * 文件: dhplay.h
 * 版权:
 * 作者: 周国锋, 王卫东
 * 创建: 2006.12
	purpose:	用于提供给用户做二次开发提供函数接口的定义和说明
*********************************************************************/
#ifndef _DHPLAY_H
#define _DHPLAY_H

#define PLAYSDK_API  __declspec(dllexport)

#define CALLMETHOD __stdcall
#define CALLBACK __stdcall

#define  FUNC_MAX_PORT 101              //最大播放通道数
//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100
//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 
//缓冲类型
#define BUF_VIDEO_SRC 1    //视频源缓冲        
#define BUF_AUDIO_SRC 2    //音频源缓冲
#define BUF_VIDEO_RENDER 3  //解码后视频数据缓冲
#define BUF_AUDIO_RENDER 4  //解码后音频数据缓冲

//错误类型
#define	DH_PLAY_NOERROR					0              //没有错误；
#define DH_PLAY_PARA_OVER				1              //输入参数非法；
#define DH_PLAY_ORDER_ERROR				2              //调用顺序不对；
#define DH_PLAY_TIMER_ERROR				3              //多媒体时钟设置失败；
#define DH_PLAY_DEC_VIDEO_ERROR			4	           //视频解码失败；
#define DH_PLAY_DEC_AUDIO_ERROR			5	           //音频解码失败；
#define DH_PLAY_ALLOC_MEMORY_ERROR		6		       //分配内存失败；
#define DH_PLAY_OPEN_FILE_ERROR			7			   //文件操作失败；
#define DH_PLAY_CREATE_OBJ_ERROR		8	           //创建线程事件等失败；
#define DH_PLAY_CREATE_DDRAW_ERROR		9		       //创建directDraw失败；
#define DH_PLAY_CREATE_OFFSCREEN_ERROR	10		       //创建后端缓存失败；
#define DH_PLAY_BUF_OVER				11	           //缓冲区满，输入流失败；
#define DH_PLAY_CREATE_SOUND_ERROR		12		       //创建音频设备失败；
#define DH_PLAY_SET_VOLUME_ERROR		13	           //设置音量失败；
#define DH_PLAY_SUPPORT_FILE_ONLY		14		       //只能在播放文件时才能使用此接口；
#define DH_PLAY_SUPPORT_STREAM_ONLY		15		       //只能在播放流时才能使用此接口；
#define DH_PLAY_SYS_NOT_SUPPORT			16		       //系统不支持，解码器只能工作在Pentium 3以上；
#define DH_PLAY_FILEHEADER_UNKNOWN		17		       //没有文件头；
#define DH_PLAY_VERSION_INCORRECT		18	           //解码器和编码器版本不对应；
#define DH_PLAY_INIT_DECODER_ERROR		19		       //初始化解码器失败；
#define DH_PLAY_CHECK_FILE_ERROR		20		       //文件太短或码流无法识别；
#define DH_PLAY_INIT_TIMER_ERROR		21		       //初始化多媒体时钟失败；
#define DH_PLAY_BLT_ERROR				22		       //位拷贝失败；
#define DH_PLAY_UPDATE_ERROR            23			   //显示overlay失败；


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

//系统支持的功能，用于按位表示系统功能
#define SUPPORT_DDRAW		1  //支持DIRECTDRAW；如果不支持，则播放器不能工作。
#define SUPPORT_BLT         2  //显卡支持BLT操作；如果不支持，则播放器不能工作
#define SUPPORT_BLTFOURCC   4  //显卡BLT支持颜色转换；
#define SUPPORT_BLTSHRINKX  8  //显卡BLT支持X轴缩小；
#define SUPPORT_BLTSHRINKY  16 //显卡BLT支持Y轴缩小；
#define SUPPORT_BLTSTRETCHX 32 //显卡BLT支持X轴放大；
#define SUPPORT_BLTSTRETCHY 64 //显卡BLT支持Y轴放大；
#define SUPPORT_SSE         128 //CPU支持SSE指令,Intel Pentium3以上支持SSE指令；
#define SUPPORT_MMX			256 //CPU支持MMX指令集。

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
	long nWidth;  //画面宽，单位像素。如果是音频数据则为0；
	long nHeight; //画面高。如果是音频数据则为0；
	long nStamp;  //时标信息，单位毫秒。
	long nType;   //数据类型，T_AUDIO16，T_RGB32， T_YV12，详见宏定义说明。
	long nFrameRate; //编码时产生的图像帧率。
}FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

//以下为对外接口，供用户作二次开发调用
//以下两个是可以不需要调用的接口
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDraw(HWND hWnd);

PLAYSDK_API BOOL CALLMETHOD PLAY_RealeseDDraw();

PLAYSDK_API BOOL CALLMETHOD PLAY_OpenFile(LONG nPort,LPSTR sFileName);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseFile(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Play(LONG nPort, HWND hWnd);
PLAYSDK_API BOOL CALLMETHOD PLAY_Stop(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Pause(LONG nPort,DWORD nPause);
PLAYSDK_API BOOL CALLMETHOD PLAY_Fast(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Slow(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOne(LONG nPort);//网络回放单帧
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayPos(LONG nPort,float fRelativePos);
PLAYSDK_API float CALLMETHOD PLAY_GetPlayPos(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVolume(LONG nPort,WORD nVolume);
PLAYSDK_API BOOL CALLMETHOD PLAY_StopSound();
PLAYSDK_API BOOL CALLMETHOD PLAY_PlaySound(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStream(LONG nPort);
PLAYSDK_API int  CALLMETHOD PLAY_GetCaps();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTime(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTime(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedFrames(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_Back(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_BackOne(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved), long nUser = 0);
PLAYSDK_API BOOL CALLMETHOD PLAY_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileTotalFrames(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameRate(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetPlayedTimeEx(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetCurrentFrameNum(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetFileHeadLength();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSdkVersion();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetLastError(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_RefreshPlay(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAYSDK_API BOOL  CALLMETHOD PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
PLAYSDK_API BOOL  CALLMETHOD PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
PLAYSDK_API BOOL  CALLMETHOD PLAY_PlaySoundShare(LONG nPort);
PLAYSDK_API BOOL  CALLMETHOD PLAY_StopSoundShare(LONG nPort);
PLAYSDK_API LONG CALLMETHOD PLAY_GetStreamOpenMode(LONG nPort);
PLAYSDK_API LONG CALLMETHOD PLAY_GetOverlayMode(LONG nPort);
PLAYSDK_API COLORREF CALLMETHOD PLAY_GetColorKey(LONG nPort);
PLAYSDK_API WORD CALLMETHOD PLAY_GetVolume(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetSourceBufferRemain(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBuffer(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBuf__stdcall)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetSourceBufFlag(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDisplayBuf(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_OneByOneBack(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileRefCallBack(LONG nPort, void (CALLBACK *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAYSDK_API BOOL CALLMETHOD PLAY_InitDDrawDevice();
PLAYSDK_API void CALLMETHOD PLAY_ReleaseDDrawDevice();
PLAYSDK_API DWORD CALLMETHOD PLAY_GetDDrawDeviceTotalNums();
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);

PLAYSDK_API BOOL CALLMETHOD PLAY_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,long *hhMonitor);
PLAYSDK_API int   CALLMETHOD PLAY_GetCapsEx(DWORD nDDrawDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_ThrowBFrameNum(LONG nPort,DWORD nNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayType(LONG nPort,LONG nType);
PLAYSDK_API long CALLMETHOD PLAY_GetDisplayType(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
PLAYSDK_API BOOL CALLMETHOD PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_CloseStreamEx(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAYSDK_API BOOL CALLMETHOD PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
PLAYSDK_API DWORD CALLMETHOD PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (CALLBACK * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetAudioCallBack(LONG nPort, void (CALLBACK * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort, long nUser),long nUser);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
PLAYSDK_API BOOL CALLMETHOD PLAY_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);

PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDRange(LONG nPort,RECT* rc,DWORD nVauleBegin,DWORD nValueEnd,DWORD nType);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetMDThreShold(LONG nPort, DWORD ThreShold) ;
PLAYSDK_API DWORD CALLMETHOD PLAY_GetMDPosition(LONG nPort, DWORD Direction, DWORD nFrame, DWORD* MDValue) ;

PLAYSDK_API BOOL CALLMETHOD PLAY_CatchPic(LONG nPort,char* sFileName) ;

PLAYSDK_API BOOL CALLMETHOD PLAY_SetFileEndCallBack(LONG nPort, void (CALLBACK *pFileEnd)(DWORD nPort,DWORD nUser),DWORD nUser);
//dataType 0 是原始码流， 1是AVI
PLAYSDK_API BOOL CALLMETHOD PLAY_StartDataRecord(LONG nPort, char *sFileName, int idataType=0);
PLAYSDK_API BOOL CALLMETHOD PLAY_StopDataRecord(LONG nPort);
PLAYSDK_API BOOL CALLMETHOD PLAY_AdjustFluency(LONG nPort, int level);
PLAYSDK_API BOOL CALLMETHOD PLAY_ChangeRate(LONG nPort, int rate);
PLAYSDK_API BOOL CALLMETHOD PLAY_SetDemuxCallBack(LONG nPort, void (CALLBACK* DecCBFun)(long nPort,char * pBuf,	long nSize,void * pParam, long nReserved,long nUser), long nUser);
#define PLAY_CMD_GetTime 1
#define PLAY_CMD_GetFileRate 2
PLAYSDK_API BOOL CALLMETHOD PLAY_QueryInfo(LONG nPort , int cmdType, char* buf, int buflen, int* returnlen);

typedef void (WINAPI *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);

PLAYSDK_API BOOL CALLMETHOD PLAY_OpenAudioRecord(pCallFunction pProc, long nBitsPerSample, long nSamplesPerSec, long nLength, long nReserved, long nUser);

PLAYSDK_API BOOL CALLMETHOD PLAY_CloseAudioRecord();

//reserved 0 表I帧帧数据水印信息 1 表帧水印 2 表水印校验 3表智能分析帧
typedef int (__stdcall* GetWaterMarkInfoCallbackFunc)(char* buf, long key, long len, long reallen, long reserved, long nUser);	//水印信息获取函数

PLAYSDK_API BOOL CALLMETHOD PLAY_SetWaterMarkCallBack(LONG nPort, GetWaterMarkInfoCallbackFunc pFunc, long nUser);

PLAYSDK_API DWORD CALLMETHOD PLAY_CreateFile(LPSTR sFileName);
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyFile(LONG nPort);
PLAYSDK_API DWORD CALLMETHOD PLAY_CreateStream(DWORD nBufPoolSize);
PLAYSDK_API BOOL CALLMETHOD PLAY_DestroyStream(LONG nPort);

#endif
