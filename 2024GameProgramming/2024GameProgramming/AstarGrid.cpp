#include "AstarGrid.h"

void AstarGrid::CreateGrid()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_grid[i][j] = new AstarNode(j, i, true);
		}
	}
}

PAstarNode AstarGrid::GetNode(const POS& pos)
{
	return _grid[pos.y][pos.x];
}

vector<PAstarNode> AstarGrid::GetOpenList(const AstarNode& node)
{
	vector<PAstarNode> openList;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int clampedX = std::clamp(node.X + i, 0, MAP_WIDTH);
			int clampedY = std::clamp(node.Y + j, 0, MAP_HEIGHT);
			if ((i + j == -1 || i + j == 1) && _grid[clampedY][clampedX]->IsWalkable)
			{
				openList.push_back(_grid[clampedY][clampedX]);
			}
		}
	}

	return openList;
}
