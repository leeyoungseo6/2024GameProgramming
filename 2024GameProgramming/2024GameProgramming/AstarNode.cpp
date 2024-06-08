#include "AstarNode.h"

AStarNode::_tagastarnode(int x, int y, bool isWalkable)
{
	X = x;
	Y = y;
	IsWalkable = isWalkable;
}

int AStarNode::GetDistanceCost(const AStarNode& node)
{
	int disX = abs(X - node.X);
	int disY = abs(Y - node.Y);

	if (disX > disY) return 14 * disY + 10 * (disX - disY);
	return 14 * disX + 10 * (disY - disX);
}

bool AStarNode::operator==(const AStarNode& b)
{
	return X == b.X && Y == b.Y;
}

bool AStarNode::operator!=(const AStarNode& b)
{
	return !(*this == b);
}
