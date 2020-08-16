#ifndef AUDIOPLAYINTERFACE_H
#define AUDIOPLAYINTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AUDIOPLAY_INTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AUDIOPLAY_INTERFACE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef AUDIOPLAY_INTERFACE_EXPORTS
#define AUDIOPLAY_INTERFACE_API __declspec(dllexport)
#else
#define AUDIOPLAY_INTERFACE_API __declspec(dllimport)
#endif

#include <mmsystem.h>


typedef void(*AudioSend)(int userdata,unsigned char *AudioData,int AudioLen);

/*下面是WINDOWS音频函数返回值定义*/
#define MMSYSERR_NOERROR      0                    /* no error */
#define MMSYSERR_NODEVICE     -1
#define MMSYSERR_DEVICEALREADYOPEN -2
#define MMSYSERR_BASE          0
#define MMSYSERR_ERROR        (MMSYSERR_BASE + 1)  /* unspecified error */
#define MMSYSERR_BADDEVICEID  (MMSYSERR_BASE + 2)  /* device ID out of range */
#define MMSYSERR_NOTENABLED   (MMSYSERR_BASE + 3)  /* driver failed enable */
#define MMSYSERR_ALLOCATED    (MMSYSERR_BASE + 4)  /* device already allocated */
#define MMSYSERR_INVALHANDLE  (MMSYSERR_BASE + 5)  /* device handle is invalid */
#define MMSYSERR_NODRIVER     (MMSYSERR_BASE + 6)  /* no device driver present */
#define MMSYSERR_NOMEM        (MMSYSERR_BASE + 7)  /* memory allocation error */
#define MMSYSERR_NOTSUPPORTED (MMSYSERR_BASE + 8)  /* function isn't supported */
#define MMSYSERR_BADERRNUM    (MMSYSERR_BASE + 9)  /* error value out of range */
#define MMSYSERR_INVALFLAG    (MMSYSERR_BASE + 10) /* invalid flag passed */
#define MMSYSERR_INVALPARAM   (MMSYSERR_BASE + 11) /* invalid parameter passed */
#define MMSYSERR_HANDLEBUSY   (MMSYSERR_BASE + 12) /* handle being used */
						   /* simultaneously on another */
						   /* thread (eg callback) */
#define MMSYSERR_INVALIDALIAS (MMSYSERR_BASE + 13) /* specified alias not found */
#define MMSYSERR_BADDB        (MMSYSERR_BASE + 14) /* bad registry database */
#define MMSYSERR_KEYNOTFOUND  (MMSYSERR_BASE + 15) /* registry key not found */
#define MMSYSERR_READERROR    (MMSYSERR_BASE + 16) /* registry read error */
#define MMSYSERR_WRITEERROR   (MMSYSERR_BASE + 17) /* registry write error */
#define MMSYSERR_DELETEERROR  (MMSYSERR_BASE + 18) /* registry delete error */
#define MMSYSERR_VALNOTFOUND  (MMSYSERR_BASE + 19) /* registry value not found */
#define MMSYSERR_NODRIVERCB   (MMSYSERR_BASE + 20) /* driver does not call DriverCallback */
#define MMSYSERR_LASTERROR    (MMSYSERR_BASE + 20) /* last error in range */

#define AUDIOERROR_DEVICENOTIOEN    101         /*设备未打开*/

/*#define AUDIOERROR_NOPLAYDEV       101                  无音频播放设备*/
/*#define AUDIOERROR_NORECORDDEV     102                  无音频采集设备*/
enum AUDIOFORMAT
{
	AR_ADPCM2C16B8000,  /*ADPCM 2channels 16bits 8000samples*/
	AR_ADPCM2C16B22050, /*ADPCM 2channels 16bits 22050samples*/
	AR_PCM1C16B8000,    /*PCM 1channels 16bits 8000samples*/
	AR_PCM1C8B8000, /*PCM 1channels 8bits 8000samples*/
	AR_G711,             /*g711 use 1channels 16bits 8000samples*/
	AR_PCM2C16B22050,/* PCM 2channels 16bits 22050samples*/
	AR_PCM2C16B8000,
	AR_UNKNOWN
};

AUDIOPLAY_INTERFACE_API int Audio_Initial();
AUDIOPLAY_INTERFACE_API int Audio_Destroy();


/*function:获取播放声音大小
 author:   雷玲玲
 process:  获取声音播放大小
 return:  0 ~100 */
AUDIOPLAY_INTERFACE_API int Audio_GetCurVol();


/*function:设置播放声音大小
 author:   雷玲玲
 process:  设置声音播放大小，volvalue: 0～100
 return:  0 成功 */
AUDIOPLAY_INTERFACE_API int Audio_SetPlayVolume(int volvalue);


/*function:音频采集初始化
 author:   雷玲玲
 process:  设置音频采集后的回调函数
 return:  0 */
AUDIOPLAY_INTERFACE_API int Audio_RecordInitex(AudioSend RTPSend);


/*function: 按照指定格式开始音频采集
 author:   雷玲玲
 process:  
 return:   100: 音频库不支持指定的格式
           < 0: 找不到录音设备或硬件不支持指定的格式*/
AUDIOPLAY_INTERFACE_API int Audio_StartRecordex(AUDIOFORMAT arformat);


/*function: 停止音频采集
 author:   雷玲玲
 process:  
 return:   0*/
AUDIOPLAY_INTERFACE_API int Audio_StopRecordex();



/*function:开始播放指定格式的音频数据
 author: 雷玲玲
 return:  0 成功 else:系统不支持声音播放
          handle: 播放句柄*/
AUDIOPLAY_INTERFACE_API int Audio_StartPlayEx(AUDIOFORMAT apformat, int* handle);


/*function:输入音频数据播放
 author: 雷玲玲
 return:  0 成功 */
AUDIOPLAY_INTERFACE_API int Audio_InputAudioData(short *DataBuff,int DataLen);

/*function:停止播放
 author: 雷玲玲
 return:  0 成功 */
AUDIOPLAY_INTERFACE_API int Audio_StopPlayEx(int handle);

/*function: 获取当前的版本号
 author:   雷玲玲
 process:  
 return:   */
AUDIOPLAY_INTERFACE_API int GetVisionNum();

/*function:音频播放初始化
 author: 雷玲玲
 return:  0 成功 else:系统不支持声音播放*/
//AUDIOPLAY_INTERFACE_API int Audio_PlayInit();


//AUDIOPLAY_INTERFACE_API int Audio_SetPlayWaveFormat(WAVEFORMATEX audio_info);


/*function: no use
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API void Audio_SetRecParam(int RtpId);


/*function: no use
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API void Audio_SetParam(void *record_cwnd,WAVEFORMATEX audio_info);

/*function: 打开音频播放设备
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API int Audio_PlayOpen();


/*function: 播放音频数据
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API int Audio_PlayStart(short *DataBuff,int DataLen);

/*function: 暂停播放音频数据
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API int Audio_PlayStop();


/*function: 关闭音频播放设备
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API int Audio_PlayClose();


/*function: 关闭音频播放和采集设备
 author:   雷玲玲
 process:  
 return:   */
//AUDIOPLAY_INTERFACE_API int Audio_Close();




#ifdef __cplusplus
}
#endif

#endif