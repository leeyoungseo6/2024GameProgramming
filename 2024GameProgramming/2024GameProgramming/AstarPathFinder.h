#pragma once
#include "define.h"
#include "Pos.h"
#include "AstarGrid.h"

class AStarPathFinder
{
private:
	AStarPathFinder() = default;
	~AStarPathFinder() {};
public:
	bool Init();
private:
	static AStarPathFinder* pInst;
public:
	static AStarPathFinder* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new AStarPathFinder;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}

	stack<POS> GetPath(const POS& startPos, const POS& targetPos);
public:
	AStarGrid Grid;
};

