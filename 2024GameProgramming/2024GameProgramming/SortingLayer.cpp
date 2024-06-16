#include "SortingLayer.h"
SortingLayer* SortingLayer::pInst = nullptr;

bool SortingLayer::Init()
{
	return true;
}

void SortingLayer::AddLayer(POS pos, SortingLayerID layer)
{
	_layers[(int)layer][pos.y][pos.x] = 1;
}

void SortingLayer::RemoveLayer(POS pos, SortingLayerID layer)
{
	_layers[(int)layer][pos.y][pos.x] -= 1;
}

void SortingLayer::RemoveLayer(SortingLayerID layer)
{
	std::fill_n(&_layers[(int)layer][0][0], MAP_WIDTH * MAP_HEIGHT * (int)layer, 0);
}

void SortingLayer::Move(POS oldPos, POS newPos, SortingLayerID layer)
{
	_layers[(int)layer][oldPos.y][oldPos.x] -= 1;
	_layers[(int)layer][newPos.y][newPos.x] += 1;
}

int SortingLayer::Mask(POS pos)
{
	for (int i = (int)SortingLayerID::Count - 1; i >= 0; i--)
	{
		if (_layers[i][pos.y][pos.x])
			return i;
	}

	return 0;
}
