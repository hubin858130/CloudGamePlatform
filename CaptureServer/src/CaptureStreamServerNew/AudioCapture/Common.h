
/*
*	author: zyb
*   \brief Common Macro
*/

#pragma once

#ifndef IS_NULLPTR
#define IS_NULLPTR(ptr)		(nullptr == (ptr))
#endif
#ifndef NOT_NULLPTR
#define NOT_NULLPTR(ptr)	(nullptr != (ptr))
#endif
#ifndef IS_TRUE
#define IS_TRUE(isTrue)		(true == (isTrue))
#endif
#ifndef IS_FALSE
#define IS_FALSE(isFalse)	(false == (isFalse))
#endif
#ifndef SafDelete_A
#define SafDelete_A(ptr)	if(NOT_NULLPTR(ptr)){ delete[] (ptr); (ptr) = nullptr; }
#endif
#ifndef SafRelease
#define SafRelease(ptr)		if(NOT_NULLPTR(ptr)){ (ptr)->Release(); (ptr) = nullptr; }
#endif
#ifndef SafCloseHandle
#define SafCloseHandle(handle)	if(NOT_NULLPTR(handle)){ CloseHandle(handle); (handle) = nullptr; }
#endif

#include <wtypes.h>