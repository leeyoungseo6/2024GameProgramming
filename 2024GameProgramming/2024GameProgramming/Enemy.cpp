#include "Enemy.h"

Enemy::Enemy(POS pos)
	: Object(pos, 'a', Layer::Enemy, SortingLayerID::Agent)
{
	AStarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = false;
	_moveDir = POS::right;
	_lastMovedTime = clock();
	_moveInterval = 1000;
}

void Enemy::Update()
{
	Move();
}

void Enemy::Move()
{
	clock_t currentTime = clock();
	if (currentTime - _lastMovedTime >= 500)
	{
		_lastMovedTime = currentTime;

		if (_targetPath.empty() == false)
		{
			_moveDir = _nextPos - _pos;
			LayerMask::GetInstance()->Move(_pos, _nextPos, _layer);
			SortingLayer::GetInstance()->Move(_pos, _nextPos, _sortingLayer);
			AStarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = true;
			_pos = _nextPos;
			AStarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = false;
			_targetPath.pop();
		}

		_targetPath = AStarPathFinder::GetInstance()->GetPath(_pos, *_targetPos);
		if (_targetPath.size() > 0)
		{
			SortingLayer::GetInstance()->Move(_nextPos, _targetPath.top(), SortingLayerID::EnemyNext);
			_nextPos = _targetPath.top();
		}
	}
}

void Enemy::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	SetColor((int)COLOR::LIGHT_RED);
	if (_moveDir == POS::up)
		cout << (_moveInterval == 1000 ? "△" : "▲");
	else if (_moveDir == POS::left)
		cout << (_moveInterval == 1000 ? "◁" : "◀");
	else if (_moveDir == POS::right)
		cout << (_moveInterval == 1000 ? "▷" : "▶");
	else if (_moveDir == POS::down)
		cout << (_moveInterval == 1000 ? "▽" : "▼");

	if (_nextPos != POS::zero && SortingLayer::GetInstance()->Mask(_nextPos) <= (int)SortingLayerID::EnemyNext)
	{
		SetColor((int)COLOR::RED);
		Gotoxy(_nextPos.x * 2, _nextPos.y);
		cout << "ㆍ";
	}
	SetColor();
}

void Enemy::Die()
{
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
	SortingLayer::GetInstance()->RemoveLayer(_nextPos, SortingLayerID::EnemyNext);
	AStarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = true;
}

void Enemy::SetDestination(PPOS targetPos)
{
	_targetPos = targetPos;
	_targetPath = AStarPathFinder::GetInstance()->GetPath(_pos, *_targetPos);
	if (_targetPath.empty() == false)
	{
		_nextPos = _targetPath.top();
		_moveDir = _nextPos - _pos;
		SortingLayer::GetInstance()->Move(_nextPos, _nextPos, SortingLayerID::EnemyNext);
	}
}

void Enemy::SetMoveInterval(const int& value)
{
	_moveInterval = value;
}
