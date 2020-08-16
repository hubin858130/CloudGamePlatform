#ifndef _MATRIX_STATE_H_
#define _MATRIX_STATE_H_

#include "stdafx.h"
#include "MatrixDll.h"
#include <string>
#include "msgdef.h"
#include "iedef.h"

#define CONTENT_LEN		1024

#define MASK_PLAY_STATE_ZERO			(0x00)
#define MASK_PLAY_STATE					(0x01)		
#define MASK_PLAY_STATE_ALM_ENABLE		(MASK_PLAY_STATE << 0)
#define MASK_PLAY_STATE_ALM_KEEPTIME	(MASK_PLAY_STATE << 1)
#define MASK_PLAY_STATE_VIDEO_SIZE		(MASK_PLAY_STATE << 2)
#define MASK_PLAY_STATE_ALL				(MASK_PLAY_STATE_ALM_ENABLE | MASK_PLAY_STATE_ALM_KEEPTIME | MASK_PLAY_STATE_VIDEO_SIZE)

/*add by lxf*/
enum CHANNEL_STATE
{
	CHANNEL_FREE = 0,
	
	//单路实时视频请求状态
	RTV_SET,
	RTV_START,
	RTV_PLAY,

	//多路轮巡请求状态
	POLL_SET,
	POLL_START,
	POLL_PLAY,

	COMPOUND_READY,
	EMPTY_VALUE = 1000,
};

enum COMPOUND_STATE
{
	COMPOUND_FREE = 100,

	COMPOUND_RTV_SET,
	COMPOUND_RTV_START,
	COMPOUND_RTV_PLAY,

	COMPOUND_POLL_SET,
	COMPOUND_POLL_START,
	COMPOUND_POLL_PLAY,
};

//合成通道状态(用于兼容2.0版本,更新播放的视频通道状态)
struct ChDetailState
{
	unsigned long mask;			//掩码

	char puid[20];
	int  chno;
	int  compno;
	int  almenable;		//报警使能标志
	int  almkeeptime;	//报警保持时间
	int  videosize;		//视频大小，目前支持：原始大小和全屏两种
};

//前端设置播放时状态(用于兼容2.0版本)
struct PuChPlayState
{
	int almenable;
	int  almkeeptime;	
	int  videosize;		
	char name[128]; /*视频通道名字*/
};

//轮巡列表,包括puid, chno, 该视频通道的状态
struct PollPlayList
{
	PollPlayList * pnext;

	char puid[20];
	int  chno;
	int  interval;
	PuChPlayState chstate;
};

//解码通道合成播放策略的状态信息
struct ComPlayState
{
	int  compno;		//合成通道号
	ComPlayState * pnext;
	PollPlayList * planlist;	//画面合成的轮巡列表
	char name[128];
	COMPOUND_STATE state;
};

//解码通道状态
struct ChannelState
{
	ChannelState * pnext;

	PollPlayList * planlist;	//轮巡列表
	ComPlayState * comlist;		//合成列表

	int chno;
	CHANNEL_STATE playstate;	//轮巡or合成
	int compoundNum;
	char name[1024]; /*轮巡或视频名字*/
};

//解码器的状态
struct DuState
{
	DuState * pnext;

	ChannelState * pchannellist;
	char duid[32];
	BOOL baudio;
	BOOL bspeak;
	//判断是否已经读取过相关前端信息
	BOOL bpuinfo;
};

MATRIXDLL_API DuState * SetDuState(char * duid, BOOL baudio = EMPTY_VALUE, BOOL bspeak = EMPTY_VALUE);
MATRIXDLL_API void SetDuChState(char * duid, int duchno, CHANNEL_STATE state, char * name = NULL, PuChannel * playlist = NULL);
MATRIXDLL_API void SetDuChReadyState(char * duid, int duchno, int comnum);
MATRIXDLL_API void SetDuCompChState(char * duid, int duchno, int comno, COMPOUND_STATE state, char * name = NULL, PuChannel * playlist = NULL);
/*查找*/
MATRIXDLL_API DuState * FindDustate(char * duid);
MATRIXDLL_API ChannelState * FindChannelState(char * duid, int chno);
MATRIXDLL_API ComPlayState * FindCompoundState(char * duid, int chno, int compoundno);
/*删除所有du状态*/
MATRIXDLL_API void RemoveAllDuState();

/*读写DU状态*/
MATRIXDLL_API void WriteDuState(char * username);
MATRIXDLL_API void ReadDuState(char * filepath);

#endif