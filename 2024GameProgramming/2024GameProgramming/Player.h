#pragma once
#include <conio.h>
#include <math.h>
#include "Object.h"

struct RaycastHit
{
	POS point;
	int distance;
	int layer;
};

class Player : public Object
{
public:
	Player(POS pos);
	void Update() override;
	void Render() override;
	void Die();

	void Move();
	bool Raycast(const POS& origin, const POS& dir, RaycastHit* hit, int maxDistance, int layer);
	const POS& GetDirection() { return _dir; };
private:
	POS _dir;
	bool _isDead;
};
