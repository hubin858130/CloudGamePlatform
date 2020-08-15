#include "stdafx.h"
#include "Pcm2AacIns.h"

#include "AudioCapture/faac.h"
#pragma comment(lib, ".\\AudioCapture\\libfaac_dll.lib")

faacEncHandle   hEncoder = { 0 };
unsigned int    nPCMBitSize = 16;//送进来的pcm 如果是float32 需要由 float32转换为 short16
unsigned char*   pbAACBuffer = NULL;
unsigned long   nMaxOutputBytes = 0;
bool            bInited = false;

CPcm2AacIns::CPcm2AacIns()
{
}


CPcm2AacIns::~CPcm2AacIns()
{
}

int CPcm2AacIns::InitParams(int nPcmParams, int nChannels, int nBitType, int nAacParams)
{
	unsigned long   nSampleRate = nPcmParams;
	
	unsigned long   nInputSamples = 0;
	
	

	//打开faac编码器引擎
	hEncoder = faacEncOpen(nSampleRate, nChannels, &nInputSamples, &nMaxOutputBytes);


	printf("single input:[%d], single output:[%d]\n", nInputSamples, nMaxOutputBytes);
	if (hEncoder == NULL)
	{
		printf("打开faac编码器引擎失败!\n");
		return -1;
	}

	// 分配内存信息  
	int  nPCMBufferSize = nInputSamples*nPCMBitSize / 8;

	pbAACBuffer = new unsigned char[nMaxOutputBytes];

	// 获取当前编码器信息  -- 不能缺少，只有获取以后才可以Set
	faacEncConfigurationPtr pConfiguration = { 0 };
	pConfiguration = faacEncGetCurrentConfiguration(hEncoder);

	// 设置编码配置信息  
	/*
	PCM Sample Input Format
	0   FAAC_INPUT_NULL         invalid, signifies a misconfigured config
	1   FAAC_INPUT_16BIT        native endian 16bit
	2   FAAC_INPUT_24BIT        native endian 24bit in 24 bits      (not implemented)
	3   FAAC_INPUT_32BIT        native endian 24bit in 32 bits      (DEFAULT)
	4   FAAC_INPUT_FLOAT        32bit floating point
	*/
	pConfiguration->inputFormat = FAAC_INPUT_16BIT;

	// AAC object types   
	//#define MAIN 1  
	//#define LOW  2  
	//#define SSR  3  
	//#define LTP  4  
	pConfiguration->aacObjectType = LOW;

	pConfiguration->bitRate = nAacParams;    // or 0
	pConfiguration->bandWidth = 32000;  //or 0 or 32000

	/*下面可以选择设置*/
	pConfiguration->allowMidside = 1;
	pConfiguration->useLfe = 0;
	pConfiguration->useTns = 0;
	pConfiguration->quantqual = 100;
	//outputformat 0 = Raw; 1 = ADTS  
	pConfiguration->outputFormat = 1;
	pConfiguration->shortctl = SHORTCTL_NORMAL;

	// 重置编码器的配置信息  
	int n = faacEncSetConfiguration(hEncoder, pConfiguration);

	bInited = true;

	return 0;
}

int CPcm2AacIns::SetPcmBuffer(char* szPcmBuffer, int nPcmSize, unsigned char*& szAacData, int& nAacSize)
{
	if (bInited)
	{
		int nInputSamples = nPcmSize / (nPCMBitSize / 8);

		// 编码  
		int nRet = faacEncEncode(hEncoder, (int*)szPcmBuffer, nInputSamples, pbAACBuffer, nMaxOutputBytes);
		szAacData = pbAACBuffer;
		nAacSize = nRet;
	}
	return 0;
}

int CPcm2AacIns::StopPcmEncode()
{
	bInited = false;
	// 扫尾工作  
	if (pbAACBuffer != NULL)
	{
		delete[] pbAACBuffer;
		pbAACBuffer = NULL;
	}
	faacEncClose(hEncoder);
	return 0;
}