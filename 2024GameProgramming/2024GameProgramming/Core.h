#pragma once
#include <Windows.h>
#include "console.h"
#include "AstarPathFinder.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Title.h"

class Core
{
private:
	Core() = default;
	~Core();
public:
	bool Init();
	void Run();
	void Render();
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
private:
	static Core* pInst;
};

