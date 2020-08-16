
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the QUERYDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// QUERYDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef _QUERYDLL_H
#define _QUERYDLL_H

#include "fhncucommon.h"
#define QUERY_ERROR_SENDMSG    10001
enum EreturnType
{
	REC_FILE_QUERY_RESP = 1,   
	REC_FILE_QUERY_XML_RESP,
		
	REC_FILE_STARTVOD_RESP,      //start vod 信令回应
	REC_FILE_STOPVOD_RESP,       

	REC_FILE_VOD_RTSP_RESP,      //回放rtsp回应

	REC_FILE_DOWNLOAD_RESP,      //下载信令回应
	REC_FILE_DOWNLOAD_OVER,      //下载完毕
	REC_FILE_STOP_DOWNLOAD_RESP,

	REC_FILE_DELETE_RESP,
	REC_FILE_MSG_SEND_ERROR,

	LOC_FILE_PLAY_RESP,			//本地回放回应
};

enum Etranstype
{
	TTYPE_TCP = 1,  //SOCK_STREAM
	TTYPE_UDP,   //SOCK_DGRAM
};


typedef struct S_RecFileInfo
{
	char FileName[256];
	int ChannelNO;
	char PUID[64];
	int FileSize;
	int FileType;
	unsigned __int64 StartTime;
	unsigned __int64 EndTime;
	char RtspUrl[512];
	int StoreType;	
}S_RecFileInfo;

typedef struct S_RecAlarmInfo
{
	int ChannelNO;
	char PUID[64];
	char AlarmID[33];
	int StoreType;
}S_RecAlarmInfo;


typedef struct fileList{
	fileList	*next;
	S_RecFileInfo	*obj;
}fileList;

typedef struct S_RTSPInfo
{
	int rtspret;       //rtsp 回应结果
	rtsp_reply_type rtpye;
	unsigned  fileTime;

}S_RTSPInfo;

typedef struct S_LocFile
{
	loc_file_reply_type rtype;
	unsigned totalTime;
}S_LocFile;

typedef struct S_RecFiles
{
	EreturnType  rType;
	int  RecResult;
	int	 FilesCount;
//if play request then return RTST://serveraddress/filename/customerid; 
	char  RecFileUrl[512];  
	fileList		*filesList;
	S_RTSPInfo *  rtspInfo;
	S_LocFile * locaFileInfo;
}S_RecFiles;


typedef struct S_PlayInfo
{
	Etranstype PlayTransType;
	long hplayWnd;
	int vidoeIndex;
	int reserve;   //用于存放开始播放的时间点
	char userid[32];
}S_PlayInfo;


#ifdef QUERYDLL_EXPORTS
#define QUERYDLL_API __declspec(dllexport)
#else
#define QUERYDLL_API __declspec(dllimport)
#endif

// This class is exported from the QueryDll.dll
/*
class QUERYDLL_API CQueryDll {
public:
	CQueryDll(void);
	// TODO: add your methods here.
};
*/


extern QUERYDLL_API int nQueryDll;

typedef int (*Recprocesscallback)(S_RecFiles * recFiles, long qCallid, long userdata, long reserve);


QUERYDLL_API long InitialRecQuery(Recprocesscallback QueryCallBack , int VersionType, int family);
QUERYDLL_API int UninitialRecQuery(long recQueryHandle);
QUERYDLL_API void SetQueryParameter(long recQueryHandle,char QSessionID[64], char QSourceID[64], char QDestinationID[64], char QToIP[32], UINT QPort);

QUERYDLL_API long QueryFiles(long recQueryHandle,unsigned int QChannelType, S_RecFileInfo *RFileInfo, int QStartNum, int QQueryNum,long userdata);
QUERYDLL_API long QueryFilesXml(long recQueryHandle,unsigned int QChannelType, S_RecFileInfo *RFileInfo, int QRecvNum, int QQueryNum,long userdata);
QUERYDLL_API long QueryAlarmFiles(long recQueryHandle,unsigned int QChannelType, S_RecAlarmInfo *RAlarmInfo,long userdata);

//return a handle of the play file message
QUERYDLL_API long RecPlayFile(long recQueryHandle,unsigned int ChannelType, S_RecFileInfo *RFileInfo, S_PlayInfo * RFilePlayInfo, long userdata);
QUERYDLL_API int RecStopPlayFile(long recQueryHandle,long recHandle,long userdata);

//return a handle of the down file message
QUERYDLL_API long RecDownFile(long recQueryHandle,unsigned int ChannelType, S_RecFileInfo *RFileInfo, S_PlayInfo * RFilePlayInfo,char * downFilename,long userdata,int dlSpeed); 
QUERYDLL_API int RecStopDownFile(long recQueryHandle,long recHandle,long userdata);

QUERYDLL_API long RecDelFile(long recQueryHandle,unsigned int ChannelType, S_RecFileInfo *RFileInfo,long userdata);

QUERYDLL_API int  RecPlayGetPosition (long recQueryHandle,long rechandle, long userdata, long *pPosition);
QUERYDLL_API int RecPlayPlayOperate(long recQueryHandle,long rechandle,ePlayOption operate, long reserve);

QUERYDLL_API unsigned int RecPlayGetCutTS(long recQueryHandle,long rechandle, long userdata);
QUERYDLL_API RecPlayGrabPic (long recQueryHandle,long rechandle, long userdata, char* filename, long picType);

QUERYDLL_API int RecGetFrameRate(long recQueryHandle,long rechandle, long userdata);
QUERYDLL_API float RecGetFlux(long recQueryHandle,long rechandle, long userdata);
QUERYDLL_API BOOL Rec_RefreshSurface(long recQueryHandle,long rechandle, long userdata);

QUERYDLL_API void RecGetDownloadLocPath(long recQueryHandle,long recHandle, LocalMedia_FileInfo *temp);

//获取本地文件的厂家类型
QUERYDLL_API enumCoFileType RecGetLocalManufType(long recQueryHandle,long rechandle, long userdata);
#endif