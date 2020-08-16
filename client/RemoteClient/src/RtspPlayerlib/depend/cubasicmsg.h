
#if !defined (CUBASICMSG_H_LLL)
#define CUBASICMSG_H_LLL
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CUBASICMSG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CUBASICMSG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CUBASICMSG_EXPORTS
#define CUBASICMSG_API __declspec(dllexport)
#else
#define CUBASICMSG_API __declspec(dllimport)
#endif


//#define cubm_error_sendmsg    10001
//#define cubm_error_ielack     10002
//#define cubm_error_picsize_too_lager    10006	/*图片太大*/
//#define cubm_error_findnotsrv	404	/*找不到服务器*/
//#define cubm_error_findnotfile	204 /*找不到图片文件*/

//#define cubm_error_register_timeout  10003   /*注册消息发送超时*/
//#define cubm_error_register_resp     10004   /*注册消息返回失败*/
//#define cubm_error_nullmsg           10005   /*空消息*/

#define cubm_pulistv3_ack      1   

#define cubm_puinfo_ack        3

#define cubm_login_ack         5
#define cubm_register_ack      6   /*added by lllei 20080807 注册响应*/

#define cubm_offline           7    

#define cubm_pulistv2_ack      9
#define cubm_ptzset_ack        10    


#define cubm_receive_alm 		 11
#define cubm_receive_threshold   12

#define cubm_receive_time_verify_resp 13
#define cubm_receive_pu_notify_req    14
#define cubm_receive_alarm_query_resp 15

#define cubm_ipmatric_query_resp  16  /*矩阵查询响应*/

#define cubm_getchannelposition	 17	 /*监控点位置更改响应*/

#define cubm_VersionInfo_resp 18	/*版本信息响应*/

#define cubm_callstatus_notify  19   /*呼叫状态通知*/
#define cubm_pswchange_resp     20   /*修改用户密码响应*/

#define cubm_http_get_pic_resp	21	/*获取图片请求*/

#define cubm_querypic_resp 22 /*前端图片查询响应*/
#define cubm_delpic_resp 23 /*前端图片删除响应*/

#define cubm_regekey_resp 23 /*key验证回应*/

#define STREAM_DISCONNECT_ALARM 1  /*视频流断开*/
#define STREAM_INTERRUPT_ALARM 2   /*视频流断续*/





#define CUMSG_VERSION_2    1
#define CUMSG_VERSION_3    2

#define CUBM_IPADDR_LEN		40	//for support ipv6

struct user
{
	char  name[128];
	char  psw[128];
	char  id[64];
	char  sessionid[64];
	BOOL  isadmin;
};

struct ikeyinfo
{
	long errorcode;
	char chancode[64];
};

struct cubm_alminfo
{
	char puid[64];
	int  channelno;
	int  almtype;
	char almtime[64];  /*yyyy-mm-dd  hh:mm:ss*/
	char almdesp[128];
	char almid[33];
	char channelname[33];
	int almchanneltype;  /*报警通道类型*/
	char almlevel[33]; //报警级别
};

struct alarmLogQuery
{
	unsigned int logType;
	char logTime[128];
	char logEvent;
	char logObjectID[19];
	short logChannel;
	unsigned int logInfo;
	char logDesp[256];
	struct alarmLogQuery *next;
	char almlevel[33]; //报警级别
};

struct cubm_alarmLogQueryInfo
{
	struct alarmLogQuery *LogQuerylist;
	int	logCount;
};

typedef struct group group;
typedef struct pu    pu;
typedef struct channel channel;

struct moniter  /*no use */
{
	moniter* pnext; 
	pu*	parent;
	int videoid;
	channel* VideoChannel;
	channel* channellist;
};

struct channel
{
	int nodetype;         /*节点类型*/
	channel *pnext;
	pu* parent;
	int id;               /*通道号*/
	int type;             /*通道类型*/
	int coresvideoid;     /*对应的视频ID号 no use*/
	char name[128];       /*通道名称*/
	double x;             /*X坐标*/
	double y;             /*Y坐标*/
	__int32 UserRight;    /*权限*/
	BOOL   HasAudioIn;      /*是否有音频输入*/
	char outDevType[128]; /*外接设备类型*/
	
	/*	通道状态: 按bit位来表示, 第0位: 平台手动录像; 
	第1位: 前端手动录像; 0: 表示没有录像,1: 表示正在录像  add by lxf */
	unsigned int channelstate;

	unsigned __int16 orderstate;  /*通道的在用状态*/
	void*  channeldata;
};

struct httppicinfo
{
	char filename[1024];		/*图片文件名*/
	char body[2*1024*1024];		/*图片数据*/
	long	bodylen;
	char path[1024];
};

struct pu
{
	int    nodetype;
	pu*    pnext;
	group* parent;
	char   id[32];
	char   name[128];
	int    channelnum;            /*no use*/
	BOOL   online;
	channel* channellist;         /*视频通道列表*/
	moniter* moniterlist;         /*no use */
	double x;
	double y;
	BOOL   HasAudioOut;            /*是否有音频输出*/
	int    AlmInNum;               /*报警输入通道数*/
	int    AlmOutNum;              /*报警输出通道数*/
	__int32 PlatformManufactureID; /*厂家ID号*/
	__int16 m_ManufactureID;       /*厂家扩展*/
	char    DeviceTypeName[33];    /*设备类型描述*/
	char    Addr[CUBM_IPADDR_LEN];              /*ip地址*/
	UINT    port;                  /*端口*/               

	/* 是否已查询到详细PU信息，具体如下：
	第0位：通道信息是否获取标志；第1位：开关量信息是否获取标志；第2位：录像状态是否查询*/
	int  HasGotDetail;    

	void * pAlmDesp;
};

struct group
{
	int   nodetype;
	group* pparent;             /*上层组节点*/
	group* downgroup;           /*下级域*/
	group* pnext;
	unsigned __int64    id;
	char  name[128];
	pu*   pulist;
	BOOL  HasGotDetail;          /*是否已查询到详细PU列表*/

};

struct IpMatrixNode;
struct IpMatrixChannelNode
{
	IpMatrixChannelNode* pnext;
	IpMatrixNode*   pMatric;
	UINT            id;
	int             ChannelType;
	short			ChannelNum;
};
struct IpMatrixNode
{
	IpMatrixNode* pnext;
	BOOL Online;
	char ID[32];
	char IP[64];
	char Name[64];
	UINT port;
	int  ChannelNum;
	unsigned __int64 GroupID;
	char GroupName[33];
	int DeviceType;
	IpMatrixChannelNode* pChannelList;
};


struct PuChannelPositionNode
{
	char PUID[32];
	int  ChannelNo;
	int  ChannelType;
	double x;
	double y;
	PuChannelPositionNode* pnext;
};

struct VersionInfo
{
	char Version[32];
	int CuRole;  /*1:C/S客户端; 2:B/S客户端*/
	int SoftwareFlag;	/*1:文件覆盖; 2:重新安装*/
	int UpdateFlag; /*0:不需要强制升级; 1:需要强制升级*/
	char Ftp_addr[CUBM_IPADDR_LEN];	
	short Ftp_port;
	char Ftp_name[64];
	char Ftp_password[64];
	int Ftp_timeout;/*有效时间*/
	char Ftp_folder[128];/*存放位置*/
};

struct PictureInfo 
{
	PictureInfo* pnext;
	long CapTime;
	char Name[255];
	long Size;
	char Address[CUBM_IPADDR_LEN];	
	long Port;
};

struct PicInfoResult
{
	long totalcount;
	long restcount;
	PictureInfo* pPicInfo;
};

//add by lm 20090415
enum ThresholType
{
	THRESH_RT_CONNECT = 1,	//建立视频连接；
	THRESH_RT_CONNECT_SUCC,	//视频连接成功建立；
	THRESH_RT_CONNECT_FAIL,	//视频连接失败；
	THRESH_RT_DISCON,		//释放视频连接；
	THRESH_RT_DISCON_ABNORMAL,	//异常释放视频连接；
	THRESH_VOD_CONNECT,			//VOD连接；
	THRESH_VOD_CONNECT_FAIL,	//VOD连接失败；
	THRESH_NO_VIDEO,			//无监控视频(无码流);
	THRESH_VIDEO_FRAME_CHANG	//码率跳变；

};

struct ThresholdValue
{
	ThresholType thresholdType;
	int thresholdValue;
};


typedef struct thValueList{
	thValueList	*next;
	ThresholdValue	*obj;
}thValueList;


#define MAX_LOG_PUID_LEN            32
#define MAX_LOG_CHANNELNAME_LEN     64
#define MAX_LOG_DATA_LEN            32
#define MAX_LOG_EXTRA_LEN		    1024

struct NPCMedia_QueryInfo
{
	int   RecordReason;                 //记录原因：手动：0、报警：1，定时：2(本地：未使用)，所有：3
	char  PuId[MAX_LOG_PUID_LEN];       //通道ID
	int   ChannelNo;                    //通道号
	long  BeginTime;					//查询起始时间
	long  EndTime;						//查询结束时间
	int	  from;							//查询条目起始点
	int	  to;							//查询条目结束点
	int   storetype;					//存储位置：平台：1，前端：0(本地：未使用)
};

struct  cubm_CallStatus
{
	int CallListID;
	char PUID[32];
	int ChannelNo;
	int CallStatus;
};
/*********************************************************************
if notifycode = ****_nack, the result is the errorcode
if notifycode = cubm_login_ack , the result is a point to user struct
if notifycode = cubm_pulist_ack, the result is a point to group struct

*********************************************************************/
     
typedef int (* cubmcallback)(long phandle,int notifycode, int msgid, long result, 
							 long errorcode, long reserved2);

/************************************************************************
function:cubm_initial
author: lllei 20080321
param: phandle: a point to bm handle
	   family: AF_INET or AF_INET6
process: initial the basic msg dll
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_initial(long* phandle ,int version, int family);

CUBASICMSG_API void cubm_destory(long phandle);

/************************************************************************
function:cubm_setcallback
author: lllei 20080326
param: handle: bm handle
       proc: callback process
process: set the bm callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_setcallback(long handle, cubmcallback proc);

/************************************************************************
function:cubm_register  this function only used in version 3.0
author: lllei 20080318
param: handle: the bm handle
       username:the register username 
	   serverip:
	   port:
process: register to server,the register result will be notified in callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_register(long handle,char* username,char*password,
								 char* serverip, UINT port);

/************************************************************************
function:cubm_login  this function only used in version 2.0
author: lllei 20080318
param: handle: the bm handle
       username:the login username 
	   serverip: 
	   port:
process: login to server,the login result will be notified in callback
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API int cubm_login(long handle,char* username,char*password,
								 char* serverip,char* sereverid, UINT port);

/************************************************************************
function:cubm_logout  this function only used in version 2.0
author: lllei 20080318
param: handle: the bm handle
process: logout to server
return: 0:success; else:error
************************************************************************/
CUBASICMSG_API void cubm_logout(long handle);

/************************************************************************
function:cubm_pugrouplist
author: lllei 20080321
param: handle: the bm handle
       groupid:the pugroup want to list
	   if groupid is null, will list all the pu
process: send list req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_pugrouplist(long handle,/*in*/int groupid);

/************************************************************************
function:cubm_getpuinfo, this function can only used in 3.0
author: lllei 20080321
param: handle: the bm handle
       puid:the puid want to get info, cant be null
process: send info req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_getpuinfo(long handle,/*in*/char* puid);
CUBASICMSG_API int cubm_getpuinfoex(long handle,/*in*/pu* pulist);
/************************************************************************
function:cubm_ptzcontrol
author: lllei 20080321
param: handle: the bm handle
process: send info req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_ptzcontrol(long handle, char* puid, int channelno,
								   int ptztype, int param1, int param2, char* channelname);

/*透明消息*/
CUBASICMSG_API int cubm_ComTransParent(long handle, char* puid, int channelno,
									char* ComData, int len);

/*日志查询*/
CUBASICMSG_API int cubm_logquery(long handle,unsigned char logType,char *puid,int puChannel, int channeltype,long beginTime,long endTime,
		int startCount,int endCount, long userdata,int logInfo);

/*流量报警上报*/
CUBASICMSG_API int cubm_stream_alarm_ind(long handle,int alarmType,char *puId,int channelNo,char *time);
/*查询断续门限*/
CUBASICMSG_API int cubm_stream_threshold_query_req(long handle);

/*上报收包 丢包状态*/
CUBASICMSG_API int cubm_packet_loseinfo_ind(long handle,char *puId,int channelNo,
											long lostPacket,long rcvPacket);

/*解码矩阵查询*/
CUBASICMSG_API int cubm_ipmatric_query(long handle);
/************************************************************************
function:cubm_pugroup
author: lllei 20080321
param: handle: the bm handle
       groupid:the pugroup want to list
	   if groupid is null, will list all the pu
process: send list req to server
return: 0:error; else:list msg id
************************************************************************/
CUBASICMSG_API int cubm_getsessionid(long handle, /*out*/char* sessionid);

CUBASICMSG_API int cubm_getserverid(long handle, /*out*/char* serverid);
CUBASICMSG_API int cubm_getuserid(long handle, /*out*/ char* userid);

CUBASICMSG_API int cubm_UploadPuChannelPosition(long handle, PuChannelPositionNode* pPositionList, long temphandle);
CUBASICMSG_API int cubm_SendVersionInfo(long handle, VersionInfo* pMyVersion);

CUBASICMSG_API int cubm_ChangePsw(long handle,char* oldpsw, char* newpsw);
CUBASICMSG_API int cubm_QueryPic(long handle, char* puid, int ChannelNo, int channeltype, NPCMedia_QueryInfo* pPicQueryInfo, long temphandle);
CUBASICMSG_API int cubm_DelPic(long handle, char* puid, int ChannelNo, int channeltype, PictureInfo* pPicQueryInfo, long temphandle, int storetype);

CUBASICMSG_API  int cubm_ChangePsw(long handle,char* oldpsw, char* newpsw);

CUBASICMSG_API int cubm_verifyKey(long handle,char* chanllengecode,int codelen);
/*******************************************************
功能：发送获取图片的请求
filename: 图片的名字；
ip: 图片服务器地址；
port: 图片服务器端口；
puserdata: 应用层数据
path: 图片路径(不需要的话可不填)
******************************************************/
CUBASICMSG_API int cubm_httpgetpicbyfilename(long handle, char * filename, char * ip, unsigned port, void * puserdata, char * path = NULL);

CUBASICMSG_API int cubm_query_alm_pic(long handle, NPCMedia_QueryInfo* pPicQueryInfo, char * almid, void * puserdata);

//add by lm 20090415
CUBASICMSG_API int cubm_getthresholdstate(long handle, int threshtype, int threshvalue,void * puserdata);
CUBASICMSG_API int cubm_reportthresholdvalue(long handle ,char* puid,int channelno,int threshtype,void * puserdata);

CUBASICMSG_API void cubm_setbasicinfo(long handle, char* userid, char* username,char*psw, char*serverip, UINT port);

#endif

