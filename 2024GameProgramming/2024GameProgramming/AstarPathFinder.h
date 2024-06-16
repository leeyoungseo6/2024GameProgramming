#pragma once
#include "define.h"
#include "Pos.h"
#include "AstarGrid.h"

class AstarPathFinder
{
private:
	AstarPathFinder() = default;
	~AstarPathFinder() {};
public:
	bool Init();
private:
	static AstarPathFinder* pInst;
public:
	static AstarPathFinder* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new AstarPathFinder;
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

