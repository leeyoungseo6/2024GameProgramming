#pragma once
#include <Windows.h>

typedef struct _tagpos
{
	int x;
	int y;

	_tagpos&& operator+(const _tagpos& b)
	{
		return { x + b.x, y + b.y };
	}
	_tagpos&& operator-(const _tagpos& b)
	{
		return { x - b.x, y - b.y };
	}
	_tagpos&& operator+=(const _tagpos& b)
	{
		return { x += b.x, y += b.y };
	}
} POS, *PPOS;

class Object
{
public:
	Object(POS pos, char symbol);
	virtual void Update() abstract;
	virtual void Render() {};
protected:
	POS _pos;
	char _symbol;
};