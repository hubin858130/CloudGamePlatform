#include "stdafx.h"
#define KEDA_AUDIO_API  extern "C"__declspec(dllimport)

typedef void (__stdcall *CBF_GetData)(void* pAudioBuf, int nAudioLen);


//////////////导入网络语音数据

KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StartPlay();//打开语音播放；
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StopPlay();
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_InputAudioData(char* pAudioBuf, int nAudioLen);
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_SetAudioVolume(WORD wVolume);



////////////////////////////////////////////////////////////////
//////////////回调语音数据
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StartAudioIn();//打开语音采集；
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_StopAudioIn();
KEDA_AUDIO_API BOOL __stdcall KEDA_AUDIO_SetAudioInCallback(CBF_GetData pCbf);