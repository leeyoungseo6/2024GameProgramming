#pragma once
#include "Object.h"
#include "AstarPathFinder.h"
class Enemy : public Object
{
public:
	Enemy(POINT pos);
	void Update() override;
	void Render() override;
private:
	POINT _targetPos;
	bool _targets;
};