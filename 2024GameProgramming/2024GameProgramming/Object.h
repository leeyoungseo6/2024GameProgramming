#pragma once
#include <Windows.h>
#include "Pos.h"
#include "console.h"
#include "LayerMask.h"
#include "SortingLayer.h"

class Object
{
public:
	Object(POS pos, char symbol, Layer layer, SortingLayerID sortingLayer);
	virtual void Update() abstract;
	virtual void Render() {};
	POS& GetPos() { return _pos; };
protected:
	POS _pos;
	char _symbol;
	Layer _layer;
	SortingLayerID _sortingLayer;
};