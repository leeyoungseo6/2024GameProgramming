#pragma once
#include <Windows.h>
#include "define.h"
#include "AstarGrid.h"
class AstarPathFinder
{
private:
	AstarPathFinder() {};
	~AstarPathFinder();
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
	AstarGrid Grid;
};

