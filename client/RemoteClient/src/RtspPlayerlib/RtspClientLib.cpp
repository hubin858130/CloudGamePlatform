#include "stdafx.h"
#include "RtspClientLib.h"
#include "RtspPlayer.h"

//start  server
int StartRtspClientLib(char* szRtspUrl, void* hPlayWnd,int nWidht,int nHight, OnPlayerStatusCallBack onUsercb)
{
	int nRet = 0;
	nRet = doWinMain((HWND)hPlayWnd, szRtspUrl, nWidht, nHight, onUsercb);
	return nRet; 
}

//stop   server
int StopClient()
{
	int nRet = 0;
	closeDoMain();
	return nRet;
}