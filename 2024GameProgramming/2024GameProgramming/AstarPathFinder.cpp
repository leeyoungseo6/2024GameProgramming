#include "AStarPathFinder.h"
AStarPathFinder* AStarPathFinder::pInst = nullptr;

bool AStarPathFinder::Init()
{
	Grid = AStarGrid();
	Grid.CreateGrid();
	return true;
}

stack<POS> AStarPathFinder::GetPath(const POS& startPos, const POS& targetPos)
{
	AStarNode* startNode = Grid.GetNode(startPos);
	AStarNode* targetNode = Grid.GetNode(targetPos);

	vector<AStarNode*> openList;
	vector<AStarNode*> closedList{ openList };
	AStarNode* currentNode = startNode;
	int cnt = 0;
	while (currentNode != targetNode)
	{
		
		for (auto neighbor : Grid.GetOpenList(*currentNode))
		{
			if (neighbor->IsWalkable == false || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) continue;
			if (cnt == 0) currentNode->G = 0;
			neighbor->G = currentNode->G + currentNode->GetDistanceCost(*neighbor);
			neighbor->H = neighbor->GetDistanceCost(*targetNode);
			neighbor->ParentNode = currentNode;
			if (std::find(openList.begin(), openList.end(), neighbor) == openList.end())
				openList.push_back(neighbor);
			++cnt;
		}

		int idx = 0;
		if (openList.empty())
			return stack<POS>();
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
