#ifndef _NET_COMMDEF_H
#define _NET_COMMDEF_H

#include <string>
using std::string;

typedef void(*OnEventUserIOStatus)(int nStatus, char* szUserID);
int DealMouseAndKeyboard(string strContent);

#endif