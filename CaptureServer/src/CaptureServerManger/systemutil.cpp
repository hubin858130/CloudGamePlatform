#include "stdafx.h"
#include "SystemUtil.h"

#if defined(_WIN32) || defined(_WIN64)

#else

#include <time.h>
#include <locale.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>  //for execl(),fork()
#include <stdio.h>
#include <string.h>  //for memcpy()...
#include <sys/socket.h>
#include <sys/types.h>  //for pid_t,
#include <sys/ioctl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <signal.h> //for kill()
#include <sys/stat.h> // for stat()
#include <sys/wait.h> // for wait() waitpid()

#include <string>
using std::string;   

#define PROC_DIRECTORY "/proc/"

#endif

	namespace SYSTEMUTIL
	{
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#include <time.h>
#include <iphlpapi.h>
#include <wincon.h>
#include <stdlib.h>
#include <stdio.h>
#include <wininet.h>
#include <winsock.h>
#include <tlhelp32.h>
#include <shellapi.h>

#pragma comment(lib,"netapi32.lib")
#pragma comment(lib, "ws2_32.lib")

		string GetUtf8(const string & strContent)
		{
			int nOutLen1 = MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), -1, 0, 0);
			wchar_t* pcOut1 = new wchar_t[nOutLen1+1];
			MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), -1, pcOut1, nOutLen1);
			pcOut1[nOutLen1] = 0;
			int nOutLen2 = WideCharToMultiByte(CP_UTF8, 0, pcOut1, -1, 0, 0, 0, 0);
			char* pcOut2 = new char[nOutLen2+1];
			int r = WideCharToMultiByte(CP_UTF8, 0, pcOut1, -1, pcOut2, nOutLen2, 0, 0);
			pcOut2[nOutLen2] = 0;
			string str = pcOut2;
			delete []pcOut1;
			delete []pcOut2;
			return str;
		}


		string GetUcs2(const string & strContent)
		{
			int nOutLen1 = MultiByteToWideChar(CP_UTF8, 0, strContent.c_str(), -1, 0, 0);
			wchar_t* pcOut1 = new wchar_t[nOutLen1+1];
			MultiByteToWideChar(CP_UTF8, 0, strContent.c_str(), -1, pcOut1, nOutLen1);
			pcOut1[nOutLen1] = 0;
			int nOutLen2 = WideCharToMultiByte(CP_ACP, 0, pcOut1, -1, 0, 0, 0, 0);
			char* pcOut2 = new char[nOutLen2+1];
			int r = WideCharToMultiByte(CP_ACP, 0, pcOut1, -1, pcOut2, nOutLen2, 0, 0);
			pcOut2[nOutLen2] = 0;
			string str = pcOut2;
			delete []pcOut1;
			delete []pcOut2;
			return str;
		}

		//转换成GB2312格式
		string GetGB2312(const string & strContent)
		{
			int nOutLen1 = MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), -1, 0, 0);
			wchar_t* pcOut1 = new wchar_t[nOutLen1+1];
			MultiByteToWideChar(CP_ACP, 0, strContent.c_str(), -1, pcOut1, nOutLen1);
			pcOut1[nOutLen1] = 0;
			int nOutLen2 = WideCharToMultiByte(20936, 0, pcOut1, -1, 0, 0, 0, 0);
			char* pcOut2 = new char[nOutLen2+1];
			int r = WideCharToMultiByte(20936, 0, pcOut1, -1, pcOut2, nOutLen2, 0, 0);
			pcOut2[nOutLen2] = 0;
			string str = pcOut2;
			delete []pcOut1;
			delete []pcOut2;
			return str;
		}

		long long GetTimeStamp()
		{
			long long lCurrentSystemTime = 0;
			SYSTEMTIME systime;
			GetLocalTime(&systime);

			time_t tCurrentTime = time(NULL);
			lCurrentSystemTime = tCurrentTime;
			lCurrentSystemTime *= 1000;
			lCurrentSystemTime += systime.wMilliseconds;

			return lCurrentSystemTime;
		}

		string GetExeFileExistDir()
		{
			string strCurPath; 
			char szBuffer[1024];
			memset(szBuffer,0x00,sizeof(szBuffer));
			DWORD dwSize = GetModuleFileName(NULL, szBuffer, 1024);
			szBuffer[dwSize] = 0;
			while(szBuffer[dwSize] != '\\' && dwSize != 0)
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
			while((pos=strCurPath.find(strOldValue.c_str(),0))!=string::npos)
			{  
				strCurPath.replace(pos,strOldValue.length(),strNewValue.c_str()); 
			} 
			return strCurPath;
		}

		void initWinSock()
		{
			static bool wsInit = false;
			if (! wsInit)
			{
				WORD wVersionRequested = MAKEWORD( 2, 0);
				WSADATA wsaData;
				if (0 == WSAStartup(wVersionRequested, &wsaData))
				{
					wsInit = true;
				}
			}
		}

		void UnInitWinSock()
		{
			WSACleanup();
		}

		//获取本机MAC地址
		string GetLocalMacAdress()
		{
			//char cMacAdress[48];
			//string strMacAdress;
			//PIP_ADAPTER_INFO pAdapterInfo;
			//PIP_ADAPTER_INFO pAdapter = NULL;
			//DWORD dwRetVal = 0;
			//ULONG ulOutBufLen;
			//pAdapterInfo=(PIP_ADAPTER_INFO)malloc(sizeof(IP_ADAPTER_INFO));
			//ulOutBufLen = sizeof(IP_ADAPTER_INFO);

			//// 第一次调用GetAdapterInfo获取ulOutBufLen大小
			//if (GetAdaptersInfo( pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
			//{
			//	free(pAdapterInfo);
			//	pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen);
			//}

			//if ((dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
			//	pAdapter = pAdapterInfo;
			//	while (pAdapter)
			//	{
			//		string strTmpMac;
			//		sprintf_s(cMacAdress,"%02x:%02x:%02x:%02x:%02x:%02x",pAdapter->Address[0],pAdapter->Address[1],pAdapter->Address[2],pAdapter->Address[3],pAdapter->Address[4],pAdapter->Address[5]);
			//		strTmpMac = cMacAdress;
			//		if (strMacAdress.empty())
			//		{
			//			strMacAdress = strTmpMac;
			//		}
			//		else if(strMacAdress > strTmpMac)   //取mac最小的一个返回
			//		{
			//			strMacAdress = strTmpMac;
			//		}
			//		pAdapter = pAdapter->Next;
			//	}
			//}
			//else
			//{
			//	printf("Call to GetAdaptersInfo failed.\n");
			//}
			//return strMacAdress;
			return "";
		}

		string GetLocalHostName()
		{
			initWinSock();
			char name[300];
			string strHostName;
			memset(&name[0],0,300);
			int nResult =gethostname(&name[0],300);
			strHostName = name;

			return strHostName;
		}

		string GetLocalIP()
		{
			string strLocalIP;

			//Socket初始化部分
			initWinSock();

			//通过本机主机名.
			char host_name[256];
			gethostname(host_name,sizeof(host_name));

			struct hostent *hp;
			struct in_addr sa;
			char *buf;

			hp = gethostbyname(host_name);

			if (hp != NULL)
			{
				//循环获取本地主机名
				for (int i = 0; i <= 0/*hp->h_addr_list[i]*/; i++)
				{
					memcpy (&sa, hp->h_addr_list[i],hp->h_length);

					buf = inet_ntoa(sa);
				}
			}
			strLocalIP = buf;

			return strLocalIP;
		}

		bool IsProcessorExist(string strProcessorName)
		{
			bool bSuccess = false;
			HANDLE hProcessSnap;
			HANDLE hProcess;
			PROCESSENTRY32 pe32;
			DWORD dwPriorityClass;

			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return bSuccess;
			}

			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First( hProcessSnap, &pe32))
			{
				CloseHandle(hProcessSnap);
				return bSuccess;
			}

			do
			{
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
				}
				else
				{
					if ((strProcessorName.compare(0,strProcessorName.length(),pe32.szExeFile)) == 0)
					{
						CloseHandle(hProcess);
						bSuccess = true;
						break;
					}
					CloseHandle(hProcess);
				}
			} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);
			return bSuccess;
		}

		bool IsProcessorExist(int nProcessID)
		{
			bool bSuccess = false;
			HANDLE hProcessSnap;
			HANDLE hProcess;
			PROCESSENTRY32 pe32;
			DWORD dwPriorityClass;

			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return bSuccess;
			}

			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First( hProcessSnap, &pe32))
			{
				CloseHandle(hProcessSnap);
				return bSuccess;
			}

			do
			{
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
				}
				else
				{
					if (nProcessID == pe32.th32ProcessID)
					{
						CloseHandle(hProcess);
						bSuccess = true;
						break;
					}
					CloseHandle(hProcess);
				}
			} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);
			return bSuccess;
		}

		int OpenProcessor(string strProcessorName,char * sParam,int nUnitID,int & nProcessorID,bool bIsShowWindow)
		{
			STARTUPINFO   si={sizeof(si)}; 
			PROCESS_INFORMATION   pi; 
			si.dwFlags=STARTF_USESHOWWINDOW;
			if (bIsShowWindow)
			{
				si.wShowWindow=SW_SHOW;
			}
			else
			{
				si.wShowWindow=SW_HIDE; 
			}

			bool bIsSuccess = CreateProcessA(NULL,sParam,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,(LPSTARTUPINFOA)&si,&pi);
			if (!bIsSuccess) 
			{
				//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"Open AlgoUnit:" << nUnitID << " failed! process name:" << strProcessorName);
				return -1;
			}
			else
			{
				nProcessorID = pi.dwProcessId;
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"Open AlgoUnit:" << nUnitID << " success! process name:" << strProcessorName);
				return 0;
			}
		}

		void TerminateProcessor(string strProcessorName)
		{
			bool bSuccess = false;
			HANDLE hProcessSnap;
			HANDLE hProcess;
			PROCESSENTRY32 pe32;
			DWORD dwPriorityClass;

			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return;
			}

			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First( hProcessSnap, &pe32))
			{
				CloseHandle(hProcessSnap);
				return;
			}

			do
			{
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
				}
				else
				{
					if ((strProcessorName.compare(0,strProcessorName.length(),pe32.szExeFile)) == 0)
					{
						TerminateProcess(hProcess, 0);
					}
					CloseHandle(hProcess);
				}
			} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);
			return;
		}

		void TerminateProcessor(int nProcessID)
		{
			bool bSuccess = false;
			HANDLE hProcessSnap;
			HANDLE hProcess;
			PROCESSENTRY32 pe32;
			DWORD dwPriorityClass;

			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				return;
			}

			pe32.dwSize = sizeof(PROCESSENTRY32);

			if (!Process32First( hProcessSnap, &pe32))
			{
				CloseHandle(hProcessSnap);
				return;
			}

			do
			{
				dwPriorityClass = 0;
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
				if (hProcess == NULL)
				{
				}
				else
				{
					if (nProcessID == pe32.th32ProcessID)
					{
						TerminateProcess(hProcess, 0);
					}
					CloseHandle(hProcess);
				}
			} while(Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);
			return;
		}

		void DeleteDirection(string & strRootDir)
		{
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;

			string::size_type   pos(0);

			int nSendAlarmCount = 0;

			hSearchFile = FindFirstFile((strRootDir+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return ;
			}
			else
			{
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						string subDir= strRootDir + "/";
						subDir += fileData.cFileName;
						DeleteDirection(subDir);
					}
					else
					{	
						string strFileName = strRootDir + "/" + fileData.cFileName;

						SetFileAttributes(strFileName.c_str(),FILE_ATTRIBUTE_NORMAL);
						BOOL Ret = DeleteFile(strFileName.c_str());
						if (!Ret)
						{
							MoveFileEx(strFileName.c_str(), NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
						}

					}
				} while (FindNextFile(hSearchFile, &fileData));	

				// release resource
				FindClose(hSearchFile);
			}

			RemoveDirectory(strRootDir.c_str());
		};

		bool DeleteEmptyDirectoryEx(string pdir)
		{
			if(pdir.length()<4)return false;         // 参数长度必须大于3，即不能为磁盘根目录或空白
			string Dir=pdir +"/";
			string Files=Dir+"*.*";
			WIN32_FIND_DATA wfd;
			HANDLE hFind=FindFirstFile(Files.c_str(),&wfd);
			bool Ret=true;
			string Tmp;
			bool bDeleteResult;
			bool bHasFile = false;
			if(hFind!=INVALID_HANDLE_VALUE)
			{
				bool bFind=true;
				while(bFind)
				{
					if(wfd.cFileName[0]!='.') // . ..
					{
						Tmp=Dir+wfd.cFileName;
						if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
						{ // 删除所有子目录
							Ret=Ret&&DeleteEmptyDirectoryEx(Tmp);
							if (!Ret)   //如果删除子文件夹失败，则退出
							{
								break;
							}
						}
						else
						{
							bHasFile = true;
						}
					}
					bFind=FindNextFile(hFind,&wfd);
				}
				FindClose(hFind);
			}
			if(!bHasFile && Ret)   //如果文件夹中没有文件，并且删除子文件夹成功，则删除文件夹
			{
				bDeleteResult = RemoveDirectory(Dir.c_str());
				if (!bDeleteResult)  //如果删除空文件夹失败，则置为重启删除并设置为隐藏
				{
					MoveFileEx(Dir.c_str(), NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
					SetFileAttributes(Dir.c_str(),FILE_ATTRIBUTE_HIDDEN);
					bDeleteResult = true;
				}
			}
			else
			{
				bDeleteResult = false;
			}
			return bDeleteResult;
		}

		time_t FileTimeToTimet(FILETIME const& ft)
		{
			ULARGE_INTEGER ull;
			ull.LowPart = ft.dwLowDateTime;
			ull.HighPart = ft.dwHighDateTime;
			return ull.QuadPart / 10000000ULL - 11644473600ULL;
		}

		FILETIME TimetToFiletime(time_t const& tt)
		{
			FILETIME ft;
			ULONGLONG ull = 0;

			memset(&ft, 0, sizeof(ft));

			ull = tt * 10000000 + 116444736000000000;
			ft.dwLowDateTime = (DWORD) ull;
			ft.dwHighDateTime = (DWORD)(ull >> 32);
			return ft;
		}

		//删除文件
		void ForceDeleteFile(char * strFile)
		{
			SetFileAttributes(strFile,FILE_ATTRIBUTE_NORMAL);
			BOOL Ret = DeleteFile(strFile);
			if (!Ret)
			{
				MoveFileEx(strFile, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
			}
		}

		//遍历删除N天之前的文件
		bool DeleteLocalStoreFile(string & strRoot, int nCircle)
		{
			bool bHasDelteFile = false;
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;	
			string local = strRoot;

			hSearchFile = FindFirstFile((local+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				bool bIsThisDirDel = false;
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						string subDir= "/";
						subDir += fileData.cFileName;

						DeleteEmptyDirectoryEx(local+subDir);			//删除空文件夹，非空则不删除，返回失败

						bHasDelteFile = DeleteLocalStoreFile(local+subDir, nCircle);	

						if (bHasDelteFile)
						{
							break;
						}
					}
					else 
					{	
						string fileName = fileData.cFileName;
						//获取文件时间
						time_t tFileTime = FileTimeToTimet(fileData.ftCreationTime);
						tm * ptmFileTime = localtime(&tFileTime);
						ptmFileTime->tm_hour = 0;
						ptmFileTime->tm_min = 0;
						ptmFileTime->tm_sec = 0;
						tFileTime = mktime(ptmFileTime);
						//获取本地时间
						time_t tLocalTime = time(NULL);
						tm * ptmLocalTime = localtime(&tLocalTime);
						ptmLocalTime->tm_hour = 0;
						ptmLocalTime->tm_min = 0;
						ptmLocalTime->tm_sec = 0;
						tLocalTime = mktime(ptmLocalTime);
						//检查是否超出存储周期
						if (tLocalTime - tFileTime > nCircle * 24 * 3600)
						{
							SetFileAttributes((local+"/"+fileName).c_str(),FILE_ATTRIBUTE_NORMAL);
							DeleteFile((local+"/"+fileName).c_str());	

							bHasDelteFile = true;
							bIsThisDirDel = true;
						}
					}
				} while (FindNextFile(hSearchFile, &fileData));	

				//log
				if (bIsThisDirDel)
				{
					//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"delete local store file dir:" << strRoot);
				}

				// release resource
				FindClose(hSearchFile);
			}

			return bHasDelteFile;
		}

		bool GetHistoryLocalFileInfo(string & strRoot,string & strFileName,int nBeforeDay,tm & tFileCreateTime)
		{
			bool bHasFile = false;
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;	
			string local = strRoot + strFileName;

			hSearchFile = FindFirstFile((local+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						string subDir= strFileName + "/";
						subDir += fileData.cFileName;

						DeleteEmptyDirectoryEx(local+subDir);			//删除空文件夹，非空则不删除，返回失败

						bHasFile = GetHistoryLocalFileInfo(local, subDir,nBeforeDay,tFileCreateTime);	

						if (bHasFile)
						{
							strFileName = subDir;
							break;
						}
					}
					else 
					{	
						string fileName = fileData.cFileName;
						tm tTempFileTime;
						//获取文件时间
						time_t tFileTime = FileTimeToTimet(fileData.ftCreationTime);
						tm * ptmFileTime = localtime(&tFileTime);
						ptmFileTime->tm_hour = 0;
						ptmFileTime->tm_min = 0;
						ptmFileTime->tm_sec = 0;
						tFileTime = mktime(ptmFileTime);
						tTempFileTime = *ptmFileTime;
						//获取本地时间
						time_t tLocalTime = time(NULL);
						tm * ptmLocalTime = localtime(&tLocalTime);
						ptmLocalTime->tm_hour = 0;
						ptmLocalTime->tm_min = 0;
						ptmLocalTime->tm_sec = 0;
						tLocalTime = mktime(ptmLocalTime);
						//检查是否超出存储周期
						if (tLocalTime - tFileTime > nBeforeDay * 24 * 3600)
						{
							strFileName += "/" + string(fileData.cFileName);
							tFileCreateTime = tTempFileTime;
							bHasFile = true;
							break;
						}
					}
				} while (FindNextFile(hSearchFile, &fileData));	

				// release resource
				FindClose(hSearchFile);
			}

			return bHasFile;
		}

		bool GetHistoryAlarmFile(string & strRoot,string & strFileName)
		{
			bool bRst = false;
			int nResult = -1;
			bool bResult = false;
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;

			string::size_type   pos(0);

			int nSendAlarmCount = 0;

			hSearchFile = FindFirstFile((strRoot+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						string subDir= "/";
						subDir += fileData.cFileName;
						if (GetHistoryAlarmFile(strRoot+subDir,strFileName))
						{
							FindClose(hSearchFile);
							return true;
						}
						else
						{
							DeleteEmptyDirectoryEx(strRoot+subDir);			//删除空文件夹，非空则不删除，返回失败
						}
					}
					else
					{	
						string fileName = fileData.cFileName;
						string tagAlarm = ".alarm";

						int nDifLength = fileName.size()-tagAlarm.size();

						if (nDifLength > 0) 
						{	
							if ((fileName.compare(fileName.size()-tagAlarm.length(), tagAlarm.length(), tagAlarm)) == 0)
							{
								strFileName = strRoot + "/" + fileName;
								FindClose(hSearchFile);

								return true;
							}
						}
					}
				} while (FindNextFile(hSearchFile, &fileData));	

				// release resource
				FindClose(hSearchFile);
			}
			return false;
		}

		bool GetHistoryPicFileInfo(string & strRoot,string & strFileName)
		{
			bool bRst = false;
			int nResult = -1;
			bool bResult = false;
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;

			string::size_type   pos(0);

			int nSendAlarmCount = 0;

			hSearchFile = FindFirstFile((strRoot+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						string subDir= "/";
						subDir += fileData.cFileName;
						if (GetHistoryPicFileInfo(strRoot+subDir,strFileName))
						{
							FindClose(hSearchFile);
							return true;
						}
						else
						{
							DeleteEmptyDirectoryEx(strRoot+subDir);			//删除空文件夹，非空则不删除，返回失败
						}
					}
					else
					{	
						string fileName = fileData.cFileName;
						string tagAlarm = ".dat";

						int nDifLength = fileName.size()-tagAlarm.size();

						if (nDifLength > 0) 
						{	
							if ((fileName.compare(fileName.size()-tagAlarm.length(), tagAlarm.length(), tagAlarm)) == 0)
							{
								strFileName = strRoot + "/" + fileName;
								FindClose(hSearchFile);

								return true;
							}
						}
					}
				} while (FindNextFile(hSearchFile, &fileData));	

				// release resource
				FindClose(hSearchFile);
			}
			return false;
		}

		//获取单层文件夹列表
		bool GetFileDirListInfo(string & strRoot,string * pStrFileDirList, int nMaxListNumber, int & nFileDirNumber)
		{
			bool bRst = false;
			HANDLE hSearchFile;
			WIN32_FIND_DATA fileData;

			string::size_type   pos(0);

			nFileDirNumber = 0;

			hSearchFile = FindFirstFile((strRoot+"/*").c_str(),&fileData);
			if (hSearchFile == INVALID_HANDLE_VALUE)
			{
				return false;
			}
			else
			{
				do
				{
					if ((_stricmp(fileData.cFileName, ".") == 0) || (_stricmp(fileData.cFileName, "..") == 0))
						continue;

					if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						if (nFileDirNumber < nMaxListNumber)
						{
							pStrFileDirList[nFileDirNumber] = fileData.cFileName;
							nFileDirNumber++;
						}
						else
						{
							break;
						}
					}
				} while (FindNextFile(hSearchFile, &fileData));	

				// release resource
				FindClose(hSearchFile);
			}
			return true;
		}

		bool SetDeviceSystemTime(struct tm & tSynTime)
		{
			bool bRst = true;

			// translations between Coordinated Universal Time (UTC) and local time
			TIME_ZONE_INFORMATION a  ;
			GetTimeZoneInformation(&a);
			//T.wHour += a.Bias/60;//The bias is the difference, in minutes, between Coordinated Universal Time (UTC) and local time
			//按时区转换时间tSynTime
			time_t tTmpSynTime = mktime(&tSynTime);
			tTmpSynTime += (a.Bias/60) * 3600;
			struct tm *pTTransferSynTime = localtime(&tTmpSynTime);

			SYSTEMTIME        T;
			GetLocalTime(&T);
			T.wYear = pTTransferSynTime->tm_year + 1900;
			T.wMonth = pTTransferSynTime->tm_mon + 1;
			T.wDay = pTTransferSynTime->tm_mday;
			T.wHour = pTTransferSynTime->tm_hour;
			T.wMinute = pTTransferSynTime->tm_min;
			T.wSecond = pTTransferSynTime->tm_sec;

			if(!SetSystemTime(&T))
			{
				bRst = false;
			}

			return bRst;
		}

		//处理子进程结束消息
		void HandleChildProcessSignal()
		{
			return;
		}

#else
		string GetUtf8(const string & strContent)
		{

			string str;
			wchar_t *unicodeStr = NULL;
			char *utf8Str = NULL;
			do
			{
				if(0 == strContent.size())
				{
					break;	
				}

				//首先先将GB2312编码转换为unicode编码
				if(NULL==setlocale(LC_ALL,"zh_CN.gb2312"))
				{	
					break;
				}

				//获取unicode编码长度
				int unicodeLen=mbstowcs(NULL,strContent.c_str(),0);
				if(unicodeLen<=0)	
				{
					break;
				}

				//字符串转换为unicode格式
				unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);
				mbstowcs(unicodeStr,strContent.c_str(),strContent.size());

				//将unicode编码转换为utf8编码
				if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))
				{
					break;
				}

				//获取utf8编码长度
				int nUtf8Len=wcstombs(NULL,unicodeStr,0);
				if(nUtf8Len<=0)	
				{
					break;
				}

				//字符串转换为utf8格式
				utf8Str=(char *)calloc(sizeof(char),nUtf8Len+1);
				wcstombs(utf8Str,unicodeStr,nUtf8Len);
				utf8Str[nUtf8Len] = 0;

				str = utf8Str;
			}while(0);

			//释放空间
			if(NULL  != unicodeStr)
			{
				free(unicodeStr);
				unicodeStr = NULL;
			}
			if(NULL  != utf8Str)
			{
				free(utf8Str);
				utf8Str = NULL;
			}

			return str;
		}

		string GetUcs2(const string & strContent)
		{

			string str;
			wchar_t *unicodeStr = NULL;
			char *gb2312Str = NULL;
			do
			{
				if(0 == strContent.size())
				{
					break;	
				}

				//首先先将UTF8编码转换为unicode编码
				if(NULL==setlocale(LC_ALL,"zh_CN.utf8"))
				{	
					break;
				}

				//获取unicode编码长度
				int unicodeLen=mbstowcs(NULL,strContent.c_str(),0);
				if(unicodeLen<=0)	
				{
					break;
				}

				//字符串转换为unicode格式
				unicodeStr=(wchar_t *)calloc(sizeof(wchar_t),unicodeLen+1);
				mbstowcs(unicodeStr,strContent.c_str(),strContent.size());

				//将unicode编码转换为gb2312编码
				if(NULL==setlocale(LC_ALL,"zh_CN.gb2312"))
				{
					break;
				}

				//获取gb2312编码长度
				int nGb2312Len=wcstombs(NULL,unicodeStr,0);
				if(nGb2312Len<=0)	
				{
					break;
				}

				//字符串转换为utf8格式
				gb2312Str=(char *)calloc(sizeof(char),nGb2312Len+1);
				wcstombs(gb2312Str,unicodeStr,nGb2312Len);
				gb2312Str[nGb2312Len] = 0;

				str = gb2312Str;
			}while(0);

			//释放空间
			if(NULL  != unicodeStr)
			{
				free(unicodeStr);
				unicodeStr = NULL;
			}
			if(NULL  != gb2312Str)
			{
				free(gb2312Str);
				gb2312Str = NULL;
			}

			return str;
		}

		//转换成GB2312格式
		string GetGB2312(const string & strContent)
		{
			string str = strContent;
			return str;
		}

		long long GetTimeStamp()
		{
			long long lCurrentSystemTime = 0;

			struct timeval tv;
			gettimeofday(&tv,NULL); 
			lCurrentSystemTime = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000; 

			return lCurrentSystemTime;
		}

		string GetExeFileExistDir()
		{
#define   WORKPATH_MAX   1024 
			string strDir;  
			char szBuffer[WORKPATH_MAX];  
			int nLen = readlink( "/proc/self/exe",   (char*)szBuffer,   WORKPATH_MAX);  
			if(nLen < 0 || nLen >= WORKPATH_MAX)   
			{ 
				printf("readlink len:%d \n",nLen); 
				return   strDir;  
			}
			while(szBuffer[nLen] != '/' && nLen != 0)
			{
				szBuffer[nLen] = 0;
				nLen--;
			}
			if(0 <= nLen)
			{
				szBuffer[nLen] = '\0';
			}  
			strDir = szBuffer; 
			return   strDir;  
		}

		//获取本机MAC地址
		string GetLocalMacAdress()
		{
			string strMac;
			char mac[256] = {0};
			struct ifreq tmp;
			int sock_mac;
			char mac_addr[30];
			sock_mac = socket(AF_INET, SOCK_STREAM, 0);
			if( sock_mac == -1){
				return strMac;
			}
			memset(&tmp,0,sizeof(tmp));
			strncpy(tmp.ifr_name,"eth0",sizeof(tmp.ifr_name)-1 );
			if( (ioctl( sock_mac, SIOCGIFHWADDR, &tmp)) < 0 ){
				return strMac;
			}
			sprintf(mac_addr, "%02x:%02x:%02x:%02x:%02x:%02x",
				(unsigned char)tmp.ifr_hwaddr.sa_data[0],
				(unsigned char)tmp.ifr_hwaddr.sa_data[1],
				(unsigned char)tmp.ifr_hwaddr.sa_data[2],
				(unsigned char)tmp.ifr_hwaddr.sa_data[3],
				(unsigned char)tmp.ifr_hwaddr.sa_data[4],
				(unsigned char)tmp.ifr_hwaddr.sa_data[5]
			);
			close(sock_mac);
			memcpy(mac,mac_addr,strlen(mac_addr));
			strMac = mac;
			return strMac;
		}

		string GetLocalIP()
		{
			string strIp;
			int sfd,intr;
			struct ifreq buf[16];
			struct ifconf ifc;
			sfd = socket(AF_INET,SOCK_DGRAM,0);
			if(sfd < 0)
			{
				return strIp;
			}

			ifc.ifc_len = sizeof(buf);
			ifc.ifc_buf = (caddr_t)buf;
			if(ioctl(sfd,SIOCGIFCONF,(char*)&ifc))
			{
				return strIp;
			}
			intr = ifc.ifc_len / sizeof(struct ifreq);
			while(intr-- > 0 && ioctl(sfd,SIOCGIFADDR,(char*)&buf[intr]));
			close(sfd);
			char * pIp = inet_ntoa(((struct sockaddr_in*)(&buf[intr].ifr_addr))->sin_addr);
			strIp = pIp;
			return strIp;
		}

		//判断是否为目录
		int IS_DIR(const char* path)
		{
			struct stat st;
			lstat(path, &st);
			return S_ISDIR(st.st_mode);
		}

		//是不是数字
		int IsNumeric(const char* ccharptr_CharacterList)
		{
			for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
				if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
					return 0; // false
			return 1; // true
		}

		//intCaseSensitive=0大小写不敏感
		int strcmp_Wrapper(const char *s1, const char *s2, int intCaseSensitive)
		{
			if (intCaseSensitive)
				return !strcmp(s1, s2);
			else
				return !strcasecmp(s1, s2);
		}

		//intCaseSensitive=0大小写不敏感
		int strstr_Wrapper(const char* haystack, const char* needle, int intCaseSensitive)
		{
			if (intCaseSensitive)
				return (int) strstr(haystack, needle);
			else
				return (int) strcasestr(haystack, needle);
		}

		//If -1 = not found, if -2 = proc fs access error
		pid_t GetPIDbyName_implements(const char* cchrptr_ProcessName, int intCaseSensitiveness, int intExactMatch)
		{
			char chrarry_CommandLinePath[1024] ;
			char chrarry_NameOfProcess[1024] ;
			char* chrptr_StringToCompare = NULL ;
			pid_t pid_ProcessIdentifier = (pid_t) -1 ;
			struct dirent* de_DirEntity = NULL ;
			DIR* dir_proc = NULL ;

			int (*CompareFunction) (const char*, const char*, int) ;

			if (intExactMatch)
				CompareFunction = &strcmp_Wrapper;
			else
				CompareFunction = &strstr_Wrapper;


			dir_proc = opendir(PROC_DIRECTORY) ;
			if (dir_proc == NULL)
			{
				perror("Couldn't open the " PROC_DIRECTORY " directory") ;
				return (pid_t) -2 ;
			}

			// Loop while not NULL
			while ( (de_DirEntity = readdir(dir_proc)) )
			{
				if (de_DirEntity->d_type == DT_DIR)
				{
					if (IsNumeric(de_DirEntity->d_name))
					{
						strcpy(chrarry_CommandLinePath, PROC_DIRECTORY) ;
						strcat(chrarry_CommandLinePath, de_DirEntity->d_name) ;
						strcat(chrarry_CommandLinePath, "/cmdline") ;
						FILE* fd_CmdLineFile = fopen (chrarry_CommandLinePath, "rt") ; //open the file for reading text
						if (fd_CmdLineFile)
						{
							fscanf(fd_CmdLineFile, "%s", chrarry_NameOfProcess) ; //read from /proc/<NR>/cmdline
							fclose(fd_CmdLineFile); //close the file prior to exiting the routine

							if (strrchr(chrarry_NameOfProcess, '/'))
								chrptr_StringToCompare = strrchr(chrarry_NameOfProcess, '/') +1 ;
							else
								chrptr_StringToCompare = chrarry_NameOfProcess ;

							//printf("Process name: %s\n", chrarry_NameOfProcess);
							//这个是全路径，比如/bin/ls
							//printf("Pure Process name: %s\n", chrptr_StringToCompare );
							//这个是纯进程名，比如ls

							//这里可以比较全路径名，设置为chrarry_NameOfProcess即可
							if ( CompareFunction(chrptr_StringToCompare, cchrptr_ProcessName, intCaseSensitiveness) )
							{
								pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
								closedir(dir_proc) ;
								return pid_ProcessIdentifier ;
							}
						}
					}
				}
			}
			closedir(dir_proc) ;
			return pid_ProcessIdentifier ;
		}

		//简单实现
		pid_t GetPIDbyName_Wrapper(const char* cchrptr_ProcessName)
		{
			return GetPIDbyName_implements(cchrptr_ProcessName, 0,0);//大小写不敏感
		}

		bool IsProcessorExist(string strProcessorName)
		{
			bool bSuccess = false;

			//获取PID
			pid_t pid = GetPIDbyName_Wrapper(strProcessorName.c_str());
			if (0 < pid)
			{
				int nKillRst = kill(pid,0);
				if( 0 == nKillRst)
				{
					bSuccess = true;
				}
			}

			return bSuccess;
		}

		bool IsProcessorExist(int nProcessID)
		{
			bool bSuccess = false;
			if (0 < nProcessID)
			{
				int nKillRst = kill(nProcessID,0);
				if( 0 == nKillRst)
				{
					bSuccess = true;
				}
			}
			return bSuccess;
		}

		int CreateProcess(const char * cmdstring)
		{
			pid_t pid;
			int status;
			if(cmdstring == NULL)
			{
				return (-1);
			}

			if((pid = fork())<0){
				status = -1;
			}
			else if(pid == 0){
				status = execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
				//LOG4CPLUS_ERROR(Logger::getInstance(LOG_MODEL_AUC),"execl commad: " << cmdstring << " failed!");
				exit(127); //子进程正常执行则不会执行此语句
			}
			else{
				status = pid;
			}
			return status;
		}

		int OpenProcessor(string strProcessorName,char * sParam,int nUnitID,int & nProcessorID,bool bIsShowWindow)
		{
			int nCreateStatus = CreateProcess(sParam);
			if (0 >= nCreateStatus) 
			{
				//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"Open AlgoUnit:" << nUnitID << " failed! process name:" << strProcessorName);
				return -1;
			}
			else
			{
				nProcessorID = nCreateStatus;
				//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"Open AlgoUnit:" << nUnitID << " success! process name:" << strProcessorName);
				return 0;
			}
		}

		void TerminateProcessor(string strProcessorName)
		{
			//获取PID
			pid_t pid = GetPIDbyName_Wrapper(strProcessorName.c_str());
			if (0 < pid)
			{
				int nKillRst = kill(pid,0);
				if( 0 == nKillRst)
				{
					nKillRst = kill(pid,SIGKILL);
				}
			}
			return;
		}

		void TerminateProcessor(int nProcessID)
		{
			if (0 < nProcessID)
			{
				int nKillRst = kill(nProcessID,0);
				if( 0 == nKillRst)
				{
					nKillRst = kill(nProcessID,SIGKILL);
				}
			}
			return;
		}

		//递归删除目录
		void DeleteDirectionRecursive(char * path)
		{
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						DeleteDirectionRecursive(temp);
					}
					else
					{
						//删除文件
						std::string strD = "rm ";
						strD += temp;
						strD += " -f -r";
						system(strD.c_str());
					}
				}

				//删除目录
				std::string strD = "rm ";
				strD += path;
				strD += " -f -r";
				system(strD.c_str());

				closedir(pdir);
			}
		}

		void DeleteDirection(string & strRootDir)
		{
			int nlen = 0;
			char strTempDir[1024];   
			//获取路径长度
			nlen = strRootDir.size();
			if (0 >= nlen)
			{
				return;
			}

			//去掉最后一个/
			strcpy(strTempDir, strRootDir.c_str());
			if(strTempDir[nlen - 1] == '/') strTempDir[nlen -1] = '\0';

			//如果是目录则递归删除
			if(IS_DIR(strTempDir))
			{
				DeleteDirectionRecursive(strTempDir);
			}
		}

		bool DeleteEmptyDirectoryExRecursive(char * path)
		{
			bool bHasFile = false;
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						bHasFile = DeleteEmptyDirectoryExRecursive(temp);
					}
					else
					{
						bHasFile = true;
						//printf("has file %s \n", temp);
					}
				}

				if(!bHasFile)
				{
					std::string strD = "rm ";
					strD += path;
					strD += " -f -r";
					system(strD.c_str());

					//printf("delete empty dir %s\n", path);
				}
				else
				{
					//printf("dir %s is not empty!\n", path);
				}

				closedir(pdir);
			}

			return bHasFile;
		}

		bool DeleteEmptyDirectoryEx(string pdir)
		{
			bool bRst = true;
			int len = 0;
			char temp[1024];   
			len = pdir.size();
			strcpy(temp, pdir.c_str());
			if(temp[len - 1] == '/') temp[len -1] = '\0';

			if(IS_DIR(temp))
			{
				bRst = DeleteEmptyDirectoryExRecursive(temp);
			}
			else  
			{
				//printf("%s\n", temp);
			}
			return bRst;
		}

		//删除文件
		void ForceDeleteFile(char * strFile)
		{
			std::string strD = "rm ";
			strD += strFile;
			strD += " -f -r";
			system(strD.c_str());
		}

		//遍历删除N天之前的文件
		bool DeleteLocalStoreFileRecursive(char* path, int nCircle)
		{
			bool bHasDelteFile = false;
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				bool bIsThisDirDel = false;
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						//删除空文件夹，非空则不删除，返回失败
						DeleteEmptyDirectoryEx(temp);			

						//删除N天之前的文件
						bHasDelteFile = DeleteLocalStoreFileRecursive(temp,nCircle);

						if (bHasDelteFile)
						{
							break;
						}
					}
					else
					{
						struct stat sFileStat;
						int nReadStatus =  stat(temp, &sFileStat);
						if(0 == nReadStatus)
						{
							//获取文件时间
							time_t tFileTime = sFileStat.st_mtime;
							tm * ptmFileTime = localtime(&tFileTime);
							ptmFileTime->tm_hour = 0;
							ptmFileTime->tm_min = 0;
							ptmFileTime->tm_sec = 0;
							tFileTime = mktime(ptmFileTime);
							//获取本地时间
							time_t tLocalTime = ::time(NULL);
							tm * ptmLocalTime = localtime(&tLocalTime);
							ptmLocalTime->tm_hour = 0;
							ptmLocalTime->tm_min = 0;
							ptmLocalTime->tm_sec = 0;
							tLocalTime = mktime(ptmLocalTime);
							//检查是否超出存储周期
							if (tLocalTime - tFileTime > nCircle * 24 * 3600)
							{
								ForceDeleteFile(temp);

								bHasDelteFile = true;
								bIsThisDirDel = true;
							}
						}
					}
				}

				//log
				if (bIsThisDirDel)
				{
					//LOG4CPLUS_INFO(Logger::getInstance(LOG_MODEL_AUC),"delete local store file dir:" << path);
				}

				closedir(pdir);
			}

			return bHasDelteFile;
		}

		//遍历删除N天之前的文件
		bool DeleteLocalStoreFile(string & strRoot, int nCircle)
		{
			bool bRst = false;
			int len = 0;
			char temp[1024];   
			len = strRoot.size();
			strcpy(temp, strRoot.c_str());
			if(temp[len - 1] == '/') temp[len -1] = '\0';

			if(IS_DIR(temp))
			{
				bRst = DeleteLocalStoreFileRecursive(temp,nCircle);
			}
			else  
			{
				//printf("%s\n", temp);
			}
			return bRst;
		}

		bool GetHistoryLocalFileInfoRecursive(char* path,string & strFileName,int nBeforeDay,tm & tFileCreateTime)
		{
			bool bHasFile = false;
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						//删除空文件夹，非空则不删除，返回失败
						DeleteEmptyDirectoryEx(temp);			

						//删除N天之前的文件
						bHasFile = GetHistoryLocalFileInfoRecursive(temp,strFileName,nBeforeDay,tFileCreateTime);

						if (bHasFile)
						{
							break;
						}
					}
					else
					{
						struct stat sFileStat;
						int nReadStatus =  stat(temp, &sFileStat);
						if(0 == nReadStatus)
						{
							tm tTempFileTime;
							//获取文件时间
							time_t tFileTime = sFileStat.st_ctime;
							tm * ptmFileTime = localtime(&tFileTime);
							ptmFileTime->tm_hour = 0;
							ptmFileTime->tm_min = 0;
							ptmFileTime->tm_sec = 0;
							tFileTime = mktime(ptmFileTime);
							tTempFileTime = *ptmFileTime;
							//获取本地时间
							time_t tLocalTime = ::time(NULL);
							tm * ptmLocalTime = localtime(&tLocalTime);
							ptmLocalTime->tm_hour = 0;
							ptmLocalTime->tm_min = 0;
							ptmLocalTime->tm_sec = 0;
							tLocalTime = mktime(ptmLocalTime);
							//检查是否超出存储周期
							if (tLocalTime - tFileTime > nBeforeDay * 24 * 3600)
							{
								strFileName = temp;
								tFileCreateTime = tTempFileTime;
								bHasFile = true;
								break;
							}
						}
					}
				}

				closedir(pdir);
			}

			return bHasFile;
		}

		bool GetHistoryLocalFileInfo(string & strRoot,string & strFileName,int nBeforeDay,tm & tFileCreateTime)
		{
			bool bRst = false;
			int len = 0;
			char temp[1024];   
			len = strRoot.size();
			strcpy(temp, strRoot.c_str());
			if(temp[len - 1] == '/') temp[len -1] = '\0';

			if(IS_DIR(temp))
			{
				bRst = GetHistoryLocalFileInfoRecursive(temp,strFileName,nBeforeDay,tFileCreateTime);
			}
			else  
			{
				//printf("%s\n", temp);
			}
			return bRst;
		}

		bool GetHistoryAlarmFileRecursive(char* path,string & strFileName)
		{
			bool bHasFile = false;
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						if (GetHistoryAlarmFileRecursive(temp,strFileName))
						{
							closedir(pdir);
							return true;
						}
						else
						{
							//删除空文件夹，非空则不删除，返回失败
							DeleteEmptyDirectoryEx(temp);			
						}
					}
					else
					{
						string fileName = pdirent->d_name;
						string tagAlarm = ".alarm";

						int nDifLength = fileName.size()-tagAlarm.size();

						if (nDifLength > 0) 
						{	
							if ((fileName.compare(fileName.size()-tagAlarm.length(), tagAlarm.length(), tagAlarm)) == 0)
							{
								strFileName = temp;
								closedir(pdir);

								return true;
							}
						}
					}
				}

				closedir(pdir);
			}

			return bHasFile;
		}

		bool GetHistoryAlarmFile(string & strRoot,string & strFileName)
		{
			bool bRst = false;
			int len = 0;
			char temp[1024];   
			len = strRoot.size();
			strcpy(temp, strRoot.c_str());
			if(temp[len - 1] == '/') temp[len -1] = '\0';

			if(IS_DIR(temp))
			{
				bRst = GetHistoryAlarmFileRecursive(temp,strFileName);
			}
			else  
			{
				//printf("%s\n", temp);
			}
			return bRst;
		}

		bool GetHistoryPicFileInfoRecursive(char* path,string & strFileName)
		{
			bool bHasFile = false;
			DIR *pdir = NULL;
			struct dirent *pdirent;
			char temp[1024];
			pdir = opendir(path);
			if(pdir)
			{
				while(pdirent = readdir(pdir))
				{
					if(strcmp(pdirent->d_name, ".") == 0
						|| strcmp(pdirent->d_name, "..") == 0)
						continue;

					sprintf(temp, "%s/%s", path, pdirent->d_name);

					if(IS_DIR(temp))
					{
						if (GetHistoryPicFileInfoRecursive(temp,strFileName))
						{
							closedir(pdir);
							return true;
						}
						else
						{
							//删除空文件夹，非空则不删除，返回失败
							DeleteEmptyDirectoryEx(temp);			
						}
					}
					else
					{
						string fileName = pdirent->d_name;
						string tagAlarm = ".dat";

						int nDifLength = fileName.size()-tagAlarm.size();

						if (nDifLength > 0) 
						{	
							if ((fileName.compare(fileName.size()-tagAlarm.length(), tagAlarm.length(), tagAlarm)) == 0)
							{
								strFileName = temp;
								closedir(pdir);

								return true;
							}
						}
					}
				}

				closedir(pdir);
			}

			return bHasFile;
		}

		bool GetHistoryPicFileInfo(string & strRoot,string & strFileName)
		{
			bool bRst = false;
			int len = 0;
			char temp[1024];   
			len = strRoot.size();
			strcpy(temp, strRoot.c_str());
			if(temp[len - 1] == '/') temp[len -1] = '\0';

			if(IS_DIR(temp))
			{
				bRst = GetHistoryPicFileInfoRecursive(temp,strFileName);
			}
			else  
			{
				//printf("%s\n", temp);
			}
			return bRst;
		}

		//设置系统时间
		bool SetDeviceSystemTime(struct tm & tSynTime)
		{
			char strTimeCmd[128];
			sprintf(strTimeCmd,"date -s \"%04d-%02d-%02d %02d:%02d:%02d\"",
				tSynTime.tm_year + 1900,
				tSynTime.tm_mon + 1,
				tSynTime.tm_mday,
				tSynTime.tm_hour,
				tSynTime.tm_min,
				tSynTime.tm_sec);
			int nRst = system(strTimeCmd);
			if(0 <= nRst)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//子进程信号回调函数
		void WaitChildProcessFunc(int signal)
		{
			int     status, chld_term_sig;
			pid_t   pid;

			pid = waitpid(0, &status, WNOHANG);

			// 子进程正常退出
			if (WIFEXITED(status) != 0)
			{
				return;
			}

			chld_term_sig = WTERMSIG(status);
			switch (chld_term_sig) {
	case SIGILL:
	case SIGTRAP:
	case SIGABRT:
	case SIGFPE:
	case SIGBUS:
	case SIGSEGV:
	case SIGXCPU:
		{
			//异常终止，不写日志是因为考虑到malloc等基础系统函数都是不可重入的，进程捕捉到信号时，会中断正在执行的指令序列;
			break;
		}
	case SIGQUIT:
	case SIGKILL:
	case SIGTERM:
		{
			//外界终止!不写日志是因为考虑到malloc等基础系统函数都是不可重入的，进程捕捉到信号时，会中断正在执行的指令序列;
			break;
		}
	default:
		break;
			}
		}

		//处理子进程结束消息
		void HandleChildProcessSignal()
		{
			//考虑到signal有不同的实现版本，这里强制实现了针对SIGCHLD消息的signal函数
			struct sigaction act;
			act.sa_handler = WaitChildProcessFunc;
			sigemptyset(&act.sa_mask);
			act.sa_flags = 0;
#ifdef SA_RESTART
			act.sa_flags |= SA_RESTART;
#endif
			sigaction(SIGCHLD,&act,NULL);
		}

#endif
	}


