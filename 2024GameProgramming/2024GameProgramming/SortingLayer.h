#pragma once
#include <string>
#include "define.h"
#include "Pos.h"
#include "console.h"

enum class SortingLayerID
{
	BG, EnemyNext, Item, Agent, Top, Count
};

class SortingLayer
{
private:
	SortingLayer() = default;
	~SortingLayer() {};
public:
	bool Init();
public:
	static SortingLayer* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new SortingLayer;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}
private:
	static SortingLayer* pInst;
public:
	void AddLayer(POS pos, SortingLayerID layer);
	void RemoveLayer(POS pos, SortingLayerID layer);
	void RemoveLayer(SortingLayerID layer);
	void Move(POS oldPos, POS newPos, SortingLayerID layer);
	void Render(POS pos, string symbol, SortingLayerID layer);
	void Render(POS oldPos, POS newPos, string symbol, SortingLayerID layer);
	int Mask(POS pos);
private:
	int _layers[(int)SortingLayerID::Count][MAP_HEIGHT][MAP_WIDTH] = { false };
};

