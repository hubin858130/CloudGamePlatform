
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNNETMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNNETMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNNETMSG_EXPORTS
#define FHNNETMSG_API __declspec(dllexport)
#else
#define FHNNETMSG_API __declspec(dllimport)
#endif

#if !defined FHNNETMSG_H
#define FHNNETMSG_H

#include "nanohttp-common.h"
#include "nanohttp-clientserver.h"
#define enumnetmsgmodule unsigned int

#define  MODULE_BASIC          1   /*基础消息处理模块*/
#define  MODULE_ALM            2   /*报警处理模块*/
#define  MODULE_MONITER        3   /*实时监控处理模块*/
#define  MODULE_PTZ            4   /*云台控制模块*/
#define  MODULE_RECORD         5   /*录像查询 回放模块*/
#define  MODULE_MEETING        6   /*视频会议模块*/
#define  MODULE_PARAMSET       7   /*参数设置*/
#define  MODULE_IPMATRIX	   8   /*矩阵控制模块*/
#define  MODULE_SBSATX         9   /*BS模块*/

enum enummsgformat
{
	FM_SIP,    /*mio发送的sip消息*/
	FM_HTTP,  /*http格式的消息*/
	FM_MEDIA, /*sip协商*/
};

/*http请求*/
enum enumhttpmsgtype
{
	NETMSG_HTTPCD_NC_RECV_REQ = 100,
	NETMSG_HTTPCD_NC_RECV_RESP,
	NETMSG_HTTPCD_NC_SND_REQ_FAIL,
	NETMSG_HTTPCD_NC_SND_RESP_FAIL,
	NETMSG_HTTPCD_NC_SND_AUTO_RESP,
	NETMSG_HTTPCD_NC_UNKNOWN,
};

enum enummediamsgtype
{
	MS_INVITE,    /*发送媒体协商*/
	MS_BYE,       /*断开媒体*/
	MS_ACK,       /*发送应答*/
};
typedef int (*moduleprocesscallback)(int notifycode, long msg, int msgid,long userdata);

/************************************************************************
function:fhnnetmsg_initial
author: lllei 20080304
param:  phandle: a point to a handle
		family: AF_INET or AF_INET6
process: initial the dll,create msg module
return: 0:success; else :error
        the phandle is a return
************************************************************************/
FHNNETMSG_API int  fhnnetmsg_initial(long * phandle, int family);

/************************************************************************
function:fhnnetmsg_destory
author: lllei 20080304
param:  the handle to destory
process: destory the msg module
return: void
************************************************************************/
FHNNETMSG_API  void   fhnnetmsg_destory(long handle);

/************************************************************************
function:fhnnetmsg_regmodule
author: lllei 20080304
param:  handle: initial function return value
        moduletype : the module
		moduleprocesscallback: receive function return
process: register a module to the dll
return: void
************************************************************************/
FHNNETMSG_API void fhnnetmsg_regmodule (long handle,enumnetmsgmodule moduletype,
									  moduleprocesscallback callbackproc);

/************************************************************************
function:fhnnetmsg_regreqmsg
author: lllei 20080304
param:  handle: initial function return value
        moduletype : the module
        msgtype: the module want req msg type
process: register a req msg receive
return: void
************************************************************************/
FHNNETMSG_API   void  fhnnetmsg_regreqmsg (long handle,enumnetmsgmodule moduletype,
										  int msgtype,long modulehandle);
/************************************************************************
function:fhhnnetmsg_sendreqmsg
author: lllei 20080304
param:  handle: initial function return value
        msg: the msg want to send,
		     if format == FM_MEDIA, the msg is ms_indicate_info_t struct
        userdata: msg userdata
process: send a req msg
return: msgid
************************************************************************/
FHNNETMSG_API int  fhhnnetmsg_sendreqmsg (long handle,void *msg,
										  void *userdata,char* toip, 
										  UINT port, enummsgformat format);

/************************************************************************
function:fhhnnetmsg_sendrespmsg
author: lllei 20080304
param:  handle: initial function return value
        msg: the msg want to send
        msgid: the req msgid
process: send a resp msg
return: void
************************************************************************/
FHNNETMSG_API int  fhhnnetmsg_sendrespmsg (long handle,void *msg, int msgid);

FHNNETMSG_API int fhnnetmsg_sendregister(long  handle, char* to, int toport,
										  char* username, char*passward,
										  int expires, void* reguserdata);

FHNNETMSG_API BOOL fhnnetmsg_cancelreg(long handle, int regid); 

FHNNETMSG_API miosMSG* fhnnetmsg_mallocmsghead(long handle);

FHNNETMSG_API void* fhnnetmsg_mallocie(long handle, int size);

FHNNETMSG_API void fhnnetmsg_malloclistnode(long handle);

FHNNETMSG_API void fhnnetmsg_add_ie_to_msg( long handle,miosMSG* msg, void* ie);

/*
 * 用来将miosMSG结构的消息转换成消息文本。
 *
 * 参数定义：
 *  handle: 接口模块句柄
 *  msg: 需要转换成文本的消息
 *  buf: 输出的缓存。如果为NULL，表明只是计算需要的输出长度。
 *  len: 输出的缓存长度。
 *  
 *
 * 返回值：
 *  返回转换成文本之后的长度。如果buf不为MIO_NULL，并且len小于实际需要的长度，返回值为所需要的长度的相反数。
 *
 */

FHNNETMSG_API int fhnnetmsg_encodeMSG( long handle, miosMSG *msg, char* buf, int len);

FHNNETMSG_API int fhhnnetmsg_sendhttpgetpic(long handle, hpair_t * querylist, void *userdata, char* toip, UINT port);
FHNNETMSG_API int fhnnetmsg_ConvertUTF8ToGb2312(long handle, char* utf8str, char* gb2312str, int gb2312len);

FHNNETMSG_API int fhnnetmsg_ConvertGb2312ToUTF8(long handle, char* gb2312str, char* utf8str, int utf8len);

FHNNETMSG_API int fhnnetmsg_SetSipKeepAliveInterval(long handle, int time);


FHNNETMSG_API miosMSG* fhnnetmsg_decodeMSG(long handle , char* buf, int len);

FHNNETMSG_API void fhnnetmsg_freeMsg(long handle, miosMSG* msg);
FHNNETMSG_API BOOL fhnnetmsg_GetLocalIp(long handle, char* localip, int len, char* dstip);
FHNNETMSG_API int fhnnetmsg_GetAddrFamily(char * ip);
#endif