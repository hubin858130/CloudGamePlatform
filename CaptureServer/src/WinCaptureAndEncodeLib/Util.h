#ifndef _DECODEUNIT_UTIL_H
#define _DECODEUNIT_UTIL_H

//RGB32 to rgb24
bool TransRGB32ToRGB24(unsigned char* pcDes, int nDesSize, unsigned char* pcSrc, int nSrcSize, int nSrcWidth, int nSrcHeight);
//RGB24תYUV420
bool TransRGB24ToYUV420(unsigned char * pcDes, int nDesSize, unsigned char* pcSrc, int nSrcSize, int nSrcWidth,int nSrcHeight);
//RGB32YUV420
bool TransRGB32ToYUV420(unsigned char * pcDes, int nDesSize, unsigned char* pcSrc, int nSrcSize, int nSrcWidth, int nSrcHeight);


#endif