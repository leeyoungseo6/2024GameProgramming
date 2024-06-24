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
	void SetDestination(PPOS targetPos);
	const POS& GetDirection() { return _moveDir; };
	void SetMoveInterval(const int& value);
private:
	void Move();
private:
	stack<POS> _targetPath;
	PPOS _targetPos;
	POS _nextPos;
	POS _moveDir;
	int _moveInterval;

	clock_t _lastMovedTime;
};