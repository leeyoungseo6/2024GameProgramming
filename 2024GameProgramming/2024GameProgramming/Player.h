#pragma once
#include "Object.h"
#include "define.h"
#include "LayerMask.h"
#include "MapManager.h"
#include "console.h"

typedef struct _tagraycasthit
{
public:
	POS point;
	Layer layer;
} RaycastHit;

class Player : public Object
{
public:
	Player(POS pos);
	void Update() override;
	void Render() override;

	const POS& GetPos() { return _pos; };
	void Move(const POS dir);
	bool Raycast(const POS& origin, const POS& dir, PPOS hit, int layer);
private:
	POS _dir;
};
