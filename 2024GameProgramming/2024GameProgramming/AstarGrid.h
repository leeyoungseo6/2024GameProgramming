#pragma once
#include <vector>
#include "define.h"

typedef struct _tagastarnode
{
public:
	int X, Y;
	int G, H;

	bool IsWalkable;
	_tagastarnode* ParentNode;

	__declspec(property(get = f)) int F;
	int f() { return G + H; }
private:
} AstarNode, *PAstarNode;

class AstarGrid
{
public:
	void CreateGrid();
	vector<AstarNode>& GetOpenList(PAstarNode node);

private:
	AstarNode _grid[MAP_HEIGHT][MAP_WIDTH];
};