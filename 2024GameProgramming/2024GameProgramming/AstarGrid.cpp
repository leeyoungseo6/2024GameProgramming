#include "AstarGrid.h"

void AstarGrid::CreateGrid()
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			_grid[i][j] = { i, j, 0, 0, true };
		}
	}
}

vector<AstarNode>& AstarGrid::GetOpenList(PAstarNode node)
{
	vector<AstarNode> openList(4);
	openList.push_back({ node->X + 1, node->Y, 0, 0, true });
	openList.push_back({ node->X - 1, node->Y, 0, 0, true });
	openList.push_back({ node->X, node->Y + 1, 0, 0, true });
	openList.push_back({ node->X, node->Y - 1, 0, 0, true });
	return openList;
}
