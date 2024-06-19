#include "Timer.h"

Timer* Timer::Instance = nullptr;

bool Timer::StartTimer(int sTime)
{
    clock_t start = clock();
    clock_t end = clock();

    while (true) {
        end = clock();
        if (double(end - start) / CLOCKS_PER_SEC >= sTime) {
            return true;
        }
    }
}
