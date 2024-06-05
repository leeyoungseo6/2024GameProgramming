#pragma once
#include <Windows.h>
#include "console.h"
#include "Player.h"
#include "Enemy.h"

class Core
{
private:
	Core();
	~Core();
public:
	bool Init();
	void Run();
private:
	void Update();
	void Render();
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
	Player* _player;
	Enemy* _enemy;
};

