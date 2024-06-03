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