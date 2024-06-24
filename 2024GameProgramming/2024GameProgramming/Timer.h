#pragma once
#include <ctime>
#include<iostream>

class Timer
{
private:
	Timer() = default;
public:
	static Timer* GetInstance() {
		if (Instance == nullptr) {
			Instance = new Timer();
		}
		return Instance;
	}
private:
	static Timer* Instance;
public:
	int timer = 0;
	clock_t start;
	clock_t end;
public:
	void StartTimer(int sTime);
	bool UpdateTimer();
};