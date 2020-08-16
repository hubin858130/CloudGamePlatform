#include "stdafx.h"
#include "BaseFactory.h"

BaseFactory::BaseFactory(void)
{
}

bool BaseFactory::Initialize(HWND hwnd, int width, int height)
{
	imgheight = height;
	imgwidth = width;
	m_hwnd = hwnd;
	m_pRenderTarget = nullptr;
	m_pBitmap = nullptr;
	CreateDeviceResources();
	return true;
}

BaseFactory::~BaseFactory(void)
{
}

HRESULT BaseFactory::CreateDeviceResources()
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU
			(
			rc.right - rc.left,
			rc.bottom - rc.top
			);
		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size, D2D1_PRESENT_OPTIONS_IMMEDIATELY),//第三个参数设置不等待垂直同步，默认垂直同步时最高刷新频率为显卡刷新频率，一般60FPS
			&m_pRenderTarget
			);
		//创建位图
		D2D1_SIZE_U imgsize = D2D1::SizeU(imgwidth, imgheight);
		D2D1_PIXEL_FORMAT pixelFormat =  //位图像素格式描述
		{
			DXGI_FORMAT_B8G8R8A8_UNORM, //该参数设置图像数据区的像素格式，现为RGBA，可根据需要改为别的格式，只是后面的数据拷贝要做相应的调整
			D2D1_ALPHA_MODE_IGNORE
		};
		D2D1_BITMAP_PROPERTIES prop =  //位图具体信息描述
		{
			pixelFormat,
			imgsize.width,
			imgsize.height
		};
		long pitch = imgsize.width * 4;
		imgdata = new char[imgsize.width * imgsize.height * 4];
		memset(imgdata, 0, imgsize.width * imgsize.height * 4);
		m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);//设置图像为抗锯齿模式
		m_pRenderTarget->CreateBitmap(imgsize, imgdata, pitch, &prop, &m_pBitmap);

		imgrect.left = 0;
		imgrect.right = imgwidth;
		imgrect.top = 0;
		imgrect.bottom = imgheight;
	}
	return hr;
}

void BaseFactory::DiscardDeviceResources()
{
	delete[] imgdata;
	SafeRelease(&m_pRenderTarget);
	m_pDirect2dFactory->Release();
	m_pBitmap->Release();
}

void BaseFactory::OnRender(char *data)//绘制图形到指定控件中
{
	m_pRenderTarget->BeginDraw();//跟显示刷新频率有关系
	m_pBitmap->CopyFromMemory(&imgrect, data, imgwidth * 4);
	m_pRenderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(0, 0, rc.right - rc.left, rc.bottom - rc.top));//该矩形大小会受到"更改文本、应用和其他项目的大小:xxx%"的影响
	m_pRenderTarget->EndDraw();
}
