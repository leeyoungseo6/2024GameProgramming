#include "Core.h"
#include "ObjectManager.h"

Core* Core::pInst = nullptr;

bool Core::Init()
{
	srand((unsigned int)time(NULL));
	CursorVisible(false, 1);
	if (!Title::GetInstance()->Init()) {
		return false;
	}
	AstarPathFinder::GetInstance()->Init();
	MapManager::GetInstance()->Init();
	LayerMask::GetInstance()->Init();
	ObjectManager::GetInstance()->Init();
	ObjectManager::GetInstance()->SpawnItem({ 3, 1 });
	return true;
}

void Core::Run()
{
	Init();
	while (true)
	{
		Update();
		Gotoxy(0, 0);
		Render();
		FrameSync(60);
	}
}

void Core::Update()
{
	ObjectManager::GetInstance()->Update();
}

void Core::Render()
{
	MapManager::GetInstance()->Render();
	ObjectManager::GetInstance()->Render();
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
