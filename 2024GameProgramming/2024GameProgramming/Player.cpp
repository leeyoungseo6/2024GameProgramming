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
	Move();
}

void Player::Move()
{
	_dir = POS::zero;
	fflush(stdin);
	if (GetAsyncKeyState('W') & 0x0001) _dir = POS::up;
	else if (GetAsyncKeyState('A') & 0x0001) _dir = POS::left;
	else if (GetAsyncKeyState('S') & 0x0001) _dir = POS::down;
	else if (GetAsyncKeyState('D') & 0x0001) _dir = POS::right;
	else return;

	RaycastHit hit;
	if (Raycast(_pos, _dir, &hit, MAP_HEIGHT, (1 << (int)Layer::Wall) | (1 << (int)Layer::Enemy)))
	{
		if (hit.layer == (int)Layer::Enemy)
			PlaySFX(TEXT("enemyDie.wav"));
		else if (hit.distance > 0)
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
	SetColor((int)COLOR::LIGHT_YELLOW);
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡Ý";
	SetColor();
}

void Player::Die()
{
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
}

bool Player::Raycast(const POS& origin, const POS& dir, RaycastHit* hit, int maxDistance, int layer)
{
	hit->point = origin;
	hit->distance = -1;
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
