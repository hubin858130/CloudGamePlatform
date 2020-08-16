#ifndef _ASFFILEINTERFACE_H
#define _ASFFILEINTERFACE_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ASFFILEINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ASFFILEINTERFACE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef ASFFILEINTERFACE_EXPORTS
#define ASFFILEINTERFACE_API __declspec(dllexport)
#else
#define ASFFILEINTERFACE_API __declspec(dllimport)
#endif

#define  MEDIATYPE_VIDEO    1
#define  MEDIATYPE_AUDIO    2

enum asfplayevent
{
    asf_playhead,       //back to head
    asf_playover,       //play over
	asf_playok,         //play video ok
	asf_playerror       //play error

};

enum AsfPlayMode
{
	ASF_NOINIT = 0,
	ASF_NOPLAY ,          /*无视频状态*/
	ASF_PLAYING,         /*普通播放状态*/
	ASF_PAUSE,           /*暂停状态*/
	ASF_FWORD,		   /*快进*/
	ASF_BACK,			   /*快退*/
	ASF_SLOW,            /*慢放*/
	ASF_FAST,            /*快放*/

	ASF_PLAYSEEK,             /*各种播放状态下的定位播放*/
	ASF_FWORDSEEK,
	ASF_BACKSEEK,
	ASF_FASTSEEK,
	ASF_SLOWSEEK,

	ASF_SOLE,
	ASF_SOLESEEK

};


typedef struct _playctl_info
{
   	AsfPlayMode playmode;
	long speed;
	long scale;
	long seektime;
		
}playctl_info;


/*回调函数功能：通知上层文件播放事件
  asfevent: 事件类型
  hHandle:  播放句柄
  errorcode: 错误码，用于上层的错误处理函数*/
typedef void(*asfplaycallback)(asfplayevent asfevent, void* pPlayasf, int errorcode);


ASFFILEINTERFACE_API void* InitialAsf(asfplaycallback proc);
ASFFILEINTERFACE_API long StartAsf(void* asfctx,char* filename, long position, long hplaywnd, void* pPlayasf);
ASFFILEINTERFACE_API int CloseAsf(void* asfctx);
ASFFILEINTERFACE_API int PlayAsfSet(void* asfctx,playctl_info* playinfo);
ASFFILEINTERFACE_API int GetAsfState(void* asfctx);
ASFFILEINTERFACE_API long GetAsfTotalTime(void* asfctx);
ASFFILEINTERFACE_API long GetAsfCurTime(void* asfctx);
ASFFILEINTERFACE_API int  CapPic(void* asfctx,char* filepath);


#endif