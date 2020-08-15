#ifndef _NVFBCHWENCODE_H_
#define _NVFBCHWENCODE_H_

typedef void(*OnH264CallBack)( char* szBuffer,int nSize, int nWidth, int nHeight, int nFrameType, void * pUserData);
//Æô¶¯×¥ÆÁ
void StartCapture();
void SetBufferCallback(OnH264CallBack cbH264Data);
void EndCapture();


#endif