

#if !defined (FHNRTVIDEO2_H_LLL)
#define FHNRTVIDEO2_H_LLL
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNRTVIDEO2_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNRTVIDEO2_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNRTVIDEO2_EXPORTS
#define FHNRTVIDEO2_API __declspec(dllexport)
#else
#define FHNRTVIDEO2_API __declspec(dllimport)
#endif

#include "fhncucommon.h"

#define rtv_success          0
#define rtv_sendmsg_error    10001
#define rtv_dest_nomedia     10002
#define rtv_dest_nosupport_media 10003
#define rtv_dest_no_mie       10004   /*返回的消息缺少IE*/


#define rtvnotify_startvideo_ok    1            /*请求实时视频成功*/
#define rtvnotify_startvideo_error 2            /*请求实时视频信令失败，V2.0有用*/
#define rtvnotify_bye              3            /*实时视频收到对端的bye*/

#define rtvnotify_askspeak_error 4              /*请求对讲失败 V2.0有用*/
#define rtvnotify_askspeak_ok    5              /*请求对讲成功*/
#define rtvnotify_speak_bye      6              /*对讲的对端bye掉连接*/

#define rtvnotify_startvideo_ms_error 7         /* 请求实时视频，对端没有回应200OK*/
#define rtvnotify_askspeak_ms_error    8        /* 请求对讲，对端没有回应200OK*/

#define rtvnotify_media_rtcp_bye       9       /*收到媒体流的rtcp bye， 对端主动bye掉*/
#define rtvnotify_media_rtcp_unreceive 10      /*没有收到对端媒体的rtcp包， 可能对端发生异常*/

#define rtvnotify_broadcast_ok      11         /*请求广播成功*/
#define rtvnotify_broadcast_list_error   12    /*请求广播组列表失败*/
#define rtvnotify_broadcast_ms_error   13      /*建立广播媒体连接失败*/  
#define rtvnotify_broadcast_bye        14      /*广播收到对端的bye*/


#define rtvnotify_speak_rtcp_bye       15
#define rtvnotify_speak_rtcp_unreceive 16


#define rtvnotify_broadcast_rtcp_bye    18
#define rtvnotify_broadcast_rtcp_unreceive 19

#define rtvnotify_broadcast_list_ok    20     /*请求广播组列表成功 */


#define rtvnotify_receive_invite       21  /*收到invite请求 reserved is a point to fhnrtv2_invite_info*/
#define rtvnotify_accept_invite        22  /*接收invite请求, callid为接收请求的id号*/

#define rtvnotify_broadcast_socket_error 23   /*媒体流接收数据错误*/
#define rtvnotify_speak_socket_error     24   
#define rtvnotify_media_socket_error     25

#define rtv_media_transtype_error  26   /*网络传输类型协商错误*/


#define rtvnotify_gotpicture   27   /*解码后的图片回调*/
#define rtvnotify_gotframe     28   /*收到媒体数据回调*/



struct fhnrtv2_picture_data
{
	int picturetype;   /*0：bgr24   1：yuv420*/
	int width;
	int height;
	void* picturedata;
	long reserved;
};


struct fhnrtv2_frame_data
{
	int framelength;   /*媒体帧数据长度*/
	void* framedata;   /*媒体数据*/
	long reserved;
};


struct fhnrtv2_invite_info
{
	fhnrtv2_destlist *pInviteList;
	int mediatype;       /*invite 请求的媒体类型*/
};

struct fhnrtv2_broadcast_list_result
{
	int errorcode;
	int listid;
	fhnrtv2_destlist* pErrorList;
};
typedef int (*rtvideocallback) (long handle, long callid, int notifycode, 
							    long errorcode,long calluserdata,long reserved);

/************************************************************************
function:fhnrtv2_initial
author: lllei 20080319
param: 	phandle: the rt handle
        version: the msg version
		family: AF_INET or AF_INET6
process: initial rtvideo dll
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_initial(long* phandle,int version, int family);

FHNRTVIDEO2_API void fhnrtv2_setcallback(long handle, rtvideocallback rtvcallback);

/************************************************************************
function:fhnrtv2_setuserinfo
author: lllei 20080319
param: 	handle: the rt handle
        userid: the user id
process: set the user id
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_setuserinfo(long handle, char* userid,char* sessionid, char* serverid);

/************************************************************************
function:fhnrtv2_askmedia
author: lllei 20080319
param: 	handle: the rt handle
        destlist: ask media pu list, only broadcast can have multi dest
		          version2 can only process one dest
		mediatype:video/audio
process: ask dest media 
return: 0:error; else:the ask media callid
************************************************************************/
FHNRTVIDEO2_API long fhnrtv2_askmedia(long handle,fhnrtv2_destlist destlist,
									  enummediatype mt,char* destip, UINT destport,long calluserdata);

FHNRTVIDEO2_API long fhnrtv2_askmediaex(long handle,fhnrtv2_destlist destlist,enummediatype mt,
					  enumtranstype tt,char* destip, UINT destport, long calluserdata);
FHNRTVIDEO2_API long fhnrtv2_askmedia_broadcast(long handle,fhnrtv2_destlist destlist,enummediatype mt,
					  enumtranstype tt,char* destip, UINT destport, long calluserdata, int format);
FHNRTVIDEO2_API long fhnrtv2_setoverlaymode(long handle, long callhandle, BOOL boverlay, COLORREF clrkey);
/************************************************************************
function:fhnrtv2_setplaywnd
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		hwnd:video play wnd
process: set video play wnd
return: NULL
************************************************************************/
FHNRTVIDEO2_API void fhnrtv2_setplaywnd(long handle, long callid, long hwnd, int videoindex); 
/************************************************************************
function:fhnrtv2_cappicture
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		filepath:picture save path
process: capture picture
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_cappicture(long handle, long callid, char* filepath);

/************************************************************************
function:fhnrtv2_startrecord
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
		filepath:record save path
process: start record 
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_startrecord(long handle, long callid, char* filepath, int rec_type);

/************************************************************************
function:fhnrtv2_stoprecord
author: lllei 20080319
param: 	handle: the rt handle
        callid: askmedia return value
process: stop record 
return: NULL
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_stoprecord(long handle, long callid);

/************************************************************************
function:fhnrtv2_getframerate
author: lllei 20080319
param: 	handle: the rt handle
process: get the rtvideo framerate
return: framerate
************************************************************************/
FHNRTVIDEO2_API int  fhnrtv2_getframerate(long handle,long callid);

/************************************************************************
function:fhnrtv2_getflux
author: lllei 20080319
param: 	handle: the rt handle
process: get the rtvideo flux
return: flux
************************************************************************/
FHNRTVIDEO2_API float  fhnrtv2_getflux(long handle,long callid);

FHNRTVIDEO2_API void fhnrtv2_GetPacketCount(long  handle, long callid,int* RecPacket, int* LosePacket);

FHNRTVIDEO2_API BOOL fhnrtv2_RefreshPlaywnd(long handle, long callid);
/************************************************************************
function:fhnrtv2_stopmedia
author: lllei 20080319
param: 	phandle: the rt handle
        callid: askmedia return value
process: stop media
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_stopmedia(long handle,long callid);

FHNRTVIDEO2_API BOOL fhnrtv2_GetCallNetWorkInfo(long handle,long callid,fhn_Call_NetWork_Info *pCallInfo);

FHNRTVIDEO2_API BOOL fhnrtv2_GetCallMediaInfo(long handle,long callid,fhn_MediaInfo_rtp *pCallInfo);
/************************************************************************
function:fhnrtv2_destory
author: lllei 20080319
param: 	handle: the rt handle
process: destory rtvideo dll
return: 0:success; else:error
************************************************************************/
FHNRTVIDEO2_API int fhnrtv2_destory(long handle);



FHNRTVIDEO2_API void fhnrtv2_EnablePictureCallback(long handle, BOOL benable);

FHNRTVIDEO2_API void fhnrtv2_EnableGrameCallback(long handle, BOOL benable);

#endif