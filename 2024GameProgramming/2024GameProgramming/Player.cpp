#include "Player.h"


Player::Player(POS pos)
	: Object(pos, 'a')
{
	_dir = { 0, 0 };
}

void Player::Update()
{
	if (GetAsyncKeyState('W') & 0x8000)
		Move({ 0, -1 });
	else if (GetAsyncKeyState('A') & 0x8000)
		Move({ -1, 0 });
	else if (GetAsyncKeyState('S') & 0x8000)
		Move({ 0, 1 });
	else if (GetAsyncKeyState('D') & 0x8000)
		Move({ 1, 0 });
}

void Player::Render()
{
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡Ý";
}

void Player::Move(const POS dir)
{
	PPOS hit = new POS;
	if (Raycast(_pos, dir, hit, 1 << (int)Layer::Enemy | 1 << (int)Layer::Wall))
	{
		_pos = *hit - dir;
	}
	delete hit;
}

bool Player::Raycast(const POS& origin, const POS& dir, PPOS hit, int layer)
{
	*hit = origin;
	while (0 <= hit->x && hit->x <= MAP_WIDTH - 2
		&& 0 <= hit->y && hit->y <= MAP_HEIGHT - 1)
	{
		if (LayerMask::GetInstance()->Mask(*hit) & layer)
			return true;
		*hit += dir;
	}

	*hit = origin;
	return false;
}
