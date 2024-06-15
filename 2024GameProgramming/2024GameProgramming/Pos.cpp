#include "Pos.h"

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