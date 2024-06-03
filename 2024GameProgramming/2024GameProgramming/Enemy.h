#pragma once
#include "Object.h"
class Enemy : public Object
{
public:
	Enemy(POINT pos);
	virtual void Update() override;
	void Render() override;
private:
	POINT _targetPos;
};