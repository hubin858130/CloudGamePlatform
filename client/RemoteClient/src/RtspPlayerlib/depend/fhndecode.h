
#if !defined (FHNDECODE_HLLL)
#define FHNDECODE_HLLL
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNDECODE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNDECODE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNDECODE_EXPORTS
#define FHNDECODE_API __declspec(dllexport)
#else
#define FHNDECODE_API __declspec(dllimport)
#endif


enum enummediadectype
{
	VT_MPEG4 = 1,
	VT_H264 = 2,
	AT_G711,
	AT_PCM1C16B8000,
	AT_PCM1C8B8000,
	AT_ADPCM2C16B8000,
	VT_Hik, /*º£¿µÊÓÆµ*/
	VT_LC, /*ÀÊ³ÛÊÓÆµ*/
	AT_LC, /*ÀÊ³ÛÒôÆµ*/
	VT_DH, /*´ó»ªÊÓÆµ*/

};

#define FHNDEC_PICTYPE_BMP   1
#define FHNDEC_PICTYPE_JPB   2
#define FHNDEC_PICTYPE_YUV420  3
#define FHNDEC_PICTYPE_BGR24   4

typedef int (*encodeaudiocallback)(long dechandle,long receivehandle, 
								 char*audiodata, int length, int mt);
typedef int (*DecPictureCallback)(long dechandle, char* picbuf, int width, int height, int pictype, long userdata);
/************************************************************************
function:fhndec_initial
author: lllei 20080319
param: initial
process: initial the yuv filter
return: 
************************************************************************/
FHNDECODE_API void fhndec_initial();
/************************************************************************
function:fhndec_createdecode
author: lllei 20080318
param: create a decode
process: create a media decode
return: 0:success; else:error
        phandle: the media decode handle
************************************************************************/
FHNDECODE_API int fhndec_createdecode(long* phandle, enummediadectype meidatype,
									  long userdata, BOOL boverlay = FALSE, COLORREF clrkey = 0);

/************************************************************************
function:fhndec_inputvideodata
author: lllei 20080312
param: handle: the decode handle
       pdata: the pointer to the media data
	   length: the media data length
process: decode the data
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_inputvideodata(long handle, void* pdata, int length, int ts);

/************************************************************************
function:fhndec_startaudioplay
author: lllei 20080312
param: handle: the decode handle
process: startaudioplay
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_startaudioplay(long handle);

/************************************************************************
function:fhndec_stopaudioplay
author: lllei 20080312
param: handle: the decode handle
process: stopaudioplay
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_stopaudioplay(long handle);

/************************************************************************
function:fhndec_inputaudiodata
author: lllei 20080312
param: handle: the decode handle
       pdata: the pointer to the media data
	   length: the media data length
process: decode the data
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_inputaudiodata(long handle, void* pdata, int length, int ts);
/************************************************************************
function:fhndec_startaudiogather
author: lllei 20080312
param: handle: the decode handle
       receivehandle: the handle want to recieve audio
	                  the receivehandle in encodeaudiocallback
		paghandle: the audio gather handle
process: startaudioplay
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_startaudiogather(enummediadectype at,long receivehandle,
										   long/*out*/* paghandle);

/************************************************************************
function:fhndec_startaudiogather
author: lllei 20080312
param: aghandle: the audiogather handle
       receivehandle: 
process: startaudiogather
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_stopaudiogather(long aghandle, long receivehandle);

/************************************************************************
function:fhndec_setplaywnd
author: lllei 20080318
param: handle: the decode handle
       hwnd:the video play wnd
process: set the video play wnd
return: null
************************************************************************/
FHNDECODE_API void fhndec_setplaywndex(long handle, long hwnd, int bshow = 1);
FHNDECODE_API void fhndec_setplaywnd(long handle, long hwnd);

/************************************************************************
function:fhndec_cappicture
author: lllei 20080318
param: handle: the decode handle
       filepath: picture filepath
process: cap picture
return: 0:success  else:error
************************************************************************/
FHNDECODE_API int fhndec_cappicture(long handle, char* filepath);

/************************************************************************
function:fhndec_startrecord
author: lllei 20080318
param: handle: the decode handle
       filepath: record filepath
process: start record
return: 0:success  else:error
************************************************************************/
FHNDECODE_API int fhndec_startrecord(long handle, char* filepath);

/************************************************************************
function:fhndec_stoprecord
author: lllei 20080318
param: handle: the decode handle
process: stop record
return: 0:success  else:error
************************************************************************/
FHNDECODE_API int fhndec_stoprecord(long handle);

/************************************************************************
function:fhndec_setmaxframenum
author: lllei 20080318
param: handle: the decode handle
       maxnum: max frame num in buf, when frame count > maxnum, then discard
process: set the max frame num in buf
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_setmaxframenum(long handle, int maxnum);

/************************************************************************
function:fhndec_closedecode
author: lllei 20080318
param: handle: the decode handle
process: close the decode
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_closedecode(long handle);

/************************************************************************
function:fhndec_getpicturesize
author: lllei 20080513
param: handle: the decode handle
process: get picture size
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_getpicturesize(long handle, int/*out*/*width, int/*out*/*height);

/************************************************************************
function:fhndec_setaudiogathercallback
author: lllei 20080513
param: cbfun: callback function
process: set callback function when gather audio data
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_setaudiogathercallback(encodeaudiocallback cbfun);

/************************************************************************
function:fhndec_setPicTureCallback
author: lllei 20080513
param: picturefun: callback function
process: decode a picture will call this callbackfuntion
return: 0:success; else:error
************************************************************************/
FHNDECODE_API int fhndec_setPictureCallback(DecPictureCallback picturefun);


FHNDECODE_API void fhndec_SetTimeScale(long handle, UINT timescale);

FHNDECODE_API void fhndec_EnableFrameControl(long handle, BOOL enable);

FHNDECODE_API BOOL fhndec_RefreshSurface(long handle);

FHNDECODE_API void fhndec_Destory();

#endif