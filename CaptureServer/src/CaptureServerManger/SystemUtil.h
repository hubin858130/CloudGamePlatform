#ifndef _SYSTEMUTIL_H
#define _SYSTEMUTIL_H

#include <string>
using std::string;

	namespace SYSTEMUTIL
	{
		//转换UTF8格式
		string GetUtf8(const string & strContent);

		//UTF8转换成ANSI格式
		string GetUcs2(const string & strContent);

		//转换成GB2312格式
		string GetGB2312(const string & strContent);

		//获取当前时间戳
		long long GetTimeStamp();

		//获取当前可执行文件所在目录
		string GetExeFileExistDir();

		//获取本机MAC地址
		string GetLocalMacAdress();

		//获取主机名称
		string GetLocalHostName();

		//获取本机IP
		string GetLocalIP();

		//按名称判断进程是否存在
		bool IsProcessorExist(string strProcessorName);

		//按进程ID判断进程是否存在
		bool IsProcessorExist(int nProcessID);

		//启动algounit
		int OpenProcessor(string strProcessorName,char * sParam,int nUnitID,int & nProcessorID,bool bIsShowWindow);

		//按进程名结束进程
		void TerminateProcessor(string strProcessorName);

		//按进程ID结束进程
		void TerminateProcessor(int nProcessID);

		//递归删除文件夹
		void DeleteDirection(string & strRootDir);

		//删除空目录
		bool DeleteEmptyDirectoryEx(string pdir);

		//删除文件
		void ForceDeleteFile(char * strFile);

		//遍历删除N天之前的文件
		bool DeleteLocalStoreFile(string & strRoot, int nCircle);

		//搜索指定日期的文件
		bool GetHistoryLocalFileInfo(string & strRoot,string & strFileName,int nBeforeDay,tm & tFileCreateTime);

		//获取历史报警文件
		bool GetHistoryAlarmFile(string & strRoot,string & strFileName);

		//获取历史报警图片文件
		bool GetHistoryPicFileInfo(string & strRoot,string & strFileName);

		//获取单层文件夹列表
		bool GetFileDirListInfo(string & strRoot,string * pStrFileDirList, int nMaxListNumber, int & nFileDirNumber);

		//设置系统时间
		bool SetDeviceSystemTime(struct tm & tSynTime);

		//处理子进程结束消息
		void HandleChildProcessSignal();

#if defined(_WIN32) || defined(_WIN64)
		#include <WTypes.h>
		//for windows special
		//文件s时间转time_t
		time_t FileTimeToTimet(FILETIME const& ft);

		//time_t转文件时间
		FILETIME TimetToFiletime(time_t const& tt);

#else
		//判断是否为目录
		int IS_DIR(const char* path);
#endif

	}
#endif