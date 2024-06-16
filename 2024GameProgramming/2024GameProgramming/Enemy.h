#pragma once
#include <stack>
#include "define.h"
#include "Object.h"
#include "Pos.h"
#include "AstarPathFinder.h"

class Enemy : public Object
{
public:
	Enemy(POS pos);
	void Update() override;
	void Render() override;

	void Die();
	void SetDestination(POS targetPos);
	const POS& GetDirection() { return _moveDir; };
private:
	stack<POS> _targetPath;
	POS _targetPos;
	POS _moveDir;

	clock_t _lastMovedTime;
};