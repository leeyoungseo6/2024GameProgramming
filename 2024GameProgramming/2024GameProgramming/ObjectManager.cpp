#include "ObjectManager.h"
#include "Core.h"
ObjectManager* ObjectManager::pInst = nullptr;

bool ObjectManager::Init()
{
	_prevTime = clock();
	return true;
}

void ObjectManager::Update()
{
	if (_player == nullptr) return;

	for (auto enemy : _enemyVec)
		if (_player->GetPos() == enemy->GetPos())
		{
			PlayerDie();
			Sleep(1000);
			EnemyDie();
			return;
		}

	_player->Update();
	POS playerPos = _player->GetPos();
	POS playerDir = _player->GetDirection();

	if (_isSpeedReduced > 0)
	{
		_isSpeedReduced -= (clock() - _prevTime);
		_prevTime = clock();
		if (_isSpeedReduced <= 0)
		{
			_isSpeedReduced = 0;
			for (auto enemy : _enemyVec)
				enemy->SetMoveInterval(1000);
		}
	}

	//if (_canAnyAttack > 0)
	//{
	//	_canAnyAttack -= 1 / 60;
	//	if (_canAnyAttack <= 0)
	//
	//}

	for (auto iter = _itemVec.begin(); iter < _itemVec.end(); iter++)
		if (playerPos == (*iter)->GetPos())
		{
			(*iter)->GetItem();
			delete (*iter);
			iter = _itemVec.erase(iter);
			break;
		}

	for (auto iter = _enemyVec.begin(); iter < _enemyVec.end(); iter++)
	{
		POS enemyPos = (*iter)->GetPos();
		if (playerPos + playerDir == enemyPos)
		{
			if (-playerDir == (*iter)->GetDirection())
			{
				Core::GetInstance()->Render();
				PlayerDie();
				Sleep(1000);
				EnemyDie();
				return;
			}
			else
			{
				// ¿¡³Ê¹Ì »ç¸Á
				(*iter)->Die();
				delete (*iter);
				iter = _enemyVec.erase(iter);

				if (_enemyVec.empty())
				{
					Core::GetInstance()->Render();
					Sleep(1000);
					PlayerDie();
					MapManager::GetInstance()->NextStage();
					return;
				}
			}
		}

		if (iter == _enemyVec.end()) return;
		(*iter)->Update();
	}
}

void ObjectManager::Render()
{
	if (_player != nullptr)
		_player->Render();
	for (auto enemy : _enemyVec)
		enemy->Render();
	for (auto item : _itemVec)
		item->Render();
}

void ObjectManager::SpawnPlayer(const POS& spawnPos)
{
	_player = new Player(spawnPos);
}

void ObjectManager::SpawnEnemy(const POS& spawnPos)
{
	Enemy* enemy = new Enemy(spawnPos);
	enemy->SetDestination(&_player->GetPos());
	_enemyVec.push_back(enemy);
}

void ObjectManager::SpawnItem(const POS& spawnPos)
{
	int rd = rand() % 100;
	if (rd < 100)
	{
		rd = rand() % 1;
		if (rd < 1)
			_itemVec.push_back(new ReduceSpeedItem(spawnPos));

	}
}

void ObjectManager::ReduceEnemySpeed()
{
	_isSpeedReduced = ReduceSpeedItem::duration;
	for (auto enemy : _enemyVec)
		enemy->SetMoveInterval(2000);
}

void ObjectManager::EnableAnyAttack()
{

}

void ObjectManager::PlayerDie()
{
	_player->Die();
	delete _player;
	_player = nullptr;
}

void ObjectManager::EnemyDie()
{
	for (auto enemy : _enemyVec)
	{
		enemy->Die();
		delete enemy;
	}

	_enemyVec.clear();

	MapManager::GetInstance()->RetryCurrentStage();
}
