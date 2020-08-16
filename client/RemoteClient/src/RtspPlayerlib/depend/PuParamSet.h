 
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PUPARAMSET_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PUPARAMSET_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef PUPARAMSET_EXPORTS
#define PUPARAMSET_API __declspec(dllexport)
#else
#define PUPARAMSET_API __declspec(dllimport)
#endif

#ifndef _PUPARAMSET_H_ 
#define _PUPARAMSET_H_

#define	SIP		0	/*mio发送的sip消息*/
#define	HTTP	1	/*http格式的消息*/
#define	MEDIA	2	/*sip协商*/

#define param_type_almin	1
#define param_type_almout	2

#define param_recv_resp 1	//收到响应
#define param_recv_req	2	//收到请求(事件)

#define PLATFORM_MANUAL_REC	1	//平台手动录像
#define PU_MANUAL_REC		2	//前端手动录像

/*录像状态查询*/
#define QUERY_PLATFORM_REC_STATE PLATFORM_MANUAL_REC
#define QUERY_PU_REC_STATE		 PU_MANUAL_REC

#define param_send_failed_resp -1
//云台(串口)参数
#define param_set_ptz_resp				WM_USER + 1
#define param_get_ptz_resp				WM_USER + 2

//视频编码
#define param_set_encode_resp			WM_USER + 3
#define param_get_encode_resp			WM_USER + 4

//音频编码
#define param_set_audioencode_resp		WM_USER + 5
#define param_get_audioencode_resp		WM_USER + 6

//显示参数
#define param_set_display_resp			WM_USER + 7
#define param_get_display_resp			WM_USER + 8

//字幕参数
#define param_set_osd_resp				WM_USER + 9
#define param_get_osd_resp				WM_USER + 10

//前端存储参数设置
#define param_set_storepolicy_resp		WM_USER + 11
#define param_get_storepolicy_resp		WM_USER + 12

//开关量告警
#define param_set_gpin_alm_resp			WM_USER + 13
#define param_get_gpin_alm_resp			WM_USER + 14

//巡航轨迹
#define param_set_cruise_resp			WM_USER + 15
#define param_get_cruise_resp			WM_USER + 16

//移动侦测使能
#define param_set_alm_motion_dect_resp	WM_USER + 17
#define param_get_alm_motion_dect_resp	WM_USER + 18

//遮挡侦测使能
#define param_set_alm_cover_dect_resp	WM_USER + 19
#define param_get_alm_cover_dect_resp	WM_USER + 20

//丢失侦测使能
#define param_set_alm_lose_dect_resp	WM_USER + 21
#define param_get_alm_lose_dect_resp	WM_USER + 22

#define param_set_alm_config_resp		WM_USER + 23
#define param_get_alm_config_resp		WM_USER + 24

//告警使能
#define param_set_alm_enable_resp		WM_USER + 25
#define param_get_alm_enable_resp		WM_USER + 26

//前端录像参数设置
#define param_get_pu_record_resp		WM_USER + 27
#define param_set_pu_record_resp		WM_USER + 28

//移动侦测区域告警
#define param_set_motion_region_resp	WM_USER + 29
#define param_get_motion_region_resp	WM_USER + 30

//遮挡侦测区域告警
#define param_set_cover_region_resp		WM_USER + 31
#define param_get_cover_region_resp		WM_USER + 32

#define param_set_preset_node_resp		WM_USER + 33
#define param_get_preset_node_resp		WM_USER + 34
#define param_delete_preset_node_resp	WM_USER + 35
#define param_set_cap_resp				WM_USER + 36
#define param_get_cap_resp				WM_USER + 37

//前端录像参数设置
#define param_set_platform_record_resp	WM_USER + 38
#define param_get_platform_record_resp	WM_USER + 39

//视频区域隐藏参数设置
#define param_set_video_hide_resp		WM_USER + 40
#define param_get_video_hide_resp		WM_USER + 41

//获取前端io信息
#define param_get_io_para_resp			WM_USER + 42
//调用预置位
#define param_call_preset_resp			WM_USER + 43

#define param_set_base_param_resp		WM_USER + 44
#define param_get_base_param_resp		WM_USER + 45

//自动归位设置
#define param_set_preset_reset_resp		WM_USER + 46
#define param_get_preset_reset_resp		WM_USER + 47

#define param_start_record_pu_resp		WM_USER + 48	//前端开始录像响应
#define param_stop_record_pu_resp		WM_USER + 49	//前端停止录像响应
#define param_start_record_plat_resp	WM_USER + 50	//平台开始录像响应
#define param_stop_record_plat_resp		WM_USER + 51	//平台停止录像响应
#define param_query_pu_record_status_resp	WM_USER + 52	//查询录像状态:前端
#define param_query_plat_record_status_resp	WM_USER + 53	//查询录像状态:平台

#define param_pu_report_status_req			WM_USER + 54	//前端上报状态(手动录像)
#define param_nru_report_status_req			WM_USER + 55	//nru上报状态(手动录像)

#define param_stop_output_resp				WM_USER + 56	//停止开关量输出的告警，用于接警
#define param_get_pu_time_resp				WM_USER + 57	//获取前端时间
#define param_set_pu_time_resp				WM_USER + 58	//设置前端时间
#define param_get_pu_input_output_resp		WM_USER + 59
#define param_set_pu_input_output_resp		WM_USER + 60	

#define param_set_pu_cap_resp			WM_USER + 61	//前端抓拍图片
#define param_get_npu_resp				WM_USER + 62	//前端图片服务器
#define param_set_npu_resp				WM_USER + 63


//开关量输入状态
#define param_get_pu_input_state_resp		WM_USER + 64
#define param_set_pu_input_state_resp		WM_USER + 65	

//开关量输出状态
#define param_get_pu_output_state_resp		WM_USER + 66
#define param_set_pu_output_state_resp		WM_USER + 67	

#define param_get_pu_version_resp		WM_USER + 68	//前端版本号
#define param_get_cap_status_resp		WM_USER + 69	//获取抓拍状态
#define param_cap_begin_resp			WM_USER + 70	//开始抓拍
#define param_cap_end_resp				WM_USER + 71	//停止抓拍
#define param_set_time_cap_resp			WM_USER + 72	//设置定时抓拍
#define param_get_time_cap_resp			WM_USER + 73	//获取定时抓拍

#define param_get_motion_alm_out_resp	WM_USER + 74	//获取告警联动信息(用于接警)
#define param_get_cover_alm_out_resp	WM_USER + 75	//获取告警联动信息(用于接警)
#define param_get_lose_alm_out_resp		WM_USER + 76	//获取告警联动信息(用于接警)
#define param_get_input_alm_out_resp	WM_USER + 76	//获取告警联动信息(用于接警)
#define param_get_pu_state_resp			WM_USER + 78	//获取前端状态信息
#define param_reset_dispaly_resp		WM_USER + 79	//重置视频参数


/*报警参数类型*/
#define	DISK_PARA				0
#define	ALARM_RECORD			1
#define CAP_PHOTO				2
#define GPIN_ALARM				3
#define VIDEO_LOSE_ALARM		4
#define VIDEO_HIDE_ALARM		5
#define	VIDEO_MOVE_ALARM		6
#define VIDEO_MOVE_ALARM_AREA	7
#define VIDEO_HIDE_ALARM_AREA	8
#define GPIN_ALARM_PLATFORM		9		//平台开关量告警查询
#define VIDEO_LOSE_ALARM_PLATFORM	10	//平台丢失告警查询
#define VIDEO_HIDE_ALARM_PLATFORM	11	//平台遮挡告警查询
#define VIDEO_MOVE_ALARM_PLATFORM	12	//平台移动告警查询
#define ALMOUT_VIDEO_MOVE			13  //视频移动联动告警输出
#define ALMOUT_VIDEO_HIDE			14  //视频遮挡联动告警输出
#define ALMOUT_VIDEO_LOSE			15  //视频丢失联动告警输出
#define ALMOUT_GPIN					16  //输入开关量联动告警输出

//前端状态
#define BIT_PU_MANUAL_REC		0 // 前端手动录像bit标志位
#define BIT_PLATFORM_MANUAL_REC	1 // 平台手动录像bit标志位
#define BIT_PU_TIME_REC			2 // 前端定时录像bit标志位
#define BIT_PLAT_TIME_REC		3 // 平台定时录像bit标志位
#define BIT_ALARM_REC			4 // 告警录像bit标志位

#define PARAM_ALM_MAX_NUM		16  //告警联动的最大数目

struct param_pu_version
{
	char hardwareVersion[33];
	char softwareVersion[33];
	char diskWithholdSize[33];
	char diskUsedSize[33];
	char diskRemainSize[33];
	char devType[33];
};

struct param_pu_time
{
	int mode;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

struct param_pu_input
{
	param_pu_input * pnext;

	int type;
	int chno;  //开关量通道号
	int state; //开关量状态

	int devtype; //1: 常闭型 2:常开型
};
typedef param_pu_input param_pu_output;

struct param_chinfo
{
	char puid[20];
	int chno;
};

//video channel status
struct param_channel_record_state
{
	char puid[20];
	int chno;
	unsigned char recordStatus;	//录像状态
	unsigned char signalStatus;	//连接的视频信号状态
	unsigned char hardwareStatus;	//硬件状态 0:正常 1:异常
	char  rate[33];	//实际码率

	param_channel_record_state * pnext;
};
typedef param_channel_record_state param_video_channel_state;

struct param_disk_state
{
	int  diskid;

	char totalsize[64];	//硬盘容量
	char freesize[64];	//剩余空间
	unsigned char  status; //1:休眠 2:不正常

	param_disk_state * pnext;
};

struct param_alm_in_state
{
	int  almno;
	unsigned char status;

	param_alm_in_state * pnext;
};
typedef param_alm_in_state param_alm_out_state;

struct param_pu_dev_status
{
	char puid[20];
	unsigned char pustate; //0:正常 1:CPU占用太高 2:硬件错误
	
	param_disk_state * pdiskstate;
	param_video_channel_state * pvideochstate;
	param_alm_in_state * palminstate;
	param_alm_out_state * palmoutstate;
};

struct param_channel_base_param
{
	int m_ChannelType;
	int m_ChannelNo;
	char m_ChannelName[33];
};

struct param_pu_io_info
{
	char ID[19];
	char DomainID[7];
	char Name[33];
	char IP[41];
	int DeviceType;
	int PlatformManufactureID;
	int ManufactureID;
	int VideoInNum;
	int VideoOutNum;
	int AudioInNum;
	int AudioOutNum;
	int AlarmInNum;
	int AlarmOutNum;
	int NonStandardNum;
	int MatrixNum;
};

struct param_preset_node
{
	int index;
	char name[64];

	param_preset_node * pnext;
};

//巡航点
struct param_cruisepoint
{
	int presetindex;
	int dwelltime;
	int speed;
	char name[64];

	param_cruisepoint * pnext;
};

//巡航轨迹
struct param_cruise
{
	int ptzid;
	int cruiseid;

	param_cruisepoint * plist;
};

struct param_image_encode
{
	int Type; /*未使用*/
	unsigned EncodeMode;
	unsigned PicQuality;
	unsigned BitRate;
	unsigned BitRateType;
	unsigned FrameRate;
	unsigned ImageSize;
	unsigned StreamType;
	unsigned IFrameInterval;

	unsigned EncodeModeA;
	unsigned PicQualityA;
	unsigned BitRateA;
	unsigned BitRateTypeA;
	unsigned FrameRateA;
	unsigned ImageSizeA;
	unsigned StreamTypeA;
	unsigned IFrameIntervalA;

	int ChannelMode;	//制式
};

//显示参数
struct param_display
{
	int Contrast;
	int Bright;
	int Hue;
	int Saturation;	
	int Whiteness;
};

//视频输入编码参数
struct param_video_in_encode
{
	param_image_encode ImageEncode;
	param_display Display;
};

//音频输入编码参数
struct param_audio_in_encode
{
	int EncodeMode;
	int Sample;
	int TrackNo;
	int EncodeBitRate;
	int QuanBitRate;
};

//osd参数
struct param_osd
{
	int  bitmapX;
	int  bitmapY;
	BOOL bitmapTimeEnable;
	BOOL bitmapTextEnable;
	char bitmapText[129];
	int  bitmapTextX;
	int  bitmapTextY;
};

//云台串口参数
struct param_ptz
{
	unsigned BaudRate;
	unsigned DataBit;
	unsigned Parity;
	unsigned StopBit;
	unsigned Mode;
	unsigned FlowControl;
	char  DecoderType[33];
	char  DecoderAddress[33];
};

struct param_alm_output
{
	int AlmNo;
	int AlmState;
};


//时间段信息
struct param_time_section
{
	int StartHour;
	int StartMinute;
	int EndHour;
	int EndMinute;
};

//有3个时间段
struct param_time
{
	param_time_section Time[3];
};

//有8天的时间段信息，包括每天
struct param_period
{
	int errorcode; //0：表示正常；否则，表示时间字符串非法
	param_time DayTime[8];
};

struct param_camera_track
{
	char PuID[20];
	int Chno;
	char name[64];

	int preset;
};

struct param_camera
{
	char PuID[20];
	int Chno;
	char name[64];
};

//移动侦测区域
struct param_motion_detection_region
{
	unsigned Sensitivity;
	char Blocks[512];	
};

struct param_almout
{
	int AlmOutputNo;
	int State;
};

struct param_alm_audio_out
{
	int audioOutId;
	BOOL audioAlmEnable;
	int almType;
	char almFile[256];
};

//告警配置参数
struct param_alarm_enable
{
	char AlmName[64];
	unsigned char almEnable;	//是否布防 
	param_period period;   	//布防时间

	BOOL bReadSecond;	//告警读秒使能：没用
	int ReadSecond;		//告警读秒：没用 

	BOOL bPuCap;		//前端本通道告警抓拍使能
	BOOL bUpload;		//图片上传：没用
	BOOL bOtherCameraCap;	//其它摄像头联动抓拍使能（包括其它通道）
	int CapCameraCount;	//联动抓拍摄像头的数目
	param_camera CapCamera[PARAM_ALM_MAX_NUM];	//联动抓拍摄像头的详细信息

	BOOL bPuRec;	//前端本通道告警录像使能

	BOOL bOtherCameraPuRec;	//前端联动其它摄像头录像使能（包括其它通道）
	int PuRecCameraCount;		//前端联动录像摄像头的数目
	param_camera PuRecCamera[PARAM_ALM_MAX_NUM];//前端联动录像摄像头的详细信息

	BOOL bPlatformRec;	//平台本通道告警录像使能

	BOOL bOtherCameraPlatRec;	//平台联动其它摄像头录像使能（包括其它通道）
	int PlatformRecCameraCount;	//平台联动录像摄像头的数目
	param_camera PlatformRecCamera[PARAM_ALM_MAX_NUM];//平台联动录像摄像头的详细信息

	BOOL bAlmOut;	//告警输出使能
	int  AlmOutCount;	//告警输出数目
	param_almout AlmOutput[PARAM_ALM_MAX_NUM]; //告警输出详细信息

	BOOL bTrack;	//本通道追踪告警使能
	int  TrackPreset;	//本通道追踪告警预置位

	BOOL bOtherTrack;	//其它摄像头追踪告警
	int  OtherTrackCount;	//其它摄像头追踪告警数目
	param_camera_track OtherTrack[PARAM_ALM_MAX_NUM];	//其它追踪告警摄像头详细信息

	BOOL bIpMatrix;	//告警矩阵使能：没用
	char IpMatrix;	//矩阵信息：没用
	int  MatrixNo;	//矩阵通道号：没用

	param_alm_audio_out almAudioOut;
};

//区域
struct param_region
{
	int x;
	int y;
	int cx;
	int cy;
};

//遮挡侦测区域
struct param_cover_detection_region
{
	unsigned Sensitivity;
	int RegionCount;
	param_region  Region[16];
};

typedef param_cover_detection_region param_video_hide_region;

//遮挡侦测配置
struct param_cover_detection
{
	BOOL bEnable;
	char AlmTime[256];
	int x;
	int y;
	int width;
	int height;
	param_alm_output AlmOut[256];   //第一个元素存数组的长度，包含该元素
	int AlmRec[256];		//第一个元素存数组的长度，包含该元素
};

struct param_lose_detection
{
	BOOL bEnable;
	param_alm_output AlmOut[256];   //第一个元素存数组的长度，包含该元素
};

//抓拍参数
struct param_cap
{
	int capResolution;
	int capQuality;	//抓拍质量
	int capTimes;	//抓拍张数(频率)

	BOOL bTimeCap;
	BOOL bPeriodCap;
	int interval;			//抓拍间隔
	param_period period;		//周期抓拍时间
	char beginTime[32]; 
	char endTime[32];	
};

//前端录像参数
struct param_record
{
	char taskName[32];
	int taskPolicy;
	char mediaFormat[32];
	int mediaType;
	//年 月 日 小时 分 中间用空格隔开
	char beginTime[32]; 
	char endTime[32];	
	BOOL bRecAudio;
	BOOL bAlmPreRec;
	int preRecTime;
	BOOL bIframeRec;
	int FrameInterval;
	//告警恢复后录像时间
	unsigned int recTime;  
	char capacityStr[33];
	BOOL bTimeRec;
	BOOL bPeriodRec;
	//周期录像时间
	param_period period;   

	int timespan;
};

struct param_default_preset
{
	int index;
	int interval;
};

struct param_error
{
	int value;
	int errcode;
	int puerr;		//告警专用
	int platerr;	//告警专用
};

struct param_param
{
	int type;
	
	void * pparam;
	void * plogdata;

	param_error err;
};

typedef int (*moduleparamsetcallback)(int notifycode, int paramtype, void * pparam, long userdata);

PUPARAMSET_API void OutPutString(char * str);
/*初始化参数设置模块*/
PUPARAMSET_API int ParamInitial(long * phandle, moduleparamsetcallback callbackfunc, int family);
/*销毁参数设置模块*/
PUPARAMSET_API void ParamDestory(long * phandle);

/*获取前端告警输入输出信息*/
PUPARAMSET_API int ParamGetPuIoInfo(long handle, char * puid, void * userdata, void * plogdata = NULL);

/*客户ID, name, 目的IP, 协议类型, 目的ID,源ID, 会话ID,序号,写入dll中保存*/
PUPARAMSET_API void ParamSetInitial(char * cid, char * cname, char * destID, char * sessID, unsigned int seqNum, char * ip, int port, int protocol);

/*puid,chno,chtype, 设备ID和name 写入dll中保存*/
PUPARAMSET_API void ParamSetMsgChannel(char * puid, char * name, short chno, unsigned char chtype);

/*发送串口参数设置请求*/
PUPARAMSET_API int ParamSetPuSerialPortReq(long handle,void * lparam , void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuSerialPortReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*开关量输入输出请求*/
PUPARAMSET_API int ParamSetInputOutputReq(long handle, void * lparam, int count, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetInputOutputReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*获取告警联动输出(接警)
almtype:开关量: 1, 2; 视频丢失: 3, 4; 视频移动: 5, 6; 视频遮挡: 101, 102;
*/
PUPARAMSET_API int ParamGetOpAlmOut(long handle,char * puid, int chno, int almtype/*告警通知类型*/, void * userdata, void * plogdata = NULL);
/*停止告警输出(接警)*/
PUPARAMSET_API int ParamStopAlmOutReq(long handle, void * lparam, int count, void * userdata, void * plogdata = NULL);

/*开关量输入状态查询*/
PUPARAMSET_API int ParamGetAlmInStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSetAlmInStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*开关量输出状态查询*/
PUPARAMSET_API int ParamGetAlmOutStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSetAlmOutStateReq(long handle,void * lparam, void * userdata, void * plogdata = NULL);

/*时间参数请求*/
PUPARAMSET_API int ParamSetTimeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetTimeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*视频图像编码请求*/
PUPARAMSET_API int ParamSetVideoEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetVideoEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*视频区域隐藏请求*/
PUPARAMSET_API int ParamSetVideoHideReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetVideoHideReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*音频编码请求*/
PUPARAMSET_API int ParamSetAudioEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAudioEncodeReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*显示参数请求*/
PUPARAMSET_API int ParamSetDisplayReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetDisplayReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端存储请求*/
PUPARAMSET_API int ParamSetPuStoreReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuStoreReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端录像参数设置*/
PUPARAMSET_API int ParamSetPuRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPuRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端录像参数设置*/
PUPARAMSET_API int ParamSetPlateformRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetPlateformRecordReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*文字字幕请求*/
PUPARAMSET_API int ParamSetImageTextReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetImageTextReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*移动侦测区域设置请求*/
PUPARAMSET_API int ParamSetMotionRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetMotionRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*移动侦测告警设置请求(不含区域)*/
PUPARAMSET_API int ParamSetMotionAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetMotionAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*遮挡侦测区域设置请求*/
PUPARAMSET_API int ParamSetCoverRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCoverRegionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*视频遮挡侦测告警设置请求(不含区域)*/
PUPARAMSET_API int ParamSetCoverAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCoverAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*视频丢失侦测告警设置请求*/
PUPARAMSET_API int ParamSetLoseAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetLoseAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*开关量告警布撤防设置*/
PUPARAMSET_API int ParamSetGpinAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetGpinAlmReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*告警设置抓拍参数设置请求*/
PUPARAMSET_API int ParamSetCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*预置点请求 设置指定通道的预置点*/
PUPARAMSET_API int ParamSetPresetNodeReq(long handle,  char * puid, int chno, int index, char * presetname, char * puname, void * userdata, void * plogdata = NULL);

/*获取指定通道的所有预置点预置点*/
PUPARAMSET_API int ParamGetPresetNodeReq(long handle,  char * puid, int chno, void * userdata, void * plogdata = NULL);

/*删除指定通道的指定预置点*/
PUPARAMSET_API int ParamDeletePresetNodeReq(long handle,  char * puid, int chno, int index, void * userdata, void * plogdata = NULL);

/*摄像头预置位自动归位*/
PUPARAMSET_API int ParamSetResetReq(long handle, char * puid, int chno, int index, int interval, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetResetReq(long handle, char * puid, int chno, void * userdata, void * plogdata = NULL);

/*巡航轨迹设置请求*/
PUPARAMSET_API int ParamSetCruiseReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetCruiseReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamDeleteCruiseReq(long handle, int cruiseno, void * userdata, void * plogdata = NULL);

/*前端日志请求*/
PUPARAMSET_API int ParamGetPuLogReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端设置布、撤防*/
PUPARAMSET_API int ParamSetAlmActionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAlmActionReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端设置告警联动*/
PUPARAMSET_API int ParamSetAlmOpReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetAlmOpReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*时钟同步*/
PUPARAMSET_API int ParamClockSynchReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*透明通道请求*/
PUPARAMSET_API int ParamComTransparentReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端抓拍(单次)*/
PUPARAMSET_API int ParamPuCapPicReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
//PUPARAMSET_API int ParamGetCapPicReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*前端抓拍(连续)*/
PUPARAMSET_API int ParamPuCapPicBeginReq(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamPuCapPicEndReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);

/*查询抓拍状态*/
PUPARAMSET_API int ParamGetPuCapPicStatusReq(long handle,  void * lparam, BOOL bManual, void * userdata, void * plogdata = NULL);

/*定时抓拍*/
PUPARAMSET_API int ParamSetTimeCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetTimeCapReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);


/*查询设备状态*/
PUPARAMSET_API int ParamGetPuDeviceStatusReq(long handle,  void * lparam, void * userdata, void * plogdata = NULL);
/*巡航轨迹调用*/
PUPARAMSET_API int ParamPtzCallControl(long handle, char* puid, int channelno,int ptztype, int param1, int param2, void * userdata, void * plogdata = NULL);

PUPARAMSET_API bool PeriodIsValid(param_time * pday);

/*通道基本参数配置*/
PUPARAMSET_API int ParamSetChannelBaseInfo(long handle, void * lparam, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamGetChannelBaseInfo(long handle, void * lparam, void * userdata, void * plogdata = NULL);

/*手动: 前端和平台录像
#define PLATFORM_MANUAL_REC	//平台手动录像
#define PU_MANUAL_REC			//前端手动录像
*/
PUPARAMSET_API int ParamManualStartRecordReq(long handle, int type, char * puid, int chno, char * cuid, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamManualStopRecordReq(long handle, int type, char * puid, int chno, char * cuid, void * userdata, void * plogdata = NULL);

/*查询录像状态:pu 和 platform
#define QUERY_PLATFORM_REC_STATE
#define QUERY_PU_REC_STATE
*/
PUPARAMSET_API int ParamQueryRecordState(long handle, int type, char * puid, char * cuid, void * userdata, void * plogdata = NULL);
PUPARAMSET_API int ParamSendEventResp(long handle, int errcode, void * plogdata = NULL);

/*前端设备版本号查询*/
PUPARAMSET_API int ParamPuVersionReq(long handle,  char * puid, void * userdata, void * plogdata = NULL);

/*获取前端状态*/
PUPARAMSET_API int ParamGetPuStatus(long handle, char * puid, void * userdata, void * plogdata = NULL);

/*设置视频显示参数恢复默认*/
PUPARAMSET_API int ParamReSetDisplay(long handle, char * puid, int chno, void * userdata, void * plogdata = NULL);

#endif

