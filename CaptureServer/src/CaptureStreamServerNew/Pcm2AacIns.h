#pragma once
class CPcm2AacIns
{
public:
	CPcm2AacIns();
	~CPcm2AacIns();

	int InitParams(int nPcmParams, int nChannels, int nBitType, int nAacParams);
	int SetPcmBuffer(char* szPcmBuffer, int nPcmSize, unsigned char*& szAacData, int& nAacSize);
	int StopPcmEncode();

};

