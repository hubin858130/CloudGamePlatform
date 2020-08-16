//megaplay.h
#ifndef __MEGAPLAY_H__
#define __MEGAPLAY_H__

#define ERROR_FILENOTFOUND   1L
#define ERROR_FILESIZE       2L
#define ERROR_FILEFORMAT     3L
#define ERROR_FILEVERSION    4L
#define ERROR_STARTPLAY      5L
#define ERROR_PLAYNOTINIT    6L
#define ERROR_NOTREALIZE     7L
#define ERROR_CHANNELERROR   8L
#define ERROR_OTHER          9L
#define ERROR_INVALIDPARAM   10L

#define MAX_DISPLAY_RECT_NUM 4      //最多显示窗口
#define MAX_DELAYFRAMENUM    500    //最大的延迟帧数
#define MAX_BUFFFRAMENUM     500    //最大的缓冲帧数
#define MIN_BUFFFRAMENUM     10     //最小的缓冲帧数

enum
{
	PARAM_DELAYTIME     = 0,        //设置获取延迟帧数
	PARAM_BUFFNUM       = 1,        //设置获取缓存帧数
	PARAM_CUR_BUFFNUM   = 2,        //获取当前缓存帧数
};

typedef struct
{
    unsigned int    timetick;       //时间戳 (ms)
    unsigned int    nChannels;      //通道数量
    unsigned int    nSamplesPerSec; //采样率
    unsigned int    wBitsPerSample; //采样位数
    const char      *pbuff;         //音频数据buff
    int             size;           //音频数据长度
}AUDIO_FRAMEINFO;

typedef struct
{
    unsigned int    timetick;       //时间戳 (ms)
    const char      *pY;            //YV12格式,Y buff
    const char      *pU;            //U buff
    const char      *pV;            //V buff
    int             stridey;        //Y 跨度
    int             strideuv;       //UV 跨度
    int             width;          //图像宽度
    int             height;         //图像高度
}VIDEO_FRAMEINFO;

#define FRAMETYPE_VIDEO     1
#define FRAMETYPE_AUDIO     2

#define CPLAY_APIIMPORT  extern "C"__declspec(dllexport)
typedef long (__stdcall *MessageCallBack)(long lType,long lPara1,long lPara2);

CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Initial(long hWnd);
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_Free();
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_OpenFile(long hHandle,LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CloseFile(long hHandle);
CPLAY_APIIMPORT	HRESULT __stdcall LCPLAYM4_OpenStream(long hHandle,long *pFileHeadBuf,long lSize);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CloseStream(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_InputData(long hHandle, long *pBuf, long lSize);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_PlaySound(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopSound(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetVolume(long hHandle,long lVolume);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Play(long hHandle,long hWnd);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Stop(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Pause(long hHandle,long lPause);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_RefreshSurface(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetPlayPos(long hHandle,long lPos);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Fast(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_Slow(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_CapPic(long hHandle,LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetPlayPos(long hHandle,long *pPos);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetVersion(long *lVer);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_QueryFunction(LPCTSTR sFunctionName,long *lCanUse);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetParameter(long hHandle,long lType,long lPara1,long lPara2);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetParameter(long hHandle,long lType,long *pPara1,long *pPara2);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetCallBack(long hHandle,long (__stdcall *CallBack)(long lType,long lPara1,long lPara2));
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetFileEndMsgWnd(long hHandle,long hWnd,long lMsg);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StartASFFileCap(long hHandle,LPCTSTR sFileName,BOOL index = FALSE);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopCapture(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StartMp4Capture(long hHandle, LPCTSTR sFileName);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_StopMp4Capture(long hHandle);
CPLAY_APIIMPORT DWORD   __stdcall LCPLAYM4_GetFileTime(long hHandle);
CPLAY_APIIMPORT DWORD   __stdcall LCPLAYM4_GetPlayedTime(long hHandle);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetPlayedTime(long hHandle,DWORD nTime);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetDecodeCallBack(long hHandle,long( CALLBACK *DecodeCallBack)(long hHandle,long frametype,long *frameinfo,long lParam ),long lParam);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_SetDisplayRect(long hHandle,int num,RECT *rect,HWND hWnd,BOOL bEnable);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_GetVideoSize(long hHandle,DWORD *Width,DWORD *Height);
CPLAY_APIIMPORT HRESULT __stdcall LCPLAYM4_OneByOne(long hHandle);
#endif
