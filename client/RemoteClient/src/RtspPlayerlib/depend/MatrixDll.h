
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MATRIXDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MATRIXDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MATRIXDLL_EXPORTS
#define MATRIXDLL_API __declspec(dllexport)
#else
#define MATRIXDLL_API __declspec(dllimport)
#endif

#ifndef _MATRIX_H_
#define _MATRIX_H_

#define DUTYPE 4
#define PUTYPE 10

//消息类型
enum MATRIXDLL_MSG_TYPE
{	
	MATRIX_SET_POLL_REQ = WM_USER + 1,
	MATRIX_SET_POLL_RESP,
	MATRIX_START_POLL_REQ,
	MATRIX_START_POLL_RESP,
	MATRIX_STOP_POLL_REQ,
	MATRIX_STOP_POLL_RESP,

	MATRIX_SET_RTV_REQ,
	MATRIX_SET_RTV_RESP,
	MATRIX_START_RTV_REQ,
	MATRIX_START_RTV_RESP,
	MATRIX_STOP_RTV_REQ,
	MATRIX_STOP_RTV_RESP,

	MATRIX_SET_RTV_COMPOUND_REQ,
	MATRIX_SET_RTV_COMPOUND_RESP,
	MATRIX_START_RTV_COMPOUND_REQ,
	MATRIX_START_RTV_COMPOUND_RESP,
	MATRIX_STOP_RTV_COMPOUND_REQ,
	MATRIX_STOP_RTV_COMPOUND_RESP,

	MATRIX_SET_POLL_COMPOUND_REQ,
	MATRIX_SET_POLL_COMPOUND_RESP,
	MATRIX_START_POLL_COMPOUND_REQ,
	MATRIX_START_POLL_COMPOUND_RESP,
	MATRIX_STOP_POLL_COMPOUND_REQ,
	MATRIX_STOP_POLL_COMPOUND_RESP,

	MATRIX_ALARM_ENABLE_STATE_REQ,
	MATRIX_ALARM_ENABLE_STATE_RESP,
	MATRIX_ALARM_STATE_MAINTAIN_REQ,
	MATRIX_ALARM_STATE_MAINTAIN_RESP,
	MATRIX_AUDIO_START_REQ,
	MATRIX_AUDIO_START_RESP,
	MATRIX_AUDIO_STOP_REQ,
	MATRIX_AUDIO_STOP_RESP,
	MATRIX_SPEAK_START_REQ,
	MATRIX_SPEAK_START_RESP,
	MATRIX_SPEAK_STOP_REQ,
	MATRIX_SPEAK_STOP_RESP,
	MATRIX_POLL_PIC_SIZE_REQ,
	MATRIX_POLL_PIC_SIZE_RESP,
	MATRIX_DU_REBOOT_REQ,
	MATRIX_DU_REBOOT_RESP,
	MATRIX_DU_VIDEO_ACK_REQ,
	MATRIX_DU_VIDEO_ACK_RESP,
	MATRIX_TB_TYPE_REQ,
	MATRIX_TB_TYPE_RESP,

	MATRIX_QUERY_POLL_RULE_REQ,
	MATRIX_QUERY_POLL_RULE_RESP,

	MATRIX_SEND_MSG_FAILED,
	MATRIX_STOP,
	MATRIX_UNKOWNN_MSG_TYPE,
};

struct MatrixDuInfo
{
	char	id[20];
	char	ip[64];
	int		port;
	int		devtype;
	int     channelnum;
};

struct MatrixUserInfo
{
	char id[64];
	char name[128];
};

struct PuChannel
{
	char nid[20];
	int chno;
	char name[64];
	int type;
	int interval;
	PuChannel * pnext;
};

struct MatrixAlarmEnableInfo
{
	MatrixAlarmEnableInfo * pnext;
	char nid[20];
	int devtype;
	int chno;
	unsigned int ienble; 
};
typedef MatrixAlarmEnableInfo MatrixAlarmMaintainInfo;
typedef MatrixAlarmEnableInfo MatrixPicSizeInfo;

struct MatrixResult
{
	long errcode;
	void * pdata;
};

typedef int (*MatrixCallBack)(int msgtype, MatrixResult * presult, void * puserdata);
/*初始化矩阵控制*/
MATRIXDLL_API int  MatrixInitial(long * phandle, int family);
/*销毁矩阵控制*/
MATRIXDLL_API void  MatrixDestroy(long handle);		
/*注册回调函数*/
MATRIXDLL_API void MatrixRegModule(long handle, MatrixCallBack callbackproc);	

/*设置解码器信息*/
MATRIXDLL_API void MatrixSetDuInfo(char * id, char * ip, int port, int type, int channelnum); 
/*设置用户信息*/
MATRIXDLL_API void MatrixSetUserInfo(char * id, char * name);  

/*设置轮巡策略*/
MATRIXDLL_API int MatrixSetPollReq(long handle, int msgtype, int chno, PuChannel * pchlist, void * pdata);
/*开始轮巡请求*/
MATRIXDLL_API int MatrixStartPollReq(long handle,  int msgtype, int chno, void * pdata);
/*停止轮巡播放*/		
MATRIXDLL_API int MatrixStopPollReq(long handle, int msgtype, int chno, void * pdata);

/*设置实时视频*/
MATRIXDLL_API int MatrixSetRtvReq(long handle, int msgtype, int chno, PuChannel * pchlist, void * pdata);
/*开始实时视频请求*/
MATRIXDLL_API int MatrixStartRtvReq(long handle,  int msgtype, int chno, void * pdata);
/*停止实时视频播放*/		
MATRIXDLL_API int MatrixStopRtvReq(long handle, int msgtype, int chno, void * pdata);

/*设置轮巡画面合成*/
MATRIXDLL_API int MatrixSetPollCompoundReq(long handle, int msgtype, int chno, int compno, int RegionNum, PuChannel * pchlist, void * pdata);
/*开始对轮巡画面合成*/
MATRIXDLL_API int MatrixStartPollCompoundReq(long handle, int msgtype, int chno,int compno, int RegionNum, void * pdata);
/*停止轮巡画面合成*/
MATRIXDLL_API int MatrixStopPollCompoundReq(long handle, int msgtype, int chno,int compno, int RegionNum, void * pdata);

/*设置实时视频合成请求*/
MATRIXDLL_API int MatrixSetRtvCompoundReq(long handle, int msgtype, int chno, int compno, int RegionNum, PuChannel * pchannel, void * pdata);
/*开始实时视频合成请求*/
MATRIXDLL_API int MatrixStartRtvCompoundReq(long handle, int msgtype, int chno, int compno, int RegionNum, void * pdata);
/*停止实时视频合成请求*/
MATRIXDLL_API int MatrixStopRtvCompoundReq(long handle, int msgtype, int chno, int compno, int RegionNum, void * pdata);

/*解码器告警状态使能设置*/
MATRIXDLL_API int MatrixAlarmEnableStateReq(long handle, int msgtype, int chno, MatrixAlarmEnableInfo * plist, void * pdata);

/*解码器告警状态维持设置*/
MATRIXDLL_API int MatrixAlarmStateMaintainReq(long handle, int msgtype, int chno, MatrixAlarmMaintainInfo * plist, void * pdata);

/*音频开关设置*/
MATRIXDLL_API int MatrixAudioReq(long handle, int msgtype, int chno, PuChannel * pchannel, void * pdata);
/*对讲开关设置*/
MATRIXDLL_API int MatrixSpeakReq(long handle, int msgtype, int chno, PuChannel * pchannel, void * pdata);

/*解码器图像大小设置*/
MATRIXDLL_API int MatrixPicSizeReq(long handle, int msgtype, int chno, MatrixPicSizeInfo * plist, void * pdata);
/*解码器重启请求*/
MATRIXDLL_API int MatrixDuReBootReq(long handle, int msgtype, char * duid, void * pdata);

/*解码器视频连接确认消息*/
MATRIXDLL_API int MatrixDuVideoAckReq(long handle, int msgtype, int chno, int compno, PuChannel * pchannel, void * pdata);

/*解码器电视模式*/
MATRIXDLL_API int MatrixDuTBTypeReq(long handle, int msgtype, int chno, int mode, void * pdata);

/*查询du状态*/
MATRIXDLL_API int MatrixQueryDuStateReq(long handle, void * pdata);

#endif
