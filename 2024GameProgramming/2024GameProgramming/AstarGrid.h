#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "define.h"
#include "Object.h"
#include "AStarNode.h"

class AStarGrid
{
public:
	void CreateGrid();
	AStarNode* GetNode(const POS& pos);
	vector<AStarNode*> GetOpenList(const AStarNode& node);

private:
	AStarNode* _grid[MAP_HEIGHT][MAP_WIDTH];
};