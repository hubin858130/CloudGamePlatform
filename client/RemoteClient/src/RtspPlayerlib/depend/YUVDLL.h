#ifndef _YUVDLL_H_
#define	_YUVDLL_H_

#define FILTER_INTERFACE_EXPORTS

#ifdef FILTER_INTERFACE_EXPORTS
#define FILTER_INTERFACE_API __declspec(dllexport)
#else
#define FILTER_INTERFACE_API __declspec(dllimport)
#endif

#define FILTER_OK		0
#define FILTER_ERR		-1
#define FILTER_INERR	-2

#define FILTER_EMPTY	-1

#define MAX_FILTER_NUM	32

FILTER_INTERFACE_API void InitYUVFilter();
FILTER_INTERFACE_API void ReleaseYUVFilter();
FILTER_INTERFACE_API int OpenYUVFilter(/*HWND*/void* inWindow,int width, int height);
FILTER_INTERFACE_API int CloseYUVFilter(int idx);
FILTER_INTERFACE_API int RePaintYUVFilter(int idx);
FILTER_INTERFACE_API int StartYUVFilter(int idx);
FILTER_INTERFACE_API int PauseYUVFilter(int idx);
FILTER_INTERFACE_API int StopYUVFilter(int idx);
FILTER_INTERFACE_API int InputDataToYUVFilter(int idx, char *buf, int buflen);

#endif //_YUVDLL_H_