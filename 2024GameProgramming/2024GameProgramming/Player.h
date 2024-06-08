#pragma once
#include "Object.h"
#include "define.h"

typedef struct _tagraycasthit
{
public:
	POS point;
	char symbol;
};

class Player : public Object
{
public:
	Player(POS pos);
	void Update() override;
	void Render() override;

	POS GetPos() { return _pos; };
	void Move();
	bool Raycast(const POS& origin, const POS& dir, PPOS hit, char target);
private:
	POS _dir;
};
