#ifndef RTSPCLIENT_LIB_H_
#define RTSPCLIENT_LIB_H_

//#if defined(_WIN32) || defined(_WIN64)
//#ifdef	 RTSPCLIENTLIB_EXPORTS
//#define   MEDIASERVER_DLL_API   __declspec(dllexport)  
//#else
//#define   MEDIASERVER_DLL_API   __declspec(dllimport)  
//#endif 
//#else
//#define   MEDIASERVER_DLL_API
//#endif

typedef void(*OnPlayerStatusCallBack)( int nStatus);//nStatus 1 ¼ÓÈë 2 ÍË³ö
//start  server
int StartRtspClientLib(char* szRtspUrl,void* hPlayWnd,int nWidht,int nHight,OnPlayerStatusCallBack onUsercb);
//stop   server
int StopClient();
//reconnect
int ReStartRtsp();

#endif

