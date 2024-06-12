#include "Core.h"
#include "console.h"
Core* Core::pInst = nullptr;

Core::Core()
{

}

bool Core::Init()
{
	CursorVisible(false, 1);
	AstarPathFinder::GetInstance()->Init();
	MapManager::GetInstance()->Init();
	LayerMask::GetInstance()->Init();
	_player = new Player({ 2, 1 });
	_enemy = new Enemy({ 2, 10 });
	return true;
}

void Core::Run()
{
	Init();
	while (true)
	{
		Update();
		Render();
		FrameSync(60);
	}
}

void Core::Update()
{
	_player->Update();
	_enemy->SetDestination(_player->GetPos());
	_enemy->Update();
}

void Core::Render()
{
	MapManager::GetInstance()->Render();
	_player->Render();
	_enemy->Render();
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
