
#if !defined(_FHNMEDIASTREAM_H)
#define _FHNMEDIASTREAM_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNMEDIASTREAM_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNMEDIASTREAM_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNMEDIASTREAM_EXPORTS
#define FHNMEDIASTREAM_API __declspec(dllexport)
#else
#define FHNMEDIASTREAM_API __declspec(dllimport)
#endif

typedef enum
{
	RTCP_SR  = 200,
	RTCP_RR  = 201,
	RTCP_SDES = 202,
	RTCP_BYE  = 203,
	RTCP_APP  = 204
} rtcp_type_t;

struct mediaframe
{
	unsigned char pt;         /*packettype*/
	unsigned int ts;          /*timestamp*/
	unsigned int extend;      /*the extend data*/
	unsigned int length;      /*framelength*/
	unsigned char * databuf;  /*frame data*/
};

#define fhnms_notify_sendata     0
#define fhnms_notify_lostpacket  1


typedef int (*fhnms_senddatacallback)(long mshandle,char* packet, int length,
									long userdta, long reserved);

typedef int (*fhnms_gotpicturecallback)(long mshandle, char* picbuf, int width, int height, int pictype, long userdata);

typedef int (*fhnms_gotframeCallback)(long mshandle, char* framebuf, int length, long userdata);

#define FHN_RECTYPE_ASF 1
#define FHN_RECTYPE_RAW 2
#define HIK_RECTYPE     3
/************************************************************************
function:fhnms_init
author: lllei 20080422
param:
process: init mediastream
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_init();
FHNMEDIASTREAM_API int fhnms_destory();

/************************************************************************
function:fhnms_setsenddatacallback
author: lllei 20080422
param: sendprocess senddatacallback
process: set senddata callback
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_setsenddatacallback(fhnms_senddatacallback sendprocess);

FHNMEDIASTREAM_API int fhnms_setGotFrameCallback(fhnms_gotframeCallback gotframeProcess);
/************************************************************************
function:fhnms_setgotpicturecallback
author: lllei 20080422
param: got picture callback
process: set gotpicture callback
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_setgotpicturecallback(fhnms_gotpicturecallback pictureprocess);

/************************************************************************
function:fhnms_createstream
author: lllei 20080306
param: 	pt: the packet type, ts or rtp
        phandle: when function return, the value is the handle of stream
process: create a mediastream
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_createstream(enumpackettype pt, long*phandle, long userdata);

/************************************************************************
function:fhnms_setplayhwnd
author: lllei 20080422
param: 	handle: createstream return handle
        hwnd: the media play wnd
process: create a mediastream
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_setplayhwnd(long handle ,long hwnd, int videoindex);

FHNMEDIASTREAM_API int fhnms_SetOverLayMode(long handle, BOOL boverlay, COLORREF clrkey);
/************************************************************************
function:fhnns_setbuffer
author: lllei 20080306
param: 	phandle: the stream handle
        buftime: buffer time in millisecond
process: set the buf time to wait when lose packet
        the initial time is 1s
return: 
************************************************************************/
FHNMEDIASTREAM_API void fhnms_setbuffer(long handle,UINT buftime);

/************************************************************************
function:fhnms_clearbuffer
author: lllei 20080306
param: 	phandle: the stream handle
process: clear the data in buffer
return:  NULL
************************************************************************/
FHNMEDIASTREAM_API void fhnms_clearbuffer(long handle);

/************************************************************************
function:fhnms_closestream
author: lllei 20080306
param: handle: the stream handle
process: close a mediastream
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_closestream(long handle);

/************************************************************************
function:fhnms_setntpsync
author: lllei 20080306
param: handle: the stream handle
       ts: the ntp time coressponding timestamp
	   ntp: the time
process: set the ntp and ts relationship
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_setntpsync(long handle,long ts, long ntp);

/************************************************************************
function:fhnms_inputdata
author: lllei 20080312
param: handle: the stream handle
       ts: the ntp time coressponding timestamp
	   ntp: the time
process: set the ntp and ts relationship
return: 0:success; else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_inputdata(long handle,void* pdata,int length);

/************************************************************************
function:fhnms_calcframerate
author: lllei 20080430
param: handle: the stream handle
process: get framerate
return: framerate
************************************************************************/
FHNMEDIASTREAM_API int fhnms_calcframerate(long handle);
/************************************************************************
function:fhnms_getframerate
author: lllei 20080430
param: handle: the stream handle
process: get framerate
return: framerate
************************************************************************/
FHNMEDIASTREAM_API int fhnms_getframerate(long handle);
FHNMEDIASTREAM_API void fhnms_GetPacketCount(long handle,int* RecPacket, int* LosePacket);
/************************************************************************
function:fhnms_getcurts
author: lllei 20080430
param: handle: the stream handle
process: get curplayingts
return: framerate
************************************************************************/
FHNMEDIASTREAM_API int fhnms_getcurts(long handle);

/************************************************************************
function:fhnms_cappicture
author: lllei 20080430
param: handle: the stream handle
       filepath: cap picture filepath
process: cap picture
return: 0:success else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_cappicture(long handle, char* filepath);

/************************************************************************
function:fhnms_getfirstts
author: lllei 20080430
param: handle: the stream handle
	   pts: a point to uint 
process: get the first ts
return: TRUE:first ts store in pts
        FALSE: no packet receive
************************************************************************/
FHNMEDIASTREAM_API BOOL fhnms_getfirstts(long handle, UINT/*out*/ *pts);

/************************************************************************
function:fhnms_getssrc
author: lllei 20080430
param: handle: the stream handle
	   pts: a point to uint 
process: get the first ts
return: TRUE:ssrc store in pts
        FALSE: no packet receive
************************************************************************/
FHNMEDIASTREAM_API BOOL fhnms_getssrc(long handle, UINT/*out*/ *pssrc);

/************************************************************************
function:fhnms_getrtcpreport
author: lllei 20080430
param: handle: the stream handle
	   pts: a point to uint 
process: get the first ts
return: 0: no packet receiveT
		>0:rtcp length
        
************************************************************************/
FHNMEDIASTREAM_API int fhnms_getrtcpreport(long handle, char/*out*/ *prreport,rtcp_type_t type);
FHNMEDIASTREAM_API int fhnms_GetRtcpSendReport(long handle, char/*out*/ *prreport);
/************************************************************************
function:fhnms_startsendaudio
author: lllei 20080513
param: handle: the stream handle
process: start send audio data
return: 0:success
        else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_startsendaudio(long handle);

FHNMEDIASTREAM_API int fhnms_StartSendAudioEx(long handle, int AudioFormat);
/************************************************************************
function:fhnms_stopsendaudio
author: lllei 20080513
param: handle: the stream handle
process: stop send audio
return: 0:success
        else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_stopsendaudio(long handle);

/************************************************************************
function:fhnms_startrecord
author: lllei 20080513
param: handle: the stream handle
process: start record data
return: 0:success
        else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_startrecord(long handle, char* filepath, int rec_type);

/************************************************************************
function:fhnms_stoprecord
author: lllei 20080513
param: handle: the stream handle
process: stop record data
return: 0:success
        else:error
************************************************************************/
FHNMEDIASTREAM_API int fhnms_stoprecord(long handle);

FHNMEDIASTREAM_API int fhnms_SetMediaDeviceInfo(long handle, DeviceDecInfo deviceinfo);

FHNMEDIASTREAM_API BOOL fhnms_GetMediaInfo(long handle, fhn_MediaInfo_rtp* pMediaInfo);

FHNMEDIASTREAM_API void fhnms_EnableFrameControl(long  handle, BOOL enable);

FHNMEDIASTREAM_API void fhnms_SetTimeScale(long handle, UINT TimeScale);


FHNMEDIASTREAM_API BOOL fhnms_RefreshPlaywnd(long handle);

FHNMEDIASTREAM_API void fhnms_EnableLosePakcetReport(long handle, BOOL benable);

#endif