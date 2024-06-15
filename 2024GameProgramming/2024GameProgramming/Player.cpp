#include "Player.h"

Player::Player(POS pos)
	: Object(pos, 'a', Layer::Default, SortingLayerID::Agent)
{
	_dir = { 0, 0 };
}

void Player::Update()
{
	if (_dir != POS{ 0, 0 })
	{
		_dir = { 0, 0 };
		return;
	}

	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case 'w':
		case 'W':
			_dir = { 0, -1 };
			break;
		case 'a':
		case 'A':
			_dir = { -1, 0 };
			break;
		case 's':
		case 'S':
			_dir = { 0, 1 };
			break;
		case 'd':
		case 'D':
			_dir = { 1, 0 };
			break;
		}
	}

	Move(_dir);
}

void Player::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡Ý";
}

void Player::Move(const POS dir)
{
	PPOS hit = new POS;
	if (Raycast(_pos, dir, hit, MAP_HEIGHT, 1 << (int)Layer::Enemy | 1 << (int)Layer::Wall))
	{
		POS nextPos = *hit - dir;
		LayerMask::GetInstance()->Move(_pos, nextPos, _layer);
		SortingLayer::GetInstance()->Move(_pos, nextPos, _sortingLayer);
		_pos = nextPos;
	}
	delete hit;
}

bool Player::Raycast(const POS& origin, const POS& dir, PPOS hit, int maxDistance, int layer)
{
	*hit = origin;
	while (0 <= hit->x && hit->x <= MAP_WIDTH - 2
		&& 0 <= hit->y && hit->y <= MAP_HEIGHT - 1 && maxDistance--)
	{
		if (LayerMask::GetInstance()->Mask(*hit) & layer)
			return true;
		*hit += dir;
	}

	*hit = origin;
	return false;
}
