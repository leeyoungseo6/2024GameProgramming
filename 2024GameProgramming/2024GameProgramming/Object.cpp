#include "Object.h"

Object::Object(POS pos, char symbol, Layer layer, SortingLayerID sortingLayer)
{
	_pos = pos;
	_symbol = symbol;
	_layer = layer;
	_sortingLayer = sortingLayer;
	LayerMask::GetInstance()->AddMask(pos, layer);
	SortingLayer::GetInstance()->AddLayer(pos, sortingLayer);
}