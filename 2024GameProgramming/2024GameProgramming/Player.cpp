#include "Player.h"

Player::Player(POS pos)
	: Object(pos, 'a', Layer::Default, SortingLayerID::Agent)
{
	_dir = POS::zero;
	_prevPos = POS::zero;
	_isDead = false;
}

void Player::Update()
{
	if (_isDead) return;
	POS dir = POS::zero;

	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case 'w':
		case 'W':
			dir = POS::up;
			break;
		case 'a':
		case 'A':
			dir = POS::left;
			break;
		case 's':
		case 'S':
			dir = POS::down;
			break;
		case 'd':
		case 'D':
			dir = POS::right;
			break;
		}
	}

	if (dir != POS::zero)
	{
		_dir = dir;
		Move(dir);
	}
}

void Player::Move(const POS dir)
{
	PPOS hit = new POS;
	if (Raycast(_pos, dir, hit, MAP_HEIGHT, 1 << (int)Layer::Enemy | 1 << (int)Layer::Wall))
	{
		_prevPos = _pos;
		POS nextPos = *hit - dir;
		LayerMask::GetInstance()->Move(_pos, nextPos, _layer);
		SortingLayer::GetInstance()->Move(_pos, nextPos, _sortingLayer);
		_pos = nextPos;
	}
	delete hit;
}

void Player::Render()
{
	if (_isDead) return;
	SetColor((int)COLOR::LIGHT_YELLOW);
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡Ý";
	SetColor();
}

void Player::Die()
{
	_isDead = true;
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
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
