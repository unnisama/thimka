#pragma once

#include <chrono>
#include <stdio.h>

class Timer{
private:
    std::chrono::_V2::steady_clock::time_point start;
    std::chrono::_V2::steady_clock::time_point prev;
public:
    Timer();
    float Step();
    float GetTime();
};