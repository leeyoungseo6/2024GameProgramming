#include "AStarGrid.h"

void AStarGrid::CreateGrid()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH - 1; j++)
		{
			_grid[i][j] = new AStarNode(j, i, true);
		}
	}
}

AStarNode* AStarGrid::GetNode(const POS& pos)
{
	return _grid[pos.y][pos.x];
}

vector<AStarNode*> AStarGrid::GetOpenList(const AStarNode& node)
{
	vector<AStarNode*> openList;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int clampedX = std::clamp(node.X + i, 0, MAP_WIDTH - 1);
			int clampedY = std::clamp(node.Y + j, 0, MAP_HEIGHT - 1);
			if ((i + j == -1 || i + j == 1) && _grid[clampedY][clampedX]->IsWalkable
				&& MapManager::GetInstance()->CheckRoad({ clampedX, clampedY }))
			{
				openList.push_back(_grid[clampedY][clampedX]);
			}
		}
	}

	return openList;
}
