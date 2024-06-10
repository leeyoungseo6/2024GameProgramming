#pragma once
#include "Object.h"
#include "MapManager.h"

enum class Layer
{
	Default, Wall, Enemy, Count
};

class LayerMask
{
private:
	LayerMask() {};
	~LayerMask();
public:
	bool Init();
public:
	static LayerMask* GetInstance()
	{
		if (pInst == nullptr)
			pInst = new LayerMask;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}
private:
	static LayerMask* pInst;
public:
	void AddMask(POS pos, Layer layer);
	void Move(POS oldPos, POS newPos, Layer layer);
	int Mask(POS pos);
private:
	bool _mask[(int)Layer::Count][MAP_HEIGHT][MAP_WIDTH];
};