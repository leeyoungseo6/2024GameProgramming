#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include "define.h"
#include "MapManager.h"
#include "AStarNode.h"
#include "Pos.h"

class AStarGrid
{
public:
	void CreateGrid();
	AStarNode* GetNode(const POS& pos);
	vector<AStarNode*> GetOpenList(const AStarNode& node);

private:
	AStarNode* _grid[MAP_HEIGHT][MAP_WIDTH];
};