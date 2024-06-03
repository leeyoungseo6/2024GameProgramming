#pragma once
#include <Windows.h>
class Object
{
public:
	Object(POINT pos, char symbol);
	virtual void Update() abstract;
	virtual void Render();
protected:
	POINT _pos;
	char _symbol;
};

class Enemy : public Object
{
public:
	Enemy(POINT pos);
	virtual void Update() override;
	void Render() override;
};