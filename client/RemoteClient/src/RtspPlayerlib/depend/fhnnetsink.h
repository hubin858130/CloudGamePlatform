
#ifdef FHNNETSINK_EXPORTS
#define FHNNETSINK_API __declspec(dllexport)
#else
#define FHNNETSINK_API __declspec(dllimport)
#endif

#if !defined (_FHNNETSINK_H)
#define _FHNNETSINK_H

typedef void (*fhnns_recvpacketcallback)(long handle,long packetdata);

typedef int (*fhnns_gotpicturecallback)(long sinkid, char* picbuf, int width, int height, int pictype, long NetSinkUserdata);

typedef int(*fhnns_GotFramedataCallback)(long sinkid, char* mediabuf, long length, long userdata);

#define fhnns_notify_rtcp_unreceive     1  /*没收到rtcp 包*/
#define fhnns_notify_rtcp_bye           2  /*收到rtcp bye*/
#define fhnns_notify_socket_error       3  /*socket错误*/
#define fhnns_notify_media_lostpacket   4  /*媒体丢包*/


typedef void (*fhnns_SinkReportCallBack)(long handle, long sinkid, int NotifyCode,long userdata);

#define FHNNS_RTV 1      /*实时模式*/
#define FHNNS_URL 2      /*回放模式*/

enum enum_SinkDirection
{
	FHNNS_RCV_ONLY   = 1,   /*只接收 sink*/
	FHNNS_SEND_ONLY  = 2,   /*只发送 sink*/
	FHNNS_SEND_RCV   =3   /*收发   sink*/
};


FHNNETSINK_API int fhnns_preparenetsink(long *phandle);

FHNNETSINK_API int fhnns_PrepareNetSinkEx(long *phandle, long userdata);

FHNNETSINK_API void fhnns_SetReportCallBack(long handle,fhnns_SinkReportCallBack SinkReportCallBack);

FHNNETSINK_API int fhnns_SetGotPictureCallBack(fhnns_gotpicturecallback GotPictureCallBack);
FHNNETSINK_API int fhnns_SetGotFrameCallback(fhnns_GotFramedataCallback GotFrameCallback);

FHNNETSINK_API long fhnns_createsink(long handle,char* remoteip, UINT port, 
								enumtranstype transtype,enumpackettype packettype);

FHNNETSINK_API long fhnns_createsink2(long handle,enumtranstype transtype,enumpackettype packettype,
									  enum_SinkDirection Direction);

FHNNETSINK_API long fhnns_createsink_db33(long handle, long rtpport);
FHNNETSINK_API long fhnns_setserverip(long handle, char * serverip);	//added by lxf

FHNNETSINK_API long fhnns_SetOverLayMode(long handle, long sinkid, BOOL boverlay, COLORREF clrkey);	//added by lxf
FHNNETSINK_API void fhnns_setsinkmode(long handle, long sinkid, int sinkmode);
/*added by lllei 20080718 set sink to url mode and rtp ssrc*/
FHNNETSINK_API void fhnns_SetSinkURLMode(long handle, long sinkid, UINT ssrc);
/*end add lllei*/
FHNNETSINK_API void fhnns_resetsink(long handle,long sinkid,char*remoteip, UINT port);
FHNNETSINK_API void fhnns_resetsink2(long handle,long sinkid,char*remoteip, UINT DestSendPort, UINT DestRcvPort);

FHNNETSINK_API void fhnns_pausesink(long handle,long sinkid);

FHNNETSINK_API void fhnns_startsink(long handle,long sinkid);

FHNNETSINK_API void fhnns_setsinkplaywnd(long handle,long sinkid,long hwnd, int videoindex);

FHNNETSINK_API void fhnns_SetDeviceInfo(long handle,long sinkid,DeviceDecInfo devinfo);

FHNNETSINK_API UINT fhnns_getlocalport(long handle,long sinkid);

FHNNETSINK_API UINT fhnns_GetLocalSendPort(long handle,long sinkid);

FHNNETSINK_API UINT fhnns_closesink(long handle,long sinkid);

FHNNETSINK_API float fhnns_getflux(long handle,long sinkid);

FHNNETSINK_API  unsigned int  fhnns_getcurts(long handle,long sinkid);

FHNNETSINK_API  int fhnns_getframerate(long handle,long sinkid);
FHNNETSINK_API void fhnns_GetPacketCount(long  handle, long sinkid,int* RecPacket, int* LosePacket);

FHNNETSINK_API  int fhnns_cappicture(long handle,long sinkid, char *filepath);

FHNNETSINK_API BOOL fhnns_getfirstts(long handle,long sinkid, UINT/*out*/ *pts);

FHNNETSINK_API BOOL fhnns_getssrc(long handle,long sinkid, UINT/*out*/ *pssrc);

FHNNETSINK_API int fhnns_startsendaudio(long handle,long sinkid);

/* start send audio with audio format*/
FHNNETSINK_API int fhnns_StartSendAudioEx(long handle, long sinkid, int AudioFormat);

FHNNETSINK_API int fhnns_stopsendaudio(long handle,long sinkid);

FHNNETSINK_API int fhnns_startrecord(long handle,long sinkid, char* filepath, int rec_type);

FHNNETSINK_API int fhnns_stoprecord(long handle,long sinkid);

FHNNETSINK_API int fhnns_unpreparenetsink(long handle);

FHNNETSINK_API void fhnns_setuserid( long handle,char* userid);
FHNNETSINK_API BOOL fhnns_GetMediaInfo(long handle, long sinkid,fhn_MediaInfo_rtp* pMediaInfo);

FHNNETSINK_API void fhnns_EnableFrameControl(long handle, long sinkid, BOOL enable);


FHNNETSINK_API BOOL fhnns_RefreshPlaywnd(long handle, long sinkid);

FHNNETSINK_API void fhnns_EnableCheckRtcp(long handle, long sinkid, BOOL bcheck);


#endif

