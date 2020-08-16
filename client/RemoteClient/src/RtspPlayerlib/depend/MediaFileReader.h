
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MEDIAFILEREADER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MEDIAFILEREADER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MEDIAFILEREADER_EXPORTS
#define MEDIAFILEREADER_API __declspec(dllexport)
#else
#define MEDIAFILEREADER_API __declspec(dllimport)
#endif


typedef void(*MFR_GotFrameCallBack)(int userdata,unsigned char *FrameData,int FrameLen);

MEDIAFILEREADER_API long MFR_Initial();

MEDIAFILEREADER_API void MFR_SetGetFrameCallBack(long handle,MFR_GotFrameCallBack pfunc);

MEDIAFILEREADER_API void MFR_Destory(long handle);

MEDIAFILEREADER_API int MFR_StartPlayFile(long handle,char* filepath, long userdata);

MEDIAFILEREADER_API int MFR_StopPlayFile(long handle, long userdata);