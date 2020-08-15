/*
* \copyright
 * CopyRight 1993-2016 NVIDIA Corporation.  All rights reserved.
 * NOTICE TO LICENSEE: This source code and/or documentation ("Licensed Deliverables")
 * are subject to the applicable NVIDIA license agreement
 * that governs the use of the Licensed Deliverables.
 */

#pragma once

#include <windows.h>

// Simple timer class, measures time in milliseconds
class Timer
{
public:
    // Constructs the timer and starts timing.
    Timer();
    ~Timer();

    // Reset the starting point to now.
    void reset();

    // Get the elapsed milliseconds since the starting point.
    double now();

protected:
    LONGLONG m_llStartTick;
};