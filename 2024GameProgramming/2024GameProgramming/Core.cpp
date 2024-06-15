#include "Core.h"

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
	_player = new Player({ 1, 1 });
	_enemyVec.push_back(new Enemy({ 1, 10 }));
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
	_player->Update();
	POS playerPos = _player->GetPos();
	POS playerDir = _player->GetDirection();
	for (auto iter = _enemyVec.begin(); iter < _enemyVec.end(); iter++)
	{
		POS enemyPos = (*iter)->GetPos();
		if (playerPos + playerDir == enemyPos)
		{
			if (-playerDir == (*iter)->GetDirection())
			{
				// ÇÃ·¹ÀÌ¾î »ç¸Á
				Gotoxy(50, 25);
				cout << "»ç¸Á";
			}
			else
			{
				// ¿¡³Ê¹Ì »ç¸Á
				(*iter)->Die();
				iter = _enemyVec.erase(iter);
			}
		}

		if (iter == _enemyVec.end()) return;
		(*iter)->SetDestination(playerPos);
		(*iter)->Update();

		if (playerPos == enemyPos)
		{
			// ÇÃ·¹ÀÌ¾î »ç¸Á
			Gotoxy(50, 25);
			cout << "»ç¸Á";
		}
	}
}

void Core::Render()
{
	MapManager::GetInstance()->Render();
	_player->Render();
	for (Enemy* enemy : _enemyVec)
		enemy->Render();
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
