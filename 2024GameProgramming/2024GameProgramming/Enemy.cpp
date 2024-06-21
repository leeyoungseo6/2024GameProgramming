#include "Enemy.h"

Enemy::Enemy(POS pos)
	: Object(pos, 'a', Layer::Enemy, SortingLayerID::Agent)
{
	AstarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = false;
	_targetPos = { -1, -1 };
	_moveDir = { 0, 1 };
	_lastMovedTime = -9999;
}

void Enemy::Update()
{
	clock_t currentTime = clock();
	if (currentTime - _lastMovedTime >= 1000)
	{
		_lastMovedTime = currentTime;
		_targetPath = AstarPathFinder::GetInstance()->GetPath(_pos, _targetPos);
		
		if (_targetPath.empty() == false)
		{
			_moveDir = _targetPath.top() - _pos;
			LayerMask::GetInstance()->Move(_pos, _targetPath.top(), _layer);
			SortingLayer::GetInstance()->Move(_pos, _targetPath.top(), _sortingLayer);
			AstarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = true;
			_pos = _targetPath.top();
			AstarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = false;
			_targetPath.pop();

			if (_targetPath.size() > 0)
			{
				SortingLayer::GetInstance()->Move(_nextPos, _targetPath.top(), SortingLayerID::EnemyNext);
				_nextPos = _targetPath.top();
			}
		}
	}
}

void Enemy::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	SetColor((int)COLOR::LIGHT_RED);
	if (_moveDir == POS::up)
		cout << "△";
	else if (_moveDir == POS::left)
		cout << "◁";
	else if (_moveDir == POS::right)
		cout << "▷";
	else if (_moveDir == POS::down)
		cout << "▽";

	if (_nextPos != POS::zero)
		Gotoxy(_nextPos.x * 2, _nextPos.y);
	if (SortingLayer::GetInstance()->Mask(_nextPos) <= (int)SortingLayerID::EnemyNext)
		cout << "ㆍ";
	SetColor();
}

void Enemy::Die()
{
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
	SortingLayer::GetInstance()->RemoveLayer(_nextPos, SortingLayerID::EnemyNext);
	AstarPathFinder::GetInstance()->Grid.GetNode(_pos)->IsWalkable = true;
}

void Enemy::SetDestination(POS targetPos)
{
	_targetPos = targetPos;
}