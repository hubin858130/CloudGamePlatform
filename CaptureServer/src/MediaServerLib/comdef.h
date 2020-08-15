#pragma once
typedef struct SMediaBufferInfo
{
	char*  szBuffer;
	int    nBufferSize;
	int    nMediatype;
	long   lTimeS;
	SMediaBufferInfo()
	{
		szBuffer = 0;
		nBufferSize = 0;
		nMediatype = 0;//0 video 1 audio
		lTimeS = 0;
	}
	SMediaBufferInfo& operator = (const SMediaBufferInfo& r)
	{
		szBuffer = r.szBuffer;
		nBufferSize = r.nBufferSize;
		nMediatype = r.nMediatype;
		lTimeS = r.lTimeS;
		return *this;
	}
}*PMediaBufferInfo;
