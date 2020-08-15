#include "StdAfx.h"
#include "CommonRSAkey.h"

RSA_PARAM g_comSoftKeyRSA[] = {
	RSA_PARAM(0x000000000000eacb,0x000000000000e17f,0x00000000cecf196c,0x00000000ced0e5b5,0x000000000000f947,0x000000001b12c35f,0x000000000000001f),
};

int GetIndexFromCpuID(char* szCpuId)
{
	int nCountLen = 0 ;
	if ( strlen(szCpuId)>=16 )
	{
		for (int n=0;n<16;n++ )
		{
			nCountLen+=szCpuId[n] ;
		}
	}
	return nCountLen%512 ;
}