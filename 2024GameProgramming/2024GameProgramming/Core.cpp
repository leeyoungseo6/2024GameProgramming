#include "Core.h"

Core* Core::pInst = nullptr;

bool Core::Init()
{
	CursorVisible(false, 1);
	if (!Title::GetInstance()->Init()) {
		return false;
	}
	AstarPathFinder::GetInstance()->Init();
	MapManager::GetInstance()->Init();
	LayerMask::GetInstance()->Init();
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
	if (_player == nullptr) return;
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
				// 플레이어 사망
				_player->Die();
				delete _player;
				_player = nullptr;
				for (auto enemy : _enemyVec)
				{
					enemy->Die();
					delete enemy;
				}
				_enemyVec.clear();
				MapManager::GetInstance()->RetryCurrentStage();
				return;
			}
			else
			{
				// 에너미 사망
				(*iter)->Die();
				delete (*iter);
				iter = _enemyVec.erase(iter);

				if (_enemyVec.empty())
				{
					_player->Die();
					delete _player;
					_player = nullptr;
					MapManager::GetInstance()->NextStage();
					//MapManager::GetInstance()->LoadMap("stage-2.txt");
					return;
				}
			}
		}

		if (iter == _enemyVec.end()) return;
		(*iter)->SetDestination(playerPos);
		(*iter)->Update();

		if (playerPos == (*iter)->GetPos())
		{
			// 플레이어 사망
			_player->Die();
			delete _player;
			_player = nullptr;
			for (auto enemy : _enemyVec)
			{
				enemy->Die();
				delete enemy;
			}
			_enemyVec.clear();
			MapManager::GetInstance()->RetryCurrentStage();
			return;
		}
	}
}

void Core::Render()
{
	MapManager::GetInstance()->Render();
	if (_player != nullptr) 
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

void Core::SpawnPlayer(POS spawnPos)
{
	_player = new Player(spawnPos);
}

void Core::SpawnEnemy(POS spawnPos)
{
	_enemyVec.push_back(new Enemy(spawnPos));
}
