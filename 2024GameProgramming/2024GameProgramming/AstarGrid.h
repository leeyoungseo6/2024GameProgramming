#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "define.h"

typedef struct _tagastarnode
{
public:
	_tagastarnode();
	_tagastarnode(int x, int y, bool isWalkable)
		: X(x), Y(y), IsWalkable(isWalkable) {};
public:
	int X, Y;
	int G, H;
	__declspec(property(get = f)) int F;
	int f() { return G + H; }

	bool IsWalkable;
	_tagastarnode* ParentNode;

public:
	int GetDistanceCost(const _tagastarnode& neighbor)
	{
		int disX = abs(X - neighbor.X);
		int disY = abs(Y - neighbor.Y);

		if (disX > disY) return 14 * disY + 10 * (disX - disY);
		return 14 * disX + 10 * (disY - disX);
	}

	bool operator ==(const _tagastarnode& b)
	{
		return X == b.X && Y == b.Y;
	}
	bool operator !=(const _tagastarnode& b)
	{
		return !(*this == b);
	}
} AstarNode, *PAstarNode;

class AstarGrid
{
public:
	void CreateGrid();
	PAstarNode GetNode(POINT pos);
	vector<PAstarNode> GetOpenList(const AstarNode& node);

private:
	PAstarNode _grid[MAP_HEIGHT][MAP_WIDTH];
};