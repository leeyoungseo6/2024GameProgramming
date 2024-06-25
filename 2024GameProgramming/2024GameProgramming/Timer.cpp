#include "Timer.h"
#include "MapManager.h"
#include "Core.h"
#include "console.h"
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

void Timer::Render()
{
    COORD Resoulution = GetConsoleResolution();
    int x = Resoulution.X / 20;
    int y = Resoulution.Y / 3;

    Gotoxy(0, 0);
    cout << "남은 시간 : " << timer - (end - start) / CLOCKS_PER_SEC << "초    ";
}

void Timer::AddTime(int time)
{
    timer += time;
}
