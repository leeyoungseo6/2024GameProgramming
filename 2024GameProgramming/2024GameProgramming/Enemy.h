#pragma once
#include "Object.h"
#include "AstarPathFinder.h"
class Enemy : public Object
{
public:
	Enemy(POS pos);
	void Update() override;
	void Render() override;
private:
	POS _targetPos;
	bool _targets;
};