#pragma once
#include "define.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "ReduceSpeedItem.h"

class ObjectManager
{
private:
	ObjectManager() = default;
	~ObjectManager() {};
public:
	bool Init();
	void Update();
	void Render();
	void SpawnPlayer(const POS& spawnPos);
	void SpawnEnemy(const POS& spawnPos);
	void SpawnItem(const POS& spawnPos);
	void ReduceEnemySpeed();
	void EnableAnyAttack();
private:
	void PlayerDie();
	void EnemyDie();
public:
	static ObjectManager* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new ObjectManager;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}
private:
	static ObjectManager* pInst;

	Player* _player;
	vector<Enemy*> _enemyVec;
	vector<Item*> _itemVec;
	int _isSpeedReduced;
	int _canAnyAttack;

	int _prevTime;
};