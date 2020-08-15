#ifndef _COMMONRASKEY_H
#define _COMMONRASKEY_H
#include "EvRas.h"
//			( p,		q		f,			n,			e,	   d,	  s)//HongleSetter生成软狗时使用，LicenseServer解析软狗的时候使用
extern RSA_PARAM g_comSoftKeyRSA[] ;

int GetIndexFromCpuID(char* szCpuId) ;

#endif