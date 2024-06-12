#include "Enemy.h"

Enemy::Enemy(POS pos)
	: Object(pos, 'a')
{
	_targetPos = { -1, -1 };
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
			_pos = _targetPath.top();
			LayerMask::GetInstance()->Move(_pos, _targetPath.top(), Layer::Enemy);
			_targetPath.pop();
		}
	}
}

void Enemy::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡â";
}

void Enemy::SetDestination(POS targetPos)
{
	if (_targetPos == targetPos) return;
	_targetPos = targetPos;
	_targetPath = AstarPathFinder::GetInstance()->GetPath(_pos, targetPos);
}