#include "Player.h"

Player::Player(POS pos)
	: Object(pos, 'a')
{

}

void Player::Update()
{

	if (Raycast(_pos, _dir, ))
}

void Player::Render()
{

}

void Player::Move()
{

}

bool Player::Raycast(const POS& origin, const POS& dir, PPOS hit, char target)
{
	*hit = origin;
	while (true)
	{
		*hit += dir;
		if (hit->x < 0 || hit->x > MAP_WIDTH
			|| hit->y < 0 || hit->y > MAP_HEIGHT)
			break;

		if (/*Map[next.y][next.x] == target*/0)
			return true;
	}

	return false;
}
