#ifndef _WinCaptureLib_H_
#define _WinCaptureLib_H_

#if defined(_WIN32) || defined(_WIN64)
#ifdef	 WINCAPTUREANDENCODELIB_EXPORTS
#define   WINCAPTURE_DLL_API   __declspec(dllexport)  
#else
#define   WINCAPTURE_DLL_API   __declspec(dllimport)  
#endif 
#else
#define   WINCAPTURE_DLL_API
#endif

typedef void(*OnH264CallBack)( char* szBuffer,int nSize, int nWidth, int nHeight, int nFrameType, void * pUserData);
typedef void(*OnMouseCallBack)(char* szBuffer, int nSize);
//Æô¶¯×¥ÆÁ
void	WINCAPTURE_DLL_API StartCapture(int nWidth,int nHeight,int nBps,int nFps);
void	WINCAPTURE_DLL_API SetBufferCallback(OnH264CallBack cbH264Data,OnMouseCallBack cbMouseCallback);
void	WINCAPTURE_DLL_API SetCursorStatus(bool bShow);
void	WINCAPTURE_DLL_API EndCapture();


#endif