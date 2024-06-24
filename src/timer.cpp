#include "timer.h"

Timer::Timer()
{
    prev = std::chrono::steady_clock::now();
    start = prev;
}

float Timer::Step()
{
    auto current = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = current - prev;
    prev = current;
    return diff.count();
}

float Timer::GetTime()
{
    auto current = std::chrono::steady_clock::now();
    std::chrono::duration<float> diff = current - start;
    return diff.count();
}
