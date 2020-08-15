/*!
 * \copyright
 * CopyRight 1993-2016 NVIDIA Corporation.  All rights reserved.
 * NOTICE TO LICENSEE: This source code and/or documentation ("Licensed Deliverables")
 * are subject to the applicable NVIDIA license agreement
 * that governs the use of the Licensed Deliverables.
 */

#include "stdafx.h"
#include "Timer.h"

LONGLONG g_llPerfFrequency; 
bool g_timeInitialized=false;

#define QPC(Int64)  QueryPerformanceCounter((LARGE_INTEGER*)&Int64)  
#define QPF(Int64)  QueryPerformanceFrequency((LARGE_INTEGER*)&Int64)

Timer::Timer()
    : m_llStartTick(0)
{
    if(!g_timeInitialized)
    {
        QPF(g_llPerfFrequency);
        g_timeInitialized = true;
    }

    QPC(m_llStartTick);
}

Timer::~Timer()
{
}

void Timer::reset()
{
    QPC(m_llStartTick);
}

double Timer::now()
{
    LONGLONG now;
    QPC(now);
    return (((double)(now - m_llStartTick)/(double)g_llPerfFrequency) * 1000.0);
}