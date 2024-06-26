#pragma once
#include <Windows.h>
#include "console.h"
#include "AstarPathFinder.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Title.h"
#include "Timer.h"

class Core
{
private:
	Core() = default;
	~Core();
public:
	bool Init();
	void Run();
	void Render();
	void GameEnd();
	bool FinishGame();
private:
	void Update();
	void FrameSync(unsigned int frameRate);
public:
	static Core* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new Core;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}
public:
	bool isAllClearStage = false;
private:
	static Core* pInst;
};

