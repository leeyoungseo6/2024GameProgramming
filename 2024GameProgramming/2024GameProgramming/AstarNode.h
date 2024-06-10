#pragma once
#include <math.h>
#include "Object.h"
typedef struct _tagastarnode
{
public:
	_tagastarnode();
	_tagastarnode(int x, int y, bool isWalkable);
public:
	int X, Y;
	int G, H;
	__declspec(property(get = f)) int F;
	int f() { return G + H; }

	bool IsWalkable;
	_tagastarnode* ParentNode;

public:
	int GetDistanceCost(const _tagastarnode& neighbor);

	void operator =(const _tagastarnode& b);
	bool operator ==(const _tagastarnode& b);
	bool operator !=(const _tagastarnode& b);
} AStarNode, *PAStarNode;