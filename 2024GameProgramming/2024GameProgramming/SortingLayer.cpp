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
	_layers[(int)layer][pos.y][pos.x] = 0;
}

void SortingLayer::RemoveLayer(SortingLayerID layer)
{
	for (int i = 0; i < MAP_HEIGHT + 2; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			_layers[(int)layer][i][j] = false;
}

void SortingLayer::Move(POS oldPos, POS newPos, SortingLayerID layer)
{
	if (_layers[(int)layer][oldPos.y][oldPos.x] > 0)
		_layers[(int)layer][oldPos.y][oldPos.x] = 0;
	_layers[(int)layer][newPos.y][newPos.x] = 1;
}

void SortingLayer::Render(POS pos, string symbol, SortingLayerID layer)
{
	if (Mask(pos) <= (int)layer)
	{
		Move(POS::zero, pos, layer);
		Gotoxy(pos.x, pos.y);
		cout << symbol;
	}
}

void SortingLayer::Render(POS oldPos, POS newPos, string symbol, SortingLayerID layer)
{
	if (oldPos != newPos)
		Move(oldPos, newPos, layer);
	if (Mask(newPos) <= (int)layer)
	{
		Gotoxy(newPos.x * 2, newPos.y);
		cout << symbol;
	}
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
