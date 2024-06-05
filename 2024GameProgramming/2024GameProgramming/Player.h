#pragma once
#include "Object.h"
#include "define.h"

class Player : public Object
{
public:
	Player(POS pos);
	void Update() override;
	void Render() override;
	void Move();
	bool Raycast(const POS& origin, const POS& dir, PPOS hit, char target);
private:
	POS _dir;
};
