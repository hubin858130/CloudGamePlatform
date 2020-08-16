/*
 * Copyright	: (C) 2006 santachi corp.
 * Filename	: Hi3510player.h
 * Description	: play header file
 * Created	: liuqingshan<liuqs_santachi@126.com> --- 2006/11/27
 * Modified	:
 */
 
 #ifndef __DECODELIB_H__
 #define __DECODELIB_H__
 
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
 
#define ST_DECODELIB_API

//播放控制
#define PLAY_MODE_NORMAL			0x0001
#define PLAY_MODE_STOP				0x0002
#define PLAY_MODE_PAUSE				0x0003
#define PLAY_MODE_SLOW				0x0004		
#define PLAY_MODE_FAST_FORWARD2		0x0010
#define PLAY_MODE_FAST_FORWARD4		0x0011
#define PLAY_MODE_FAST_FORWARD8		0x0012
#define PLAY_MODE_FAST_FORWARD16	0x0013
#define PLAY_MODE_FAST_FORWARD32	0x0014
#define PLAY_MODE_FAST_BACKWARD2	0x0020
#define PLAY_MODE_FAST_BACKWARD4	0x0021
#define PLAY_MODE_FAST_BACKWARD8	0x0022
#define PLAY_MODE_FAST_BACKWARD16	0x0023
#define PLAY_MODE_FAST_BACKWARD32	0x0024
#define PLAY_MODE_SINGLE_FRAME		0x0030

typedef int (*DUAL_SPEAK_CALLBACK)(int size, const char* data, DWORD dwUser);

//音量
#define VOLUM_MIN	0
#define VOLUM_MAX	65535

//播放类型
#define PLAY_UNKNOW_TYPE     -1    //no file
#define PLAY_LOCALFILE_TYPE  0     //local file
#define PLAY_NETFILE_TYPE    1     //net file
#define PLAY_NETSTREAM_TYPE  2     //net stream

//声音控制类型
#define DST_SPEAKERS		0   //主音量  
#define SRC_WAVEOUT			1   //波形
#define SRC_SYNTHESIZER		2	//软件合成器
#define SRC_COMPACTDISC     3	//CD音量
#define SRC_MICROPHONE		4   //麦克风
 
 ST_DECODELIB_API int st_player_initPlayLib(void);
 ST_DECODELIB_API int st_player_deinitPlayLib(void);
 
 ST_DECODELIB_API unsigned long st_player_createPlayInstance(int dev_type , int play_type); //play_type :0 file, 1 net file, 2 net stream
 ST_DECODELIB_API int st_player_destroyPlayInstance(unsigned long player_id);
 
 ST_DECODELIB_API int st_player_setNetPlayBufNum(unsigned long player_id, int num);
 ST_DECODELIB_API int st_player_setPlayWnd(unsigned long player_id, HWND hwnd);
 ST_DECODELIB_API int st_player_setPlayPicSize(unsigned long player_id, int width, int height);
 ST_DECODELIB_API int st_player_getNetPlayBufNum(unsigned long player_id);
 ST_DECODELIB_API HWND st_player_getPlayWnd(unsigned long player_id);
 ST_DECODELIB_API int st_player_getPlayPicSize(unsigned long player_id, int *width, int *height);
 
 ST_DECODELIB_API int st_player_openPlayFile(unsigned long player_id, char *file_name);
 ST_DECODELIB_API int st_player_closePlayFile(unsigned long player_id);
 ST_DECODELIB_API int st_player_getPlayFileTotalSize(unsigned long player_id);
 ST_DECODELIB_API int st_player_getPlayFileTotalTime(unsigned long player_id);
 ST_DECODELIB_API int st_player_getCurPlayFilePos(unsigned long player_id);
 ST_DECODELIB_API int st_player_setCurPlayFilePos(unsigned long player_id, int pos);
 ST_DECODELIB_API int st_player_getCurPlayedTime(unsigned long player_id);
 ST_DECODELIB_API int st_player_setCurPlayedTime(unsigned long player_id, int len);

ST_DECODELIB_API int st_player_getFrameRate(unsigned long player_id, BOOL bFrame_rate);
ST_DECODELIB_API int st_player_getBitRate(unsigned long player_id, BOOL bBit_rate);
 
 ST_DECODELIB_API int st_player_startPlay(unsigned long player_id);
 ST_DECODELIB_API int st_player_stopPlay(unsigned long player_id);
 ST_DECODELIB_API int st_player_setPlayMode(unsigned long player_id, int play_mode);

 ST_DECODELIB_API int st_player_startlocalrecord(unsigned long player_id, char *recordfile_name);
 ST_DECODELIB_API int st_player_stoplocalrecord(unsigned long player_id);
 
 ST_DECODELIB_API int st_player_inputNetFrame(unsigned long player_id, char *buf, int size);
 ST_DECODELIB_API int st_player_getListFrameNum(unsigned long player_id);

 ST_DECODELIB_API int st_player_openSound(unsigned long player_id);
 ST_DECODELIB_API int st_player_closeSound(unsigned long player_id);
 ST_DECODELIB_API int st_player_setPlayVolume(int volume);
 ST_DECODELIB_API int st_player_getPlayVolume();
 ST_DECODELIB_API int st_player_SetMute(BOOL bMute);
 ST_DECODELIB_API BOOL st_player_GetMute();
 ST_DECODELIB_API int st_player_setMicPlayVolume(int volume);
 ST_DECODELIB_API int st_player_getMicPlayVolume();
 ST_DECODELIB_API int st_player_SetMicMute(BOOL bMute);
 ST_DECODELIB_API BOOL st_player_GetMicMute();
 
 ST_DECODELIB_API int st_player_setOsdString(unsigned long player_id, int index, int pos_x, int pos_y, char *osd_string);
 ST_DECODELIB_API int st_player_removeOsdstring(unsigned long player_id, int index, int pos_x, int pos_y, char *osd_string);
 
 ST_DECODELIB_API int st_player_capturePicture(unsigned long player_id, char *file_name);
 ST_DECODELIB_API int st_player_capturePictureBuf(unsigned long player_id, char *buf);
 
 ST_DECODELIB_API int st_player_getSDKVesion(char *ver_string);
 ST_DECODELIB_API int st_player_getLastError(unsigned long player_id, char *err_string);
 
 ST_DECODELIB_API int st_player_StartDualTalk(unsigned long player_id);
 ST_DECODELIB_API int st_player_StopDualTalk(unsigned long player_id);
 ST_DECODELIB_API int st_player_registerSetDualCallback(unsigned long player_id, DUAL_SPEAK_CALLBACK callback, DWORD dwUser);
 
 ST_DECODELIB_API int st_player_getCurrentFrameNo(unsigned long player_id); 
 ST_DECODELIB_API int st_player_adjustViewArea(unsigned long player_id, int left, int right, int top, int bottom);
 
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __PLAYER_H__ */
 