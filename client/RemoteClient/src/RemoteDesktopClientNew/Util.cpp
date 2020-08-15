#include "stdafx.h"
#include "Util.h"
#include <objbase.h>  
#include <time.h>
#include <stdio.h>

unsigned int IPStrToInt(const char *ip)
{
	unsigned uResult = 0;
	int nShift = 24;
	int temp = 0;
	const char *pStart = ip;
	const char *pEnd = ip;

	while (*pEnd != '\0')
	{
		while (*pEnd != '.' && *pEnd != '\0')
		{
			pEnd++;
		}
		temp = 0;
		for (pStart; pStart != pEnd; ++pStart)
		{
			temp = temp * 10 + *pStart - '0';
		}

		uResult += temp << nShift;
		nShift -= 8;

		if (*pEnd == '\0')
			break;
		pStart = pEnd + 1;
		pEnd++;
	}

	return uResult;
}

string GetExeFileExistDir()
{
	string strCurPath;
	char szBuffer[1024];
	memset(szBuffer, 0x00, sizeof(szBuffer));
	DWORD dwSize = GetModuleFileName(NULL, szBuffer, 1024);
	szBuffer[dwSize] = 0;
	while (szBuffer[dwSize] != '\\' && dwSize != 0)
	{
		szBuffer[dwSize] = 0; dwSize--;
	}
	//去掉最后一个"\\"
	if (0 <= dwSize)
	{
		szBuffer[dwSize] = 0;
	}
	strCurPath = szBuffer;
	//替换所有的"\\"
	string::size_type   pos(0);
	string strNewValue = "/";
	string strOldValue = "\\";
	while ((pos = strCurPath.find(strOldValue.c_str(), 0)) != string::npos)
	{
		strCurPath.replace(pos, strOldValue.length(), strNewValue.c_str());
	}
	return strCurPath;
}
  
string CreateGuidString(bool bFlag) //为了防止在绝对短的时间内批量生成GUID，我添加了时间戳和随机数减小重复概率
{
	string strGuid;
	char buffer[40];
	GUID guid;
	time_t ltime;
	time(&ltime);

	if (CoCreateGuid(&guid))
	{
		fprintf(stderr, "create guid error\n");
	}
	else
	{
		guid.Data1 = (DWORD)ltime; //添加上时间戳
		guid.Data2 = (WORD)rand(); //添加随机数
		guid.Data3 = (WORD)rand(); //添加随机数

		if (bFlag)
		{
			_snprintf_s(buffer, sizeof(buffer),
				"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
				guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2],
				guid.Data4[3], guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);
		}
		else
		{
			_snprintf_s(buffer, sizeof(buffer),
				"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
				guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2],
				guid.Data4[3], guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);
		}

		strGuid = buffer;

	}
	return strGuid;

}