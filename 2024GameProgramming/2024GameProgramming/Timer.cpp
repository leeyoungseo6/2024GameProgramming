#include "Timer.h"

Timer* Timer::Instance = nullptr;

void Timer::StartTimer(int sTime)
{
    time = sTime;
}

bool Timer::UpdateTimer()
{
    clock_t start = clock();
    clock_t end = clock();

    end = clock();
    if (double(end - start) / CLOCKS_PER_SEC >= time) {
        std::cout << "しいしししししししししししししししししししししししししししししししししししししししししししし";
        return true;
    }

    return false;
}

