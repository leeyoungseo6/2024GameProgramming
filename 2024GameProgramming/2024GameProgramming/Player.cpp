#include "Player.h"
#include "MapManager.h"

Player::Player(POS pos)
	: Object(pos, 'a')
{
	_dir = { 0, 1 };
}

void Player::Update()
{
	Move();
}

void Player::Render()
{

}

void Player::Move()
{
	PPOS hit = new POS;
	if (Raycast(_pos, _dir, hit, 1 << (int)Layer::Enemy | 1 << (int)Layer::Wall))
	{
		_pos = *hit;
		cout << "¼º°ø";
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
