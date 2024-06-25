#include "Timer.h"
#include "MapManager.h"
#include "Core.h"
#include <Windows.h>

Timer* Timer::Instance = nullptr;

void Timer::StartTimer(int sTime)
{
    timer = sTime;
    start = clock();
    end = 0;
}

bool Timer::UpdateTimer()
 {
    if (start == 0) return false;
    end = clock();
    if (double(end - start) / CLOCKS_PER_SEC >= timer) 
    {
        Core::GetInstance()->GameEnd();
        return true;
    }

    return false;
}

void Timer::AddTime(int time)
{
    timer += time;
}
