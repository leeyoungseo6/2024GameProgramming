#include <iostream>
#include "AstarNode.h"

_tagastarnode::_tagastarnode(int x, int y, bool isWalkable)
{
	X = x;
	Y = y;
	G = 0;
	H = 0;
	IsWalkable = isWalkable;
}

int _tagastarnode::GetDistanceCost(const _tagastarnode& node)
{
	int disX = abs(X - node.X);
	int disY = abs(Y - node.Y);

	return disX + disY;
}

void _tagastarnode::operator=(const _tagastarnode& b)
{
	X = b.X;
	Y = b.Y;
	G = b.G;
	H = b.H;
	IsWalkable = b.IsWalkable;
	ParentNode = b.ParentNode;
}

bool _tagastarnode::operator==(const _tagastarnode& b)
{
	return X == b.X && Y == b.Y;
}

bool _tagastarnode::operator!=(const _tagastarnode& b)
{
	return !(*this == b);
}