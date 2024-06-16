#include <iostream>
#include "AStarNode.h"

AStarNode::AStarNode(int x, int y, bool isWalkable)
{
	X = x;
	Y = y;
	G = 0;
	H = 0;
	IsWalkable = isWalkable;
}

int AStarNode::GetDistanceCost(const AStarNode& node)
{
	int disX = abs(X - node.X);
	int disY = abs(Y - node.Y);

	if (disX > disY) return 14 * disY + 10 * (disX - disY);
	return 14 * disX + 10 * (disY - disX);
}

void AStarNode::operator=(const AStarNode& b)
{
	X = b.X;
	Y = b.Y;
	G = b.G;
	H = b.H;
	IsWalkable = b.IsWalkable;
	ParentNode = b.ParentNode;
}

bool AStarNode::operator==(const AStarNode& b)
{
	return X == b.X && Y == b.Y;
}

bool AStarNode::operator!=(const AStarNode& b)
{
	return !(*this == b);
}