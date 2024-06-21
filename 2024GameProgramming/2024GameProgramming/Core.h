#pragma once
#include <Windows.h>
#include "console.h"
#include "Player.h"
#include "Enemy.h"
#include "AstarPathFinder.h"
#include "MapManager.h"
#include "Title.h"

class Core
{
private:
	Core() = default;
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
public:
	void SpawnPlayer(POS spawnPos);
	void SpawnEnemy(POS spawnPos);
private:
	static Core* pInst;
	Player* _player;
	vector<Enemy*> _enemyVec;
};

