#pragma once
#include "Object.h"
#include "AstarPathFinder.h"
#include "LayerMask.h"
#include "console.h"

class Enemy : public Object
{
public:
	Enemy(POS pos);
	void Update() override;
	void Render() override;
	void SetDestination(POS targetPos);
private:
	stack<POS> _targetPath;
	POS _targetPos;

	clock_t _lastMovedTime;
};