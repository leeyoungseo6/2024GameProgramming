#pragma once
#include <math.h>

class AStarNode
{
public:
	AStarNode();
	AStarNode(int x, int y, bool isWalkable);
public:
	int X, Y;
	int G, H;
	__declspec(property(get = f)) int F;
	int f() { return G + H; }

	bool IsWalkable;
	AStarNode* ParentNode;

public:
	int GetDistanceCost(const AStarNode& neighbor);

	void operator =(const AStarNode& b);
	bool operator ==(const AStarNode& b);
	bool operator !=(const AStarNode& b);
};