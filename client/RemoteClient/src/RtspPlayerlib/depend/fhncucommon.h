
#if !defined FHNCUCOMMON_H
#define FHNCUCOMMON_H

#define CUMSG_VERSION_2    1
#define CUMSG_VERSION_3    2

#define RECORD_STORETYPE_PU            0
#define RECORD_STORETYPE_SERVER        1/*录像文件存储位置：NRU*/
#define RECORD_STORETYPE_LOC		   2/*录像文件存储位置：LOCAL*/



#define TREE_NODE_LEVEL_GROUP         0   /*设备组*/
#define TREE_NODE_LEVEL_PU            1   /*设备*/
#define TREE_NODE_LEVEL_CHANNEL       2   /*通道*/



#define cubm_error_sendmsg    10001
#define cubm_error_ielack     10002
#define cubm_error_picsize_too_lager    10006	/*图片太大*/
#define cubm_error_findnotsrv	404	/*找不到服务器*/
#define cubm_error_findnotfile	204 /*找不到图片文件*/

#define cubm_error_register_timeout  10003   /*注册消息发送超时*/
#define cubm_error_register_resp     10004   /*注册消息返回失败*/
#define cubm_error_nullmsg           10005   /*空消息*/
#define cubm_error_readikey          10006   /*读取fhnkey错误*/

enum enumpackettype
{
	PT_RTP = 1,
	PT_TS,
	PT_RTP_VERSION2,
	PT_RTP_VERSION3,

};

enum enumtranstype
{
	TT_TCP = 1,  //SOCK_STREAM
	TT_UDP,   //SOCK_DGRAM
};

enum enummediatype
{
	MT_VIDEO = 1,
	MT_SPEAK = 2,
	MT_BROAD = 3,
	MT_SUBSTREAM = 4,   //子码流

};

struct rtppacketport
{
	unsigned int rtpport;
	unsigned int rtcpport;
	unsigned int rtpsocket;
	unsigned int rtcpsocket;
};

struct fhnrtv2_destlist
{
	fhnrtv2_destlist *pnext;
	char              puid[32];
	int               channelno;
};

/*对回放视频流 从sdp中获取视频相关信息 
  如果sdp中没有携带相关信息时，devtype 填成12 picwidth 702 picheight 576 timescale 90000
  图像长宽填写错误可能导致视频流播放时图像显示不正常
  timescale 填写错误可能导致录像回放时播放不流畅*/
struct DeviceDecInfo
{
	int devtype;
	int picwidth;
	int picheight;
	unsigned int timescale;  /*1S的时间戳间隔*/
	char config[512];
};


/*rtp媒体描述信息*/
struct fhn_MediaInfo_rtp 
{
	int pt;         /*payload*/
	int TimeSpan; /*时间戳间隔*/
	int v_width;   /*视频宽*/
	int v_height;  /*视频高*/
};

/*媒体协商的信息*/
struct fhn_Call_NetWork_Info
{

	char  DestIP[32];
	short DestRcvPort;
	short DestSendPort;
	short LocalRcvPort;
	short LocalSendPort;

	int   SdpCodec;
	char  SdpMap[512];

};

typedef enum rtsp_reply_type
{
	RTSP_PLAY_REPLAY = 1,     /*建立连接或操作回应，需要判断错误码*/  
	RTSP_STREAM_CUT,      /*5秒没有媒体数据*/
	RTSP_STREAM_RECV_ERROR,  /*TCP方式接受数据错误*/
	RTSP_SERVER_SHUTUP,   /*服务器断开连接*/
	RTSP_RTP_DATA,         /*TCP 方式收到媒体数据包*/
	RTSP_RTCP_DATA,         /*TCP方式收到RTCP包*/   
	RTSP_CALC_FRAMERATE  /*定时统计请求*/

}cm_reply_type_t;
typedef enum loc_file_reply
{
	FILE_PLAYOK,         //play video ok
	FILE_PLAYHEAD,       //back to head
    FILE_PLAYOVER,       //play over
	FILE_PLAYERROR       //play error
}loc_file_reply_type;


#define RTSP_RESP_SUCCESS          0   /*成功*/
#define RTSP_RESP_ERROR_TIMEOUT    1   /*响应超时 5秒*/
#define RTSP_RESP_ERROR_NOFILE     2   /*找不到文件*/
#define RTSP_RESP_ERROR_OTHER      3   /*其他错误*/
#define RTSP_RESP_ERROR_RECEIVE    4   /*接收数据错误*/
#define RTSP_RESP_ERROR_SOCKET     5   /*创建socket错误*/
#define RTSP_RESP_FINISH		   6   /*文件播放完毕*/


enum ePlayOption
{
	PLAY_FAST,
	PLAY_FASTSEEK,
	PLAY_SLOW,
	PLAY_SLOWSEEK,
	PLAY_FWOD,
	PLAY_FWODSEEK,
	PLAY_BACK,
	PLAY_BACKSEEK,
	PLAY_PAUSE,
	PLAY_PAUSESEEK,
	PLAY_CONT,
	PLAY_SETPOS,
	PLAY_GETFRAMERATE,
	PLAY_SETTIME,      /*指定播放时间点(秒数)*/
};



/*rtsp 返回消息*/
enum ERecPlayType
{
	VOD_CONURL_FAIL,           //回放socket链接失败
	VOD_CONURL_TIMEOUT,        //回放过程中连接超时

	VOD_RTSP_UNKNOW_RESP,       //未知回应
	VOD_START_RTSP_RESP,        //start vod rtsp回应
	VOD_STOP_RTSP_RESP,         //stop vod rtsp 回应
	VOD_SPEED_RTSP_RESP,        //快慢放rtsp回应
	VOD_SCALE_RTSP_RESP,        //快进、退rtsp回应
	VOD_PAUSE_RTSP_RESP,        //暂停rtsp回应
	VOD_CONPLAY_RTSP_RESP,      //继续播放rtsp回应
	VOD_SPOTPLAY_RTSP_RESP,     //定位播放rtsp回应
	VOD_PLAY_STREAM_CUT,        //播放时链接出错
	VOD_PLAY_OVER,              //播放完毕

	DOWN_CONURL_FAIL,           //下载socket链接失败
	DOWN_CONURL_TIMEOUT,        //下载过程中连接超时

	DOWN_RTSP_UNKNOW_RESP,      //未知回应
	DOWN_STRAT_RTSP_RESP,       //下载rtsp请求回应
	DOWN_STOP_RTSP_RESP,        //停止下载rtsp请求回应
	DOWN_SPEED_RTSP_RESP,       //下载变速rtsp回应
	DOWN_STREAM_CUT,            //下载时链接出错
	DOWN_OVER,                  //下载完毕

	OPEN_FILE_RET,           //open file success
	OPEN_FILE_FAIL,           //open file failed
	PLAY_FILE_RET,           //play file error
	PLAY_FILE_END,            //the end of the playing file
	PLAY_FILE_HEAD,           //back to the head of the playing file
};

#define CHANNEL_TYPE_NULL    0
#define CHANNEL_TYPE_VIDEO_IN  1
#define CHANNEL_TYPE_ALARM_IN  5

#define STORE_POS_PU 						0 /*前端*/
#define STORE_POS_NPC   					1 /*图像服务器*/
#define STORE_POS_LOC						2 /*本地*/

#define Media_FileType_PIC					1 /*图片文件*/
#define Media_FileType_RECORD				2 /*录像文件*/

#define RECORD_REASON_MANUAL				0 /*手工*/
#define RECORD_REASON_ALM					1 /*报警*/
#define RECORD_REASON_TIME					2 /*定时*/
#define RECORD_REASON_ALL					3 /*所有*/
#define RECORD_REASON_DOWNLOAD				4 /*下载*/

#define MAX_LOG_PUID_LEN            32
#define MAX_LOG_CHANNELNAME_LEN     64
#define MAX_LOG_DATA_LEN            32
#define MAX_LOG_EXTRA_LEN		    1024

#include <stdlib.h>

typedef struct LocalMedia_FileInfo    LocalMedia_FileInfo;
struct LocalMedia_FileInfo
{
	int  RecordType;                               //记录类型，图片、录像
	char FilePath[_MAX_PATH] ;                     //文件绝对路径，含文件名
	int  RecordReason;                             //记录原因：一般、告警、手工
	char PuId[MAX_LOG_PUID_LEN];                   //通道ID
	int  ChannelNo;                                //通道号
	char ChannelName[MAX_LOG_CHANNELNAME_LEN];     //通道名称
	char Createtime[MAX_LOG_DATA_LEN];             //文件创建时间
    char Endtime[MAX_LOG_DATA_LEN];                //录像文件结束时间，如果是图片则为NULL 
	char extra[MAX_LOG_EXTRA_LEN];                 //其他信息，用于扩展
};


typedef struct LocalMedia_FileList    LocalMedia_FileList;    
struct LocalMedia_FileList
{
	LocalMedia_FileList	*next;
	LocalMedia_FileInfo	*obj;
};


typedef struct LocalMedia_QueryInfo    LocalMedia_QueryInfo;
struct LocalMedia_QueryInfo
{
	int   RecordType;                     //图片、录像、所有
	int   RecordReason;                   //记录原因：一般、报警、手工、所有
	char  PuId[MAX_LOG_PUID_LEN];         //通道ID
	int   ChannelNo;                      //通道号
	char  BeginTime[MAX_LOG_DATA_LEN];    //查询起始时间
	char  EndTime[MAX_LOG_DATA_LEN];      //查询结束时间
	char  extra[MAX_LOG_EXTRA_LEN];       //其他信息,用于扩展
};

enum enumCoFileType{
	COFILE_UNKOW = 0,
	COFILE_DAHU = 1,      /*大华*/
	COFILE_HIKA ,         /*海康*/
	COFILE_FHN,           /*烽火*/
	COFILE_LC,            /*朗驰*/
	COFILE_HB,            /*汉邦*/
	COFILE_TOPSEE,        /*天视通*/
	COFILE_STC,           /*三立*/
};


/*RTP payload 媒体类型定义*/
#define PAYLOAD_AUDIO_FHN_G711    8        
#define PAYLOAD_AUDIO_FHN_ADPCM   36
#define PAYLOAD_AUDIO_FHN_PCM     42
#define PAYLOAD_AUDIO_DAHUA       38
#define PAYLOAD_AUDIO_STC         41
#define PAYLOAD_AUDIO_HIKI        43
#define PAYLOAD_AUDIO_LC          45
#define PAYLOAD_AUDIO_HB          51


#define PAYLOAD_MEDIA_FHN_H264    99
#define PAYLOAD_MEDIA_FHN_MPEG4   96
#define PAYLOAD_MEDIA_FHN_MPEG4_1 35
#define PAYLOAD_MEDIA_DAHUA       37
#define PAYLOAD_MEDIA_STC         40
#define PAYLOAD_MEDIA_HIKI        53
#define PAYLOAD_MEDIA_LC          44
#define PAYLOAD_MEDIA_HB          50
#endif