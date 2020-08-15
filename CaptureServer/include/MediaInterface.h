#pragma once

#include <stdint.h>
#include <Windows.h>

#define MAX_DATA_OBJ_COUNT  ( 64 )

#pragma pack(push, 8)

struct FrameData
{
    uint32_t   time ;
    uint32_t   size ;
    uint8_t *  buffer ;
    void *     context ;
} ;

struct ImageData
{
    //
    // YUV数据
    //
    FrameData   image ;
    
    //
    // 附加数据个数
    //
    uint32_t    count ;
    
    //
    // 附加数据
    //
    FrameData   contexts[MAX_DATA_OBJ_COUNT] ;
} ;

struct NetStatusObj
{
    int16_t      nStatus ; //状态值
    int16_t      nRef  ;
    uint16_t     nSRtt ; // 发送的rtt
    uint16_t     nPRtt ; // 接收端的rtt = 0 说明还没有收到对端的反馈
} ;

#pragma pack(pop)

#ifndef __FRAME__BUFFER__

#define __FRAME__BUFFER__

#pragma pack(push, 1)

struct IFrame420PBuffer
{
    uint8_t *   m_YBuffer ; // y
    uint8_t *   m_UBuffer ; // u
    uint8_t *   m_VBuffer ; // v
    uint32_t    m_YLength ;
    uint32_t    m_ULength ;
    uint32_t    m_VLength ;
    uint32_t    m_UMemSize ;
    uint32_t    m_uPacked  ;
} ;

#pragma pack(pop)
#endif


class IVoiceEvent
{
#define VOICE_ERR_PLAY_DEVICE_START ( 0 )
#define VOICE_ERR_RECORD_DEVICE_START ( 1 )
public:
    virtual void __stdcall OnVoiceDevErrEvent( int nErrType, int nErrCode ) = 0 ;
    
    //
    // 分析线程初始化
    //
    virtual void __stdcall OnVoiceInit() = 0 ;
    
    //
    // 采集数据
    // @pbuffer
    // @usize  40毫秒 16k长度  1280 bytes = 640个采样
    // @utime 时间戳
    //
    virtual void __stdcall OnVoiceDevBufferEvent(const FrameData * pPCMData ) = 0 ;
    virtual void __stdcall OnVoiceClean() = 0 ;
} ;



class IVoiceEngine
{
public:
	virtual void  __stdcall Release() = 0 ;
    
    //
    //  开启该选项，返回pcm数据
    //
#define AUDIO_PARSER_MIC				( 0x0 )
#define AUDIO_PARSER_PCM                ( 0x2 )
#define AUDIO_PARSER_SYS				( 0x1 )


    //
    // @uMode = AUDIO_PARSER_PCM 会启用分析模式
    // 默认开启播放
    //
	virtual int  __stdcall Init( int nVoiceTypeId, IVoiceEvent * pVoiceEvent, uint32_t uMode ) = 0 ;
	virtual void  __stdcall Close() = 0 ;
    
    // bEnable = true 开启播放，= false 关闭播放
	virtual void  __stdcall EnableRecord( bool bEnable , uint32_t uDelay ) = 0 ;
	virtual void  __stdcall EnablePlay(bool bEnable) = 0 ;
    virtual int   __stdcall Mute( bool bEnable ) = 0 ;
} ;




class IMediaClientEvent
{
public:
	//
	// nErrorCode = 0 成功
	// nErrorCode = 1 失败
	//
#define LOGIN_ME_OK			( 0 )
#define LOGIN_ME_FAIL		( 1 )

    //
    // 登录服务器成功
    //
	virtual void  __stdcall LoginEvent( int nErrorCode ) = 0 ;
    
    //
    // 服务器使用后会通知，在通讯过程中会切换
    //
	virtual void  __stdcall MediaServerEvent( int nAddress, int nPort ) = 0 ;
    
#define AUDIO_DATA_TYPE     ( 0 )
#define VIDEO_DATA_TYPE     ( 1 )
    
    //
    // 有用户进来  @nDataType = AUDIO_DATA_TYPE/VIDEO_DATA_TYPE
    //
	virtual void  __stdcall UserEnterEvent( int nUserId , int nDataType ) = 0 ;
    
    //
    // 有用户离开 @nDataType = AUDIO_DATA_TYPE/VIDEO_DATA_TYPE
    //
	virtual void  __stdcall UserLeaveEvent( int nUserId , int nDataType ) = 0 ;
    
    // 网络断开
	virtual void  __stdcall CloseEvent( int nCloseCode ) = 0 ;
    
    //
    // 网络质量回调
    // pNetStatus.nStatus
    
#define NET_STATUS_NORMAL       ( 0 )   // 中等
#define NET_STATUS_EXCELLENCE   ( 1 )   // 很好
#define NET_STATUS_BAD          ( -1 )  // 差
#define NET_STATUS_VERY_BAD     ( -2 )  // 非常差
    
    virtual void  __stdcall NetStatusEvent( NetStatusObj * pNetStatus ) = 0 ;
};

class IMediaClient
{
public:
	virtual void  __stdcall Release() = 0 ;
    
    // @设置端口列表
	virtual void  __stdcall SetPortArray( uint16_t * pNetPortArray, uint32_t uPortCount) = 0 ;
    
    // 设置ip列表
	virtual void  __stdcall SetAddressArray( uint32_t * uAddressArray, uint32_t uAddressCount) =0 ;
    
    //
    // 设置用户信息 @result =0 成功
    //
	virtual int   __stdcall SetUserInfo( uint64_t uRoomID, uint32_t uRoomKey, uint32_t uCID ) = 0 ;
    
    //
    // 登录服务器 @result = 0 成功
    // @uLoginType = MEDIA_SERVER_MODE 是服务器端模式
	//
#define MEDIA_MODE_SERVER		( 0x80000000 )
#define MEDIA_MODE_CLIENT	    ( 0 )

	virtual int   __stdcall EnterServer( uint32_t uLoginType, IMediaClientEvent * pMediaServerEvent ) = 0 ;
    
    //
    // 离开服务器
    //
	virtual int   __stdcall LeaveServer() = 0 ;
    
    //
    // 获取时间戳 和视频 音频时间戳一致
    // @rc = 0 出错，该值不可能等于0
    //
    virtual uint32_t __stdcall GetMediaTime() = 0 ;

	//
	// 增加一个用户登陆key
	// @uTimeOut = 0xffffffff 永久不释放，测试使用
	// 
#define FOR_EVER_TIME		( 0xffffffff )
	virtual int	__stdcall AddClientUserKey( uint32_t uCid , uint32_t uKey , uint32_t uTimeOut ) = 0 ;

	//
	// 删除一个用户对
	//
	virtual int __stdcall RemoveClientUserKey( uint32_t uCid ) = 0 ;
} ;



class IVideoUserEvent
{
public:

	//
	// 初始化 @nwidth @nheight 是视频尺寸
	// 在这个里面初始化 opengl
    //
	virtual int32_t  __stdcall OnVideoInit( int nWidth, int nHeight ) = 0 ;
	
	//
	// 原始接口 在线程里面，方便做深入的整合
	//


//
// 如果 SetZoomImageType = VF_I420
// ImageData->buffer = & IFrame420PBuffer
// 默认是ARGB
// 如果 ImageType = VF_I420 这么使用
// IFrame420PBuffer * pVideoFrame = (IFrame420PBuffer *)(pImageData->image.buffer) ;
// 渲染 pVideoFrame->YBuffer/UBuffer
//
	virtual int32_t  __stdcall OnVideoBuffer(const ImageData * pImageData ) = 0 ;
    
    //
    // 非同步调用，会直接返回消息
    //
    virtual int32_t  __stdcall OnDataBuffer( FrameData * pFrameData, uint32_t uCount ) = 0 ;
    
    //
    // 退出调用
    //
	virtual void     __stdcall OnVideoClean() = 0 ;
};

class IVideoUser
{
public:
    //
    // @bSyncData = 0 不同步附加数据 单独回调 OnDataBuffer 函数
    //            = 1 同步数据 在视频帧回调函数中返回对应的附加数据 默认设置
    //
    //
	virtual void  __stdcall Init( IVideoUserEvent * pVideoUserEvent, uint32_t bSyncData )  = 0 ;
    
#define VF_NV21         ( 1 )
#define VF_NV12         ( 2 )
#define VF_YV12         ( 3 )
#define VF_I420         ( 8 ) // 支持
    
#define VF_RGB565       ( 4 ) // 支持
#define VF_RGB24        ( 5 ) // 目前不支持
#define VF_RGBA         ( 6 ) // 支持
#define VF_RGBX         ( 7 ) // 目前不支持
    
//
//
// 在 SetZoomSize  之前调用
//
//
    virtual void  __stdcall SetZoomImageType(uint32_t uPixType) = 0 ;
    virtual void  __stdcall Close() = 0 ;
	virtual void  __stdcall SetData(void * pData) = 0 ;
	virtual void * __stdcall GetData() = 0 ;
	virtual uint32_t __stdcall GetUserId() = 0 ;
    
    // 获取视频尺寸
	virtual void  __stdcall GetVideoInfo(int * nWidth, int * nHeight, int * nCodecId ) = 0 ;
    
    // 设置缩放大小
    virtual void  __stdcall SetZoomSize(int nWidth, int nHeight ) = 0 ;
    
    //
    // 释放分配的帧缓存区 OnVideoBuffer 回调产生的视频帧
    //
    virtual void __stdcall ReleaseFrameBuffer( FrameData * pFrameData ) = 0 ;
    
    //
    // 当前渲染帧率
    //
    virtual uint32_t __stdcall GetLocalFrameCount() const  = 0 ;
    
    //
    //  下面是从0开始的计数 需要自己减掉上次的值 计算当前值
    //
    virtual uint32_t __stdcall GetErrFrameCount() const = 0 ;     // 解码错误的包计数
    virtual uint32_t __stdcall GetAllFrameCount() const = 0  ;     // 解码成功的包计数
    virtual uint32_t __stdcall GetDropFrameCount() const = 0 ;    // 由于卡顿丢弃的包计数
} ;

class IVideoRenderEvent
{
public:
	virtual void  __stdcall OnCreateVideoUser( IVideoUser * pVideoUser ) = 0 ;
	virtual void  __stdcall OnCloseVideoUser( IVideoUser * pVideoUser ) = 0 ;
	virtual void  __stdcall OnMyVideoBuffer( char * pBuffer , int nSize ) = 0 ;
} ;

	//
	//
	//
#define VIDEO_CAPTURE_INIT_EVENT		( 0x0010 )  // @nEventType 打开
#define VIDEO_CAPTURE_CLEA_EVENT		( 0x0011 )  // @nEventType 关闭
#define VIDEO_CAPTURE_SUCC				( 0x0000 )  // @nErrorCode = 0 成功


/*
 时间戳从登录媒体服务器的tick为0 开始计数
 */
class IVideoEngine
{
public:
	virtual void  __stdcall Release() = 0 ;

	virtual int  __stdcall Init( IVideoRenderEvent * pVideoRenderEvent ) = 0 ;
	virtual int  __stdcall Close() = 0 ;


    //
    // @nwidht nheight 预览尺寸
    // @nzoomwidth nzoomheight 实际编码尺寸
    // @rotate 反转角度 0 90 270
    //
	virtual int  __stdcall SetCaptureInfo( int nWidth, int nHeight , int nZoomWidth, int nZoomHeight,int Rotate ) = 0 ;

	//
	// @nDefFrames =0 def =10
	// @nMaxFrames =0 def =15
	//
	virtual int  __stdcall SetCaptureFrames(int nDefFrames, int nMaxFrames) = 0 ;
    
#define DEF_VIDEO_CODEC_TYPE        ( 0 ) // H264
#define VIDEO_CODEC_TYPE_OPENH264   ( 1 )
#define VIDEO_CODEC_TYPE_X264       ( 2 )
#define VIDEO_CODEC_TYPE_HARD264    ( 3 ) // 硬件编
#define VIDEO_CODEC_TYPE_VP8        ( 4 )
#define VIDEO_CODEC_TYPE_VP9        ( 8 )
#define VIDEO_CODEC_TYPE_HIGH264    ( 16 )
#define VIDEO_CODEC_TYPE_FEC        ( 0x10000000 )
#define VIDEO_CODEC_TYPE_FEC_TAG    ( 0xFFFFFFF )
    
	//
	// @ hWnd  是显示视频预览窗口的句柄
	// @nEncBitRate = 0 
	//
	virtual int  __stdcall StartCaptrueVideo( int nEncBitRate,  HWND hWnd ) = 0 ;
    
    //
    // @result = time 时间戳 4字节 < 该时间戳不会等于0 >
    //         = 0 说明失败，编码线程忙碌，该帧丢失，非0表示成功
    //
    virtual uint32_t  __stdcall ProcessEncodeBuffer( char * pEncBuffer , uint32_t uSize ) = 0 ;
    
	virtual int  __stdcall StopCaptrueVideo() = 0 ;
	virtual int  __stdcall EnablePlayVideo(bool bEnable) = 0 ;
	virtual int  __stdcall ShowVideoConfigWin(int nTop, int nLeft) = 0 ;
    virtual int __stdcall ResetCaptureInfo( int nZoomWidth, int nZoomHeight , int nRotate ) = 0 ;
    
#define MAX_VDATA_SIZE  ( 1260 )
    //
    // utime是时间戳 @ProcessEncodeBuffer 返回值
    // @result = uSize succ...
    //         < 0  fail...
    //
    // 不建议多线程调用，单线程调用
    //
    //
    virtual int32_t __stdcall PostDataBuffer( const void * pBuffer, uint32_t uSize, uint32_t uTime ) = 0 ;
    
    // 获取当前编码帧率
    virtual uint32_t __stdcall GetCaptureFrameCount() = 0 ;
    
    // 获取当前丢帧计数，由于cpu负载太高导致
    virtual uint32_t __stdcall GetLostFrameCount() = 0  ;

	//
	// 发送264编码后数据 GetTickCount() 
	//
	virtual int32_t	__stdcall SendH264Buffer( const void * pBuffer , uint32_t uSize , uint32_t uKeyFrame, uint32_t uTime )  = 0 ;
	virtual int32_t	__stdcall SendH264Buffer2( const void * pBuffer , uint32_t uSize , uint32_t uKeyFrame, uint32_t uTime )  = 0 ;

} ;

class IMediaInterface
{
public:
	virtual void  __stdcall Release() = 0 ;
    
    //
    // pLogDir = NULL  @"/sdcard/AR_Media_Sdk/"
    //
	virtual int  __stdcall Init(const char * pLogDir) = 0 ;
	virtual int  __stdcall Clean() = 0 ;
    
	virtual IMediaClient *  __stdcall CreateMediaClient() = 0 ;
	virtual IVoiceEngine *  __stdcall CreateVoiceEngine() = 0 ;
	virtual IVideoEngine *  __stdcall CreateVideoEngine() = 0 ;
    
    virtual int __stdcall  WriteLog( const char * pszLog, uint32_t uSize ) = 0  ;

};



#ifdef __cplusplus
extern "C"{
#endif
    
    IMediaInterface *  __stdcall CreateMediaEngine() ;
    
#ifdef __cplusplus
} ;
#endif


