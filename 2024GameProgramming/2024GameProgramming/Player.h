#pragma once
#include <conio.h>
#include "Object.h"

class Player : public Object
{
public:
	Player(POS pos);
	void Update() override;
	void Render() override;
	void Die();

	void Move(const POS dir);
	bool Raycast(const POS& origin, const POS& dir, PPOS hit, int maxDistance, int layer);
	const POS& GetDirection() { return _dir; };
private:
	POS _dir;
	POS _prevPos;
	bool _isDead;
};
