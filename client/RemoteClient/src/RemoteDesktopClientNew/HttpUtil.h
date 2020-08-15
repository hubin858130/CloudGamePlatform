#pragma once
class CHttpUtil
{
public:
	CHttpUtil();
	~CHttpUtil();

	int getVmInfo(char* szIP, int nPort, int nNetType, CString strAreaId, CString& strResult);
	int getVmInfo(char* szIP, int nPort, CString strAreaId, CString& strResult);
};

