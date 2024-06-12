#include "AStarPathFinder.h"
AstarPathFinder* AstarPathFinder::pInst = nullptr;

bool AstarPathFinder::Init()
{
	Grid = AStarGrid();
	Grid.CreateGrid();
	return true;
}

stack<POS> AstarPathFinder::GetPath(const POS& startPos, const POS& targetPos)
{
	AStarNode* startNode = Grid.GetNode(startPos);
	AStarNode* targetNode = Grid.GetNode(targetPos);

	vector<AStarNode*> openList;
	vector<AStarNode*> closedList{ openList };
	AStarNode* currentNode = startNode;

	while (currentNode != targetNode)
	{
		for (auto neighbor : Grid.GetOpenList(*currentNode))
		{
			if (neighbor->IsWalkable == false || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) continue;
			neighbor->G = currentNode->G + currentNode->GetDistanceCost(*neighbor);
			neighbor->H = currentNode->GetDistanceCost(*targetNode);
			neighbor->ParentNode = currentNode;
			if (std::find(openList.begin(), openList.end(), neighbor) == openList.end())
				openList.push_back(neighbor);
		}

		int idx = 0;
		currentNode = openList.front();
		for (int i = 0; i < openList.size(); i++)
		{
			AStarNode* node = openList[i];
			if (node->F < currentNode->F || (node->F == currentNode->F && node->H < currentNode->H))
			{
				currentNode = node;
				idx = i;
			}
		}

		openList.erase(openList.begin() + idx);
		closedList.push_back(currentNode);
	}

	currentNode = targetNode;

	stack<POS> path;
	while (currentNode != startNode)
	{
		path.push({ currentNode->X, currentNode->Y });
		currentNode = currentNode->ParentNode;
	}

	return path;
}
