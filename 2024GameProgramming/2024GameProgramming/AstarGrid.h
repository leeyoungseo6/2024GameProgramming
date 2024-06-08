#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "define.h"
#include "Object.h"
#include "AstarNode.h"

class AStarGrid
{
public:
	void CreateGrid();
	PAStarNode GetNode(const POS& pos);
	vector<PAStarNode> GetOpenList(const AStarNode& node);

private:
	PAStarNode _grid[MAP_HEIGHT][MAP_WIDTH];
};