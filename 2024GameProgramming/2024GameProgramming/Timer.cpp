#include "Timer.h"
#include "MapManager.h"
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
    end = clock();
    if (double(end - start) / CLOCKS_PER_SEC >= timer) 
    {
        //MapManager::GetInstance()->RetryCurrentStage();
        return true;
    }

    return false;
}