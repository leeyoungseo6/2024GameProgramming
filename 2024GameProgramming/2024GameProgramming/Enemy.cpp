#include "Enemy.h"

Enemy::Enemy(POS pos)
	: Object(pos, 'a', Layer::Enemy, SortingLayerID::Agent)
{
	_targetPos = { -1, -1 };
	_moveDir = { 0, 1 };
	_lastMovedTime = -9999;
}

void Enemy::Update()
{
	//cout << "Ãâ·Â" << endl;
	clock_t currentTime = clock();
	if (currentTime - _lastMovedTime >= 1000)
	{
		_lastMovedTime = currentTime;
		
		if (_targetPath.empty() == false)
		{
			LayerMask::GetInstance()->Move(_pos, _targetPath.top(), _layer);
			SortingLayer::GetInstance()->Move(_pos, _targetPath.top(), _sortingLayer);
			_pos = _targetPath.top();
			_targetPath.pop();
			_moveDir = _targetPath.top() - _pos;
		}
	}
}

void Enemy::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	if (_moveDir == POS{ 0, -1 })
		cout << "¡â";
	else if (_moveDir == POS{ -1, 0 })
		cout << "¢·";
	else if (_moveDir == POS{ 1, 0 })
		cout << "¢¹";
	else if (_moveDir == POS{ 0, 1 })
		cout << "¡ä";
}

void Enemy::Die()
{
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
}

void Enemy::SetDestination(POS targetPos)
{
	if (_targetPos == targetPos) return;
	_targetPos = targetPos;
	_targetPath = AstarPathFinder::GetInstance()->GetPath(_pos, targetPos);
}