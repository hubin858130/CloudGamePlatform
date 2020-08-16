
#ifndef		_T15COMMON_H
#define		_T15COMMON_H


// 解码输出格式
#define	OUT_FMT_YUV_420	 0x00000601
#define OUT_FMT_YUV_422  0x00000102
#define OUT_FMT_RGB_032  0x00000204
#define OUT_FMT_RGB_024  0x00000303
#define OUT_FMT_RGB_565  0x00000402
#define OUT_FMT_RGB_555  0x00000502

#define	OUT_FMT_AUDIO	 0x00000602

#define		ERR_NO_ERROR					0	// 成功
#define		ERR_MEMORY_ALLOC_ERROR			1	// 内存分配失败
#define		ERR_PARAM_INVALID_ERROR			2	// 参数无效
#define		ERR_OPEN_DDRAW_ERROR			3	// 显卡初始化失败
#define		ERR_OPEN_DSOUND_ERROR			4	// 音频初始化失败
#define		ERR_GETFILEINFO_ERROR			5	// 获取文件信息失败
#define		ERR_DECINIT_ERROR				6	// 解码器初始化失败
#define		ERR_INIT_DDRAW_ERROR			7	// 显卡初始化失败
#define		ERR_IFRAME_NOT_FOUND_ERROR		8	// 查找IFrame失败
#define		ERR_OPENFILE_ERROR				9	// 打开文件失败
#define		ERR_OPEN_ALOW_ERROR				10	// 打开ALaw音频失败
#define		ERR_FILE_HEADER_ERROR			11  // 无效的文件头
#define		ERR_DECODER_TYPE_ERROR			12	// 文件/流模式解码已经打开:切换类型时
#define		ERR_DEC_OPENED_ERROR			13	// 解码器已经打开
#define		ERR_DEC_BUSY_ERROR				14	// 解码器忙
#define		ERR_FILE_KEYFRAME				15	// 没有关键帧
#define		ERR_FRAME_HEAD_ERROR			16	// 帧头错误

#define		PLAYING_FILE				0
#define		PLAYING_STREAM				1

#define		STREAM_OPEN_REALTIME		0
#define		STREAM_OPEN_FILE			1




// T15_SetMsgWnd
/*
	lParam中包含通道号
*/
#define MSG_FILE_END_NOTIFICATION		(WM_USER+151)	// 文件播放完成发送
#define MSG_BUFFER_NOTIFICATION			(WM_USER+152)	// 源缓冲区阀值和剩余数据小于等于阀值时发送 wParam: 1
#define	MSG_EXCEPTION_ERROR				(WM_USER+152)	// 异常错误									wParam: 0
#define	MSG_INDEX_OK					(WM_USER+154)	// 索引线程创建结束

#define BY_FRAMENUM				1	//表示帧号
#define BY_FRAMTIME				2	//表示时间，单位ms

typedef struct{
	long nFilePos;		//文件位置；
	long nFrameNum;		//帧序号；
	long nFrameTime;	//帧时标（ms）;
}FRAME_POS,*PFRAME_POS;


typedef struct{
	long nWidth;	//画面宽，单位像素。如果是音频数据则为0；
	long nHeight;	//画面高。如果是音频数据则为；
	long nStamp;	//时标信息，单位毫秒。
	long nType;		//	 
	long nFrameRate;//编码时产生的图像帧率。
}FRAME_INFO;

typedef	struct{
	WORD	wYear;
	WORD	wMonth;
	WORD	wWeek;
	WORD	wDay;
	WORD	wHour;
	WORD	wMinute;
	WORD	wSecond;
	WORD	wMilli;
}_SYSTEM_TIME;

typedef	struct {
		short	year;
		short	month;
		short	day;
		short	hour;
		short	minute;
		short	second;
		short	milli;	
		short	week;
}VIDEO_TIME;
typedef struct 
{
	char YinheID[8];	// :'YINHEBMW'
	DWORD HeadSize;		// :64
	char HeadID[4];		// :0x2008("MP4 ")
	DWORD framerate;	// :n (1/n)
	DWORD VideoStandard;// :0 ntsc;1 pal
	DWORD VideoWidth;	// :
	DWORD VideoHeight;	// :
	DWORD AudioType;	// 0: 无音频, 1: G.729 8k, 2: a-law, 3: g.729a , 4: g.722
	char  reserved[28]; // 1. byte i-frame interval
}HB_FILE_HEAD;

// 文件录像时间
typedef	struct{
	WORD	wYear;
	WORD	wMonth;
	WORD	wWeek;
	WORD	wDay;
	WORD	wHour;
	WORD	wMinute;
	WORD	wSecond;
	WORD	wMilli;

}_RECORD_TIME;






































#endif