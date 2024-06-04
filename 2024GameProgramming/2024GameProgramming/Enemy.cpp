#include "Enemy.h"

Enemy::Enemy(POINT pos)
	: Object(pos, 'a')
{
	_targetPos = { -1, -1 };
	_targets = false;
}

void Enemy::Update()
{
	if (_targets == false)
	{
		stack<POINT> path = AstarPathFinder::GetInstance()->GetPath(_pos, {0, 0});
		while (path.empty() == false)
		{
			_pos = path.top();
			cout << path.top().x << " " << path.top().y << endl;
			path.pop();
		}

		_targets = true;
	}
}

void Enemy::Render()
{

}