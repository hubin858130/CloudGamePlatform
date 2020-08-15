#pragma once
#include<string>
using std::string;

unsigned int IPStrToInt(const char *ip); //IP  string to  int
string GetExeFileExistDir();
string CreateGuidString(bool bFlag);
BOOL ReSetWindows(DWORD dwFlags, BOOL bForce);
string UrlEncode(string str);
string UrlDecode(string str);