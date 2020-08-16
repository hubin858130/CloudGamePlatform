
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RECPLAYINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RECPLAYINTERFACE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef _RECPLAYINTERFACE_H
#define _RECPLAYINTERFACE_H

typedef struct S_RecPlayInfo
{
	int ret;
	cm_reply_type_t rtpye;
	unsigned  fileTime;

}S_RecPlayInfo;




#ifdef RECPLAYINTERFACE_EXPORTS
#define RECPLAYINTERFACE_API __declspec(dllexport)
#else
#define RECPLAYINTERFACE_API __declspec(dllimport)
#endif

typedef int (*RecPlayCallBack)(long rechandle, long hHandle,long userdata,S_RecPlayInfo * recPlay);
//moidified by lm 20080509
//support multiple thread rec-file play
//add the playcontenner handle to each interface

/************************************************************************
function:InitialRecPlay
author: lm 20080509
param: 	RecPlayCBack :the address of the call back function 
process: init the rec play dll
return: -1:error; else:rec play contenner handle
************************************************************************/
RECPLAYINTERFACE_API long InitialRecPlay(RecPlayCallBack RecPlayCBack);

/************************************************************************
function:UninitialRecPlay
author: lm 20080509
param: 	rechandle: the handle of the rec play contenner 
process: uninit the rec play dll
return: 0:success; else :error
************************************************************************/
RECPLAYINTERFACE_API int  UninitialRecPlay(long rechandle);

/************************************************************************
function:OpenRecFile
author: lm 20080509
param: 	rechandle: the handle of the rec play contenner
		filename :local file name 
		position :open file position (seconds)
		hplaywnd: the play window handle  
process: open the local file
return: -1:error ;else :the file play handle
************************************************************************/
//RECPLAYINTERFACE_API long OpenRecFile(long rechandle, char* filename, long position, long hplaywnd, long userdata,int videoindex,DeviceDecInfo * deviceinfo);

/************************************************************************
function:CloseRecFile
author: lm 20080509
param: 	rechandle: the handle of the rec play contenner
		hHandle:file play handle
process: close the play of the local file
return: 0:success; else :error
************************************************************************/
//RECPLAYINTERFACE_API int  CloseRecFile(long rechandle, long hHandle);

/************************************************************************
function:OpenRecUrl
author: lm 20080509
param: 	rechandle: the handle of the rec play contenner
		url: remote file url;
		userid: cu user id
		position: start position(seconds)
		hplaywnd:the play window handle
process: open the remote file
return: -1:error; else :the url play handle

no use now
************************************************************************/
RECPLAYINTERFACE_API long RecPlay_OpenRecUrl(long rechandle, char* url, char * userid, long position, 
											 long hplaywnd,long userdata,int videoindex,DeviceDecInfo * deviceinfo);


/************************************************************************
function:CloseRecUrl
author: lm 20080509
param: 	hHandle:the url play handle
process: close the url play
return: 0:success; else :error
************************************************************************/
RECPLAYINTERFACE_API int  RecPlay_CloseRecUrl(long rechandle, long hHandle);

RECPLAYINTERFACE_API int RecPlay_Operate(long rechandle, long hHandle, ePlayOption operate, int reserve);

RECPLAYINTERFACE_API  int  RecPlay_GrabPic (long rechandle, long hHandle, char* filename, long picType);

RECPLAYINTERFACE_API int RecPlay_GetFrameRate(long rechandle, long hHandle);

RECPLAYINTERFACE_API float RecPlay_GetFlux(long rechandle, long hHandle);

RECPLAYINTERFACE_API BOOL RecPlay_StartRecord(long rechandle, long hHandle, char* FileName);

RECPLAYINTERFACE_API BOOL RecPlay_StopRecord(long rechandle, long hHandle);

RECPLAYINTERFACE_API int  RecPlay_GetPlayPosition (long rechandle, long hHandle, long *pPosition);
RECPLAYINTERFACE_API unsigned int RecPlay_GetRecFileCurTs(long rechandle, long hHandle);


//add by lm 20081111
/************************************************************************
function:OpenRecUrlEx
author: lm 20081111
param: 	rechandle: the handle of the rec play contenner
		url: remote file url;
		userid: cu user id
		position: start position(seconds)
		hplaywnd:the play window handle
		transType : 0:udp  1:tcp
process: open the remote file
return: -1:error; else :the url play handle
************************************************************************/

/*reserved: 用来区分回放服务器的版本信息
1:老版本的NRU,回放的数据流携带了长度校验字段
0:新版本NRU,回放的数据流众不带长度校验字段*/
RECPLAYINTERFACE_API long RecPlay_OpenRecUrlEx(long rechandle, char* url, char * userid, long position, 
											   long hplaywnd, long userdata,int videoindex, int transType,int dlSpeed,int reserved);
RECPLAYINTERFACE_API long RecPlay_InitUDP(long rechandle,char * tmpip , int tmpport,int *localPort);
RECPLAYINTERFACE_API int RecPlay_StartUDP(long rechandle,long hHandle,char* url, char * userid, long position, long hplaywnd, long userdata,int videoindex, int transType,int dlSpeed,int reserved);
RECPLAYINTERFACE_API int RecPlay_StopUDP(long rechandle,long hHandle);
RECPLAYINTERFACE_API BOOL RecPlay_RefreshSurface(long rechandle,long hHandle);

#endif
