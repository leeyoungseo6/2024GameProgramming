#include "Pos.h"
_tagpos _tagpos::zero = { 0, 0 };
_tagpos _tagpos::up = { 0, -1 };
_tagpos _tagpos::down = { 0, 1 };
_tagpos _tagpos::left = { -1, 0 };
_tagpos _tagpos::right = { 1, 0 };

_tagpos&& _tagpos::operator+(const _tagpos& b)
{
	return { x + b.x, y + b.y };
}

_tagpos&& _tagpos::operator-(const _tagpos& b)
{
	return { x - b.x, y - b.y };
}

_tagpos&& _tagpos::operator-()
{
	return { -x, -y };
}

_tagpos&& _tagpos::operator+=(const _tagpos& b)
{
	return { x += b.x, y += b.y };
}

bool _tagpos::operator==(const _tagpos& b)
{
	return x == b.x && y == b.y;
}

bool _tagpos::operator!=(const _tagpos& b)
{
	return !(*this==b);
}

bool _tagpos::operator==(_tagpos&& b)
{
	return x == b.x && y == b.y;
}

bool _tagpos::operator!=(_tagpos&& b)
{
	return !(*this==b);
}

bool operator==(const _tagpos& a, _tagpos&& b)
{
	return a.x == b.x && a.y == b.y;
}