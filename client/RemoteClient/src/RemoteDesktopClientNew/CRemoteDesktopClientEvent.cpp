#include "stdafx.h"
#include "RemoteDesktopClientDlg.h"


CString Int2Cstring(int n)
{
	CString str;
	str.Format("%d", n);
	return str;
}

CString Long2Cstring(int n)
{
	CString str;
	str.Format("%ld", n);
	return str;
}

CString CRemoteDesktopClientDlg::createMsgBody(int mMsg, int mValue1, int mValue2, long lParam)
{
	//{"type":4,"value":[1,2,3]}
	CString strMsg = "{\"type\":";
	strMsg += Int2Cstring(mMsg);
	strMsg += ",\"value\":[";
	switch (mMsg) {
	case TYPE_MOUSE_LEFT_DOWN:
	case TYPE_MOUSE_LEFT_UP:
	case TYPE_MOUSE_RIGHT_DOWN:
	case TYPE_MOUSE_RIGHT_UP:
	case TYPE_MOUSE_MOVE:
	{
		strMsg += Int2Cstring(mValue1);
		strMsg += ",";
		strMsg += Int2Cstring(mValue2);
		strMsg += ",";
		strMsg += Long2Cstring(lParam);
	}
		break;
	default: {
				 strMsg += Int2Cstring(mValue1);
	}
		break;
	}
	strMsg += "]}";

	return strMsg;
}

HBITMAP CRemoteDesktopClientDlg::MakeBitmap(HDC hDc, LPBYTE lpBits, long lWidth, long lHeight, WORD wBitCount)
{
	BITMAPINFO bitinfo;
	memset(&bitinfo, 0, sizeof(BITMAPINFO));

	bitinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitinfo.bmiHeader.biWidth = lWidth;
	bitinfo.bmiHeader.biHeight = lHeight;
	bitinfo.bmiHeader.biPlanes = 1;
	bitinfo.bmiHeader.biBitCount = wBitCount;
	bitinfo.bmiHeader.biCompression = BI_RGB;
	bitinfo.bmiHeader.biSizeImage = lWidth*lHeight*(wBitCount / 8);
	bitinfo.bmiHeader.biXPelsPerMeter = 96;
	bitinfo.bmiHeader.biYPelsPerMeter = 96;
	bitinfo.bmiHeader.biClrUsed = 0;
	bitinfo.bmiHeader.biClrImportant = 0;

	return CreateDIBitmap(hDc, &bitinfo.bmiHeader, CBM_INIT, lpBits, &bitinfo, DIB_RGB_COLORS);
}

BOOL SaveBitmapToFile(HBITMAP   hBitmap, CString szfilename)
{
	HDC     hDC;
	//当前分辨率下每象素所占字节数          
	int     iBits;
	//位图中每象素所占字节数          
	WORD     wBitCount;
	//定义调色板大小，     位图中像素字节大小     ，位图文件大小     ，     写入文件字节数              
	DWORD     dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	//位图属性结构              
	BITMAP     Bitmap;
	//位图文件头结构          
	BITMAPFILEHEADER     bmfHdr;
	//位图信息头结构              
	BITMAPINFOHEADER     bi;
	//指向位图信息头结构                  
	LPBITMAPINFOHEADER     lpbi;
	//定义文件，分配内存句柄，调色板句柄              
	HANDLE     fh, hDib, hPal, hOldPal = NULL;

	//计算位图文件每个像素所占字节数              
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL)     *     GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else  if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = iBits;//24

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 0;

	dwBmBitsSize = ((Bitmap.bmWidth *wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存              
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	//     处理调色板                  
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//     获取该调色板下新的像素值              
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,
		(BITMAPINFO *)lpbi, DIB_RGB_COLORS);

	//恢复调色板                  
	if (hOldPal)
	{
		::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//创建位图文件                  
	fh = CreateFile(szfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)         return     FALSE;

	//     设置位图文件头              
	bmfHdr.bfType = 0x4D42;     //     "BM"              
	dwDIBSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
	//     写入位图文件头              
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//     写入位图文件其余内容              
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	//清除                  
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return     TRUE;

}

void GetMaskBitmaps(HBITMAP hSourceBitmap, COLORREF clrTransparent,
	HBITMAP &hAndMaskBitmap, HBITMAP &hXorMaskBitmap)
{
	HDC hDC = ::GetDC(NULL);
	HDC hMainDC = ::CreateCompatibleDC(hDC);
	HDC hAndMaskDC = ::CreateCompatibleDC(hDC);
	HDC hXorMaskDC = ::CreateCompatibleDC(hDC);

	//Get the dimensions of the source bitmap
	BITMAP bm;
	::GetObject(hSourceBitmap, sizeof(BITMAP), &bm);


	hAndMaskBitmap = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);
	hXorMaskBitmap = ::CreateCompatibleBitmap(hDC, bm.bmWidth, bm.bmHeight);

	//Select the bitmaps to DC
	HBITMAP hOldMainBitmap = (HBITMAP)::SelectObject(hMainDC, hSourceBitmap);
	HBITMAP hOldAndMaskBitmap = (HBITMAP)::SelectObject(hAndMaskDC, hAndMaskBitmap);
	HBITMAP hOldXorMaskBitmap = (HBITMAP)::SelectObject(hXorMaskDC, hXorMaskBitmap);

	//Scan each pixel of the souce bitmap and create the masks
	COLORREF MainBitPixel;
	for (int x = 0; x<bm.bmWidth; ++x)
	{
		for (int y = 0; y<bm.bmHeight; ++y)
		{
			MainBitPixel = ::GetPixel(hMainDC, x, y);
			if (MainBitPixel == clrTransparent)
			{
				::SetPixel(hAndMaskDC, x, y, RGB(255, 255, 255));
				::SetPixel(hXorMaskDC, x, y, RGB(0, 0, 0));
			}
			else
			{
				::SetPixel(hAndMaskDC, x, y, RGB(0, 0, 0));
				::SetPixel(hXorMaskDC, x, y, MainBitPixel);
			}
		}
	}

	::SelectObject(hMainDC, hOldMainBitmap);
	::SelectObject(hAndMaskDC, hOldAndMaskBitmap);
	::SelectObject(hXorMaskDC, hOldXorMaskBitmap);

	::DeleteDC(hXorMaskDC);
	::DeleteDC(hAndMaskDC);
	::DeleteDC(hMainDC);

	::ReleaseDC(NULL, hDC);
}

HCURSOR CRemoteDesktopClientDlg::CreateCursorFromBitmap(HBITMAP hSourceBitmap,COLORREF clrTransparent,DWORD xHotspot, DWORD yHotspot)
{
	HCURSOR hRetCursor = NULL;

	do
	{
		if (NULL == hSourceBitmap)
		{
			break;
		}

		//Create the AND and XOR masks for the bitmap
		HBITMAP hAndMask = NULL;
		HBITMAP hXorMask = NULL;
		GetMaskBitmaps(hSourceBitmap, clrTransparent, hAndMask, hXorMask);
		if (NULL == hAndMask || NULL == hXorMask)
		{
			break;
		}

		//Create the cursor using the masks and the hotspot values provided
		ICONINFO iconinfo = { 0 };
		iconinfo.fIcon = FALSE;
		iconinfo.xHotspot = xHotspot;
		iconinfo.yHotspot = yHotspot;
		iconinfo.hbmMask = hAndMask;
		iconinfo.hbmColor = hXorMask;

		hRetCursor = ::CreateIconIndirect(&iconinfo);

	} while (0);

	return hRetCursor;
}