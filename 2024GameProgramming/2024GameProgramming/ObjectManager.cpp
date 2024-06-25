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

	_player->Update();
	ItemUpdate();
	EnemyUpdate();
}

void ObjectManager::ItemUpdate()
{
	int deltaTime = clock() - _prevTime;
	_prevTime = clock();

	if (_isSpeedReduced > 0)
	{
		_isSpeedReduced -= deltaTime;
		if (_isSpeedReduced <= 0)
		{
			_isSpeedReduced = 0;
			for (auto enemy : _enemyVec)
				enemy->SetMoveInterval(1000);
		}
	}

	if (_canAnyAttack > 0)
	{
		_canAnyAttack -= deltaTime;
		if (_canAnyAttack <= 0)
			_canAnyAttack = 0;
	}
}

void ObjectManager::EnemyUpdate()
{
	POS playerPos = _player->GetPos();
	POS playerDir = _player->GetDirection();

	for (auto iter = _enemyVec.begin(); iter < _enemyVec.end(); iter++)
	{
		POS enemyPos = (*iter)->GetPos();
		POS enemyDir = (*iter)->GetDirection();
		if (playerPos + playerDir == enemyPos)
		{
			if (-playerDir != enemyDir || _canAnyAttack)
			{
				// ¿¡³Ê¹Ì »ç¸Á
				(*iter)->Die();
				delete (*iter);
				iter = _enemyVec.erase(iter);
				SpawnItem(enemyPos);

				if (_enemyVec.empty())
				{
					Core::GetInstance()->Render();
					Sleep(1000);
					PlayerDie();
					ClearItem();
					MapManager::GetInstance()->NextStage();
					return;
				}
			}
			else
			{
				Core::GetInstance()->Render();
				PlayerDie();
				Sleep(1000);
				EnemyDie();
				ClearItem();
				return;
			}
		}

		if (iter == _enemyVec.end()) return;
		(*iter)->Update();

		if (playerPos == (*iter)->GetPos())
		{
			Core::GetInstance()->Render();
			PlayerDie();
			Sleep(1000);
			EnemyDie();
			ClearItem();
			return;
		}
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
	int rd = rand() % 35;
	if (rd < 100)
	{
		rd = rand() % 3;
		if (rd < 1)
			_itemVec.push_back(new PlusTimeItem(spawnPos));
		else if (rd < 2)
			_itemVec.push_back(new ReduceSpeedItem(spawnPos));
		else if (rd < 3)
			_itemVec.push_back(new AnyAttackItem(spawnPos));
	}
}

void ObjectManager::SpawnItem(const POS& spawnPos, OBJ_TYPE type)
{
	switch (type)
	{
	case OBJ_TYPE::PLUSTIMEITEM: 
		_itemVec.push_back(new PlusTimeItem(spawnPos));
		break;
	case OBJ_TYPE::REDUCEDSPEEDITEM:
		_itemVec.push_back(new ReduceSpeedItem(spawnPos));
		break;
	case OBJ_TYPE::ANYATTACKITEM: 
		_itemVec.push_back(new AnyAttackItem(spawnPos));
		break;
	}
}

void ObjectManager::GetItem(const POS& pos)
{
	for (auto iter = _itemVec.begin(); iter < _itemVec.end(); iter++)
	{
		if ((*iter)->GetPos() == pos)
		{
			(*iter)->GetItem();
			delete (*iter);
			iter = _itemVec.erase(iter);
			break;
		}
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
	_canAnyAttack = AnyAttackItem::duration;
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

void ObjectManager::ClearItem()
{
	for (auto item : _itemVec)
	{
		LayerMask::GetInstance()->RemoveMask(item->GetPos(), Layer::Item);
		SortingLayer::GetInstance()->RemoveLayer(item->GetPos(), SortingLayerID::Agent);
	}
	_itemVec.clear();
}
