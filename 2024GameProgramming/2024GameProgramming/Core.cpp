#include "Core.h"
#include "ObjectManager.h"
#include "Timer.h"
Core* Core::pInst = nullptr;

bool Core::Init()
{
	srand((unsigned int)time(NULL));
	CursorVisible(false, 1);
	if (!Title::GetInstance()->Init()) {
		return false;
	}
	AStarPathFinder::GetInstance()->Init();
	ObjectManager::GetInstance()->Init();
	ObjectManager::GetInstance()->SpawnItem({ 3, 3 });
	MapManager::GetInstance()->Init();
	LayerMask::GetInstance()->Init();
	return true;
}

void Core::Run()
{
	if (Init()) {
		while (true)
		{
			Update();
			Gotoxy(0, 0);
			Render();
			FrameSync(60);
		}
	}
	system("cls");
}

void Core::Update()
{
	ObjectManager::GetInstance()->Update();
	Timer::GetInstance()->UpdateTimer();
}

void Core::Render()
{
	MapManager::GetInstance()->Render();
	Timer::GetInstance()->Render();
	ObjectManager::GetInstance()->Render();
}

void Core::GameEnd()
{
	ObjectManager::GetInstance()->PlayerDie();
	ObjectManager::GetInstance()->EnemyDie();
}

void Core::FrameSync(unsigned int frameRate)
{
	clock_t oldTime = clock();
	clock_t curTime;

	while (true)
	{
		curTime = clock();
		if (curTime - oldTime > 1000 / frameRate)
		{
			oldTime = curTime;
			break;
		}
	}
}
