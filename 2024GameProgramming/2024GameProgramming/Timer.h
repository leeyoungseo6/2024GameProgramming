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
	bool StartTimer(int sTime);

};