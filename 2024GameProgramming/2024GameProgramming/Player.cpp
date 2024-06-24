#include "Player.h"
#include "ObjectManager.h"
#include "mci.h"

Player::Player(POS pos)
	: Object(pos, 'a', Layer::Default, SortingLayerID::Agent)
{
	_dir = POS::zero;
	_isDead = false;
}

void Player::Update()
{
	if (_isDead) return;
	Move();
}

void Player::Move()
{
	_dir = POS::zero;
	if (_kbhit())
	{
		char c = _getch();
		switch (c)
		{
		case 'W':
		case 'w': _dir = POS::up; break;

		case 'A':
		case 'a': _dir = POS::left; break;

		case 'S':
		case 's': _dir = POS::down; break;

		case 'D':
		case 'd': _dir = POS::right; break;
		}
	}
	else return;

	RaycastHit hit;
	if (Raycast(_pos, _dir, &hit, MAP_HEIGHT, (1 << (int)Layer::Wall) | (1 << (int)Layer::Enemy)))
	{
		if (hit.layer == (int)Layer::Enemy)
			PlaySFX(TEXT("enemyDie.wav"));
		else
			PlaySFX(TEXT("wallKick.wav"));
		POS nextPos = hit.point - _dir;
		LayerMask::GetInstance()->Move(_pos, nextPos, _layer);
		SortingLayer::GetInstance()->Move(_pos, nextPos, _sortingLayer);

		if (Raycast(_pos, _dir, &hit, hit.distance, 1 << (int)Layer::Item))
			ObjectManager::GetInstance()->GetItem(hit.point);

		_pos = nextPos;
	}
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

bool Player::Raycast(const POS& origin, const POS& dir, RaycastHit* hit, int maxDistance, int layer)
{
	hit->point = origin;
	hit->distance = 0;
	while (0 <= hit->point.x && hit->point.x <= MAP_WIDTH - 2
		&& 0 <= hit->point.y && hit->point.y <= MAP_HEIGHT - 1 && maxDistance--)
	{
		int result = LayerMask::GetInstance()->Mask(hit->point) & layer;
		if (result)
		{
			hit->layer = (int)log2(result);
			return true;
		}
		hit->point = hit->point + dir;
		hit->distance += 1;
	}

	hit->point = origin;
	hit->distance = 0;
	return false;
}
