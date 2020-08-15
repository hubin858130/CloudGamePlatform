/*
* Copyright 2017-2018 NVIDIA Corporation.  All rights reserved.
*
* Please refer to the NVIDIA end user license agreement (EULA) associated
* with this source code for terms and conditions that govern your use of
* this software. Any use, reproduction, disclosure, or distribution of
* this software and related documentation outside the terms of the EULA
* is strictly prohibited.
*
*/

#include <d3d11.h>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <wrl.h>
#include "NvEncoder/NvEncoderD3D11.h"
#include "./Utils/Logger.h"
#include "./Utils/NvCodecUtils.h"
#include "./Utils/AppEncUtils.h"
#include "Timer.h"
#include "NEncoderLib.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

using Microsoft::WRL::ComPtr;

NvEncoderD3D11*  g_pEncD3d11 = NULL;
ComPtr<ID3D11DeviceContext> pContext;
ComPtr<ID3D11Texture2D> pTexSysMem;
int			g_nWidth = 0;
int			g_nHeight = 0;

OnEncodeStatusCallBack		g_pOnEncStatuscbi = NULL;
OnH264StreamCallback		g_pH264Cb = NULL;

FILE*		fpOut = NULL;

simplelogger::Logger *logger = simplelogger::LoggerFactory::CreateConsoleLogger();

class RGBToNV12ConverterD3D11 {
public:
    RGBToNV12ConverterD3D11(ID3D11Device *pDevice, ID3D11DeviceContext *pContext, int nWidth, int nHeight)
        : pD3D11Device(pDevice), pD3D11Context(pContext)
    {
        pD3D11Device->AddRef();
        pD3D11Context->AddRef();

        pTexBgra = NULL;
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
        desc.Width = nWidth;
        desc.Height = nHeight;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_RENDER_TARGET;
        desc.CPUAccessFlags = 0;
        ck(pDevice->CreateTexture2D(&desc, NULL, &pTexBgra));

        ck(pDevice->QueryInterface(__uuidof(ID3D11VideoDevice), (void **)&pVideoDevice));
        ck(pContext->QueryInterface(__uuidof(ID3D11VideoContext), (void **)&pVideoContext));

        D3D11_VIDEO_PROCESSOR_CONTENT_DESC contentDesc = 
        {
            D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE,
            { 1, 1 }, desc.Width, desc.Height,
            { 1, 1 }, desc.Width, desc.Height,
            D3D11_VIDEO_USAGE_PLAYBACK_NORMAL
        };
        ck(pVideoDevice->CreateVideoProcessorEnumerator(&contentDesc, &pVideoProcessorEnumerator));

        ck(pVideoDevice->CreateVideoProcessor(pVideoProcessorEnumerator, 0, &pVideoProcessor));
        D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC inputViewDesc = { 0, D3D11_VPIV_DIMENSION_TEXTURE2D, { 0, 0 } };
        ck(pVideoDevice->CreateVideoProcessorInputView(pTexBgra, pVideoProcessorEnumerator, &inputViewDesc, &pInputView));
    }

    ~RGBToNV12ConverterD3D11()
    {
        for (auto& it : outputViewMap)
        {
            ID3D11VideoProcessorOutputView* pOutputView = it.second;
            pOutputView->Release();
        }

        pInputView->Release();
        pVideoProcessorEnumerator->Release();
        pVideoProcessor->Release();
        pVideoContext->Release();
        pVideoDevice->Release();
        pTexBgra->Release();
        pD3D11Context->Release();
        pD3D11Device->Release();
    }
    void ConvertRGBToNV12(ID3D11Texture2D*pRGBSrcTexture, ID3D11Texture2D* pDestTexture)
    {
        pD3D11Context->CopyResource(pTexBgra, pRGBSrcTexture);
        ID3D11VideoProcessorOutputView* pOutputView = nullptr;
        auto it = outputViewMap.find(pDestTexture);
        if (it == outputViewMap.end())
        {
            D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC outputViewDesc = { D3D11_VPOV_DIMENSION_TEXTURE2D };
            ck(pVideoDevice->CreateVideoProcessorOutputView(pDestTexture, pVideoProcessorEnumerator, &outputViewDesc, &pOutputView));
            outputViewMap.insert({ pDestTexture, pOutputView });
        }
        else
        {
            pOutputView = it->second;
        }

        D3D11_VIDEO_PROCESSOR_STREAM stream = { TRUE, 0, 0, 0, 0, NULL, pInputView, NULL };
        ck(pVideoContext->VideoProcessorBlt(pVideoProcessor, pOutputView, 0, 1, &stream));
        return;
    }

private:
    ID3D11Device *pD3D11Device = NULL;
    ID3D11DeviceContext *pD3D11Context = NULL;
    ID3D11VideoDevice *pVideoDevice = NULL;
    ID3D11VideoContext *pVideoContext = NULL;
    ID3D11VideoProcessor *pVideoProcessor = NULL;
    ID3D11VideoProcessorInputView *pInputView = NULL;
    ID3D11VideoProcessorOutputView *pOutputView = NULL;
    ID3D11Texture2D *pTexBgra = NULL;
    ID3D11VideoProcessorEnumerator *pVideoProcessorEnumerator = nullptr;
    std::unordered_map<ID3D11Texture2D*, ID3D11VideoProcessorOutputView*> outputViewMap;
};

void InitEncode(char *szBgraFilePath, int nWidth, int nHeight, int nBps, char *szOutFilePath, NvEncoderInitParam *pEncodeCLIOptions, int iGpu, bool bForceNv12)
{
    ComPtr<ID3D11Device> pDevice;
    ComPtr<IDXGIFactory1> pFactory;
    ComPtr<IDXGIAdapter> pAdapter;	
    
//	fopen_s(&fpOut, szOutFilePath, "ab+");
	g_nWidth = nWidth;
	g_nHeight = nHeight;
    ck(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)pFactory.GetAddressOf()));

	for (int n = 0; n < 5; n++)
	{
		iGpu = n;
		ck(pFactory->EnumAdapters(iGpu, pAdapter.GetAddressOf()));
		ck(D3D11CreateDevice(pAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, 0,
			NULL, 0, D3D11_SDK_VERSION, pDevice.GetAddressOf(), NULL, pContext.GetAddressOf()));
		DXGI_ADAPTER_DESC adapterDesc;
		pAdapter->GetDesc(&adapterDesc);
		char szDesc[80];
		wcstombs(szDesc, adapterDesc.Description, sizeof(szDesc));
		std::cout << "GPU in use: " << szDesc << std::endl;
		std::string strGpu(szDesc);
		int nPos = strGpu.find("NVIDIA");
		if ( nPos>= 0)
		{
			std::cout << "nv is found!" << std::endl;
			break;
		}
	}
    

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
    desc.Width = nWidth;
    desc.Height = nHeight;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    ck(pDevice->CreateTexture2D(&desc, NULL, pTexSysMem.GetAddressOf()));

    std::unique_ptr<RGBToNV12ConverterD3D11> pConverter;
    if (bForceNv12)
    {
        pConverter.reset(new RGBToNV12ConverterD3D11(pDevice.Get(), pContext.Get(), nWidth, nHeight));
    }

 //   NvEncoderD3D11 enc(pDevice.Get(), nWidth, nHeight, bForceNv12 ? NV_ENC_BUFFER_FORMAT_NV12 : NV_ENC_BUFFER_FORMAT_ARGB);
	if (g_pEncD3d11 == NULL)
	{
		g_pEncD3d11 = new NvEncoderD3D11(pDevice.Get(), nWidth, nHeight, bForceNv12 ? NV_ENC_BUFFER_FORMAT_NV12 : NV_ENC_BUFFER_FORMAT_ARGB);
	}

    NV_ENC_INITIALIZE_PARAMS initializeParams = { NV_ENC_INITIALIZE_PARAMS_VER };
    NV_ENC_CONFIG encodeConfig = { NV_ENC_CONFIG_VER };
    initializeParams.encodeConfig = &encodeConfig;
	GUID  m_stEncodeGUID = NV_ENC_CODEC_H264_GUID;
	GUID m_stCodecProfileGUID = NV_ENC_H264_PROFILE_BASELINE_GUID;// NV_ENC_H264_PROFILE_MAIN_GUID; //huqb
	GUID m_stPresetGUID = NV_ENC_PRESET_LOW_LATENCY_HP_GUID;// NV_ENC_PRESET_LOW_LATENCY_DEFAULT_GUID; NV_ENC_PRESET_LOW_LATENCY_HP_GUID
	g_pEncD3d11->CreateDefaultEncoderParams(&initializeParams, m_stEncodeGUID, m_stPresetGUID, m_stCodecProfileGUID, 100,nBps);

    pEncodeCLIOptions->SetInitParams(&initializeParams, bForceNv12 ? NV_ENC_BUFFER_FORMAT_NV12 : NV_ENC_BUFFER_FORMAT_ARGB);

	g_pEncD3d11->CreateEncoder(&initializeParams);
}


int Encode(char* szBuffer, int nSize)
{
	//Timer time;
	//time.reset();

	std::vector<std::vector<uint8_t>> vPacket;

	const NvEncInputFrame* encoderInputFrame = g_pEncD3d11->GetNextInputFrame();
	D3D11_MAPPED_SUBRESOURCE map;
	ck(pContext->Map(pTexSysMem.Get(), D3D11CalcSubresource(0, 0, 1), D3D11_MAP_WRITE, 0, &map));
	for (int y = 0; y < g_nHeight; y++)
	{
		memcpy((uint8_t *)map.pData + y * map.RowPitch, szBuffer + y * g_nWidth * 4, g_nWidth * 4);
	}
	pContext->Unmap(pTexSysMem.Get(), D3D11CalcSubresource(0, 0, 1));

	ID3D11Texture2D *pTexBgra = reinterpret_cast<ID3D11Texture2D*>(encoderInputFrame->inputPtr);
	pContext->CopyResource(pTexBgra, pTexSysMem.Get());

	g_pEncD3d11->EncodeFrame(vPacket);

	for (std::vector<uint8_t> &packet : vPacket)
	{
		//fwrite(reinterpret_cast<char*>(packet.data()), packet.size(), 1, fpOut);
		if (g_pH264Cb != NULL)
		{
			g_pH264Cb(reinterpret_cast<char*>(packet.data()), packet.size(), g_nWidth, g_nHeight, 0, NULL);
		}
	}

//	fclose(fpOut);
	//long lTime = time.now();

	//std::cout << "1 frame encoded time: " << lTime <<"ms"<< std::endl;

	return 0;
}


int Encode(ID3D11Texture2D* tx)
{
	//Timer time;
	//time.reset();

	std::vector<std::vector<uint8_t>> vPacket;

	const NvEncInputFrame* encoderInputFrame = g_pEncD3d11->GetNextInputFrame();

	ID3D11Texture2D *pTexBgra = reinterpret_cast<ID3D11Texture2D*>(encoderInputFrame->inputPtr);
	pContext->CopyResource(pTexBgra, tx);

	g_pEncD3d11->EncodeFrame(vPacket);

	for (std::vector<uint8_t> &packet : vPacket)
	{
		fwrite(reinterpret_cast<char*>(packet.data()), packet.size(), 1, fpOut);
	}


	//long lTime = time.now();

	//std::cout << "1 frame encoded time: " << lTime <<"ms"<< std::endl;

	return 0;
}

/**
*  This sample application illustrates encoding of frames in ID3D11Texture2D textures.
*  There are 2 modes of operation demonstrated in this application.
*  In the default mode application reads RGB data from file and copies it to D3D11 textures
*  obtained from the encoder using NvEncoder::GetNextInputFrame() and the RGB texture is
*  submitted to NVENC for encoding. In the second case ("-nv12" option) the application converts
*  RGB textures to NV12 textures using DXVA's VideoProcessBlt API call and the NV12 texture is
*  submitted for encoding.
*/
int Domain(int nW, int nH,int nBps)
{
    char szInFilePath[256] = "test.rgb";
    char szOutFilePath[256] = "out.h264";
	int nWidth = nW ;
	int nHeight = nH;
    try
    {
        NvEncoderInitParam encodeCLIOptions;
        int iGpu = 1;
        bool bForceNv12 = false;
        ParseCommandLine_AppEncD3D(0,NULL, szInFilePath, nWidth, nHeight, szOutFilePath, encodeCLIOptions, iGpu, bForceNv12);

 //       CheckInputFile(szInFilePath);

		InitEncode(szInFilePath, nWidth, nHeight,nBps,szOutFilePath, &encodeCLIOptions, iGpu, bForceNv12);
    }
    catch (const std::exception &ex)
    {
        std::cout << ex.what();
        exit(1);
    }
    return 0;
}

//
int InitEncoder(int nWidth, int nHeight, int nBps, OnEncodeStatusCallBack onUsercbi, OnH264StreamCallback h264Cb, void* pUserData)
{
	g_pOnEncStatuscbi = onUsercbi;
	g_pH264Cb = h264Cb;
	Domain(nWidth, nHeight,nBps);
	return 0;
}
//
int PutFrameBuffer(char* szBuffer, int nSize, int nType)
{
	//Timer t;
	//t.reset();
	if (nSize == 0 || szBuffer == NULL)
		return -1;
	Encode(szBuffer, nSize);
	//long lTime = t.now();
	//std::cout << "1 frame time: " << lTime << "ms" << std::endl;
	return 0;
}
//
int PutFrameBuffer(void* pframe)
{
	if (pframe == NULL)
		return -1;
	Encode((ID3D11Texture2D*)pframe);
	return 0;
}
//
int releaseEncoder()
{
	if (g_pEncD3d11!=NULL)
	{
		g_pEncD3d11->DestroyEncoder();
		delete g_pEncD3d11;
		g_pEncD3d11 = NULL;
	}
	if (fpOut)
	{
		fclose(fpOut);
		fpOut = NULL;
	}
	
	return 0;
}
