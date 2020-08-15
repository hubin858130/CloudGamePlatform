#ifndef MEDIASERVER_LIB_H_
#define MEDIASERVER_LIB_H_

#if defined(_WIN32) || defined(_WIN64)
#ifdef	 MEDIASERVERLIB_EXPORTS
	#define   MEDIASERVER_DLL_API   __declspec(dllexport)  
#else
	#define   MEDIASERVER_DLL_API   __declspec(dllimport)  
#endif 
#else
	#define   MEDIASERVER_DLL_API
#endif

typedef void(*OnUserStatusCallBack)(int nUserNum, int nStatus);//nStatus 1 ¼ÓÈë 2 ÍË³ö
//start  server
int MEDIASERVER_DLL_API StartMediaServer(OnUserStatusCallBack onUsercb);
//stop   server
int MEDIASERVER_DLL_API StopMediaServer();
//send   video buffer
int MEDIASERVER_DLL_API	SendVideoBuffer(char* szBuffer, int nSize, long lTimeS);
//send   audio buffer
int MEDIASERVER_DLL_API	SendAudioBuffer(char* szBuffer, int nSize);

#endif
