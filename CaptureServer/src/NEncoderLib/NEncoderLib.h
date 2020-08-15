#ifndef NENCODER_LIB_H_
#define NENCODER_LIB_H_

#if defined(_WIN32) || defined(_WIN64)
#ifdef	 NENCODERLIB_EXPORTS
#define   NENCODER_DLL_API   __declspec(dllexport)  
#else
#define   NENCODER_DLL_API   __declspec(dllimport)  
#endif 
#else
#define   NENCODER_DLL_API
#endif

#define _FRAME_TYPE_RGB32	0
#define _FRAME_TYPE_RGB24	1
#define _FRAME_TYPE_YUV420  2

typedef void(*OnEncodeStatusCallBack)(int nStatus);//nStatus
typedef void(*OnH264StreamCallback)(char* szBuffer, int nSize, int nWidth, int nHeight, int nFrameType, void * pUserData);
//
int NENCODER_DLL_API InitEncoder(int nWidth,int nHeight,int nBps,OnEncodeStatusCallBack onUsercbi, OnH264StreamCallback h264Cb,void* pUserData);
//
int NENCODER_DLL_API PutFrameBuffer(char* szBuffer, int nSize, int nType=0);
//
int NENCODER_DLL_API PutFrameBuffer(void* pframe);
//
int NENCODER_DLL_API releaseEncoder();

#endif