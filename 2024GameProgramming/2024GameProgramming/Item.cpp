#include "Item.h"
#include "mci.h"

Item::Item(POS pos, string symbol, int color)
	: Object(pos, 'a', Layer::Item, SortingLayerID::Item)
{
	_symbol = symbol;
	_color = color;
}

void Item::Render()
{
	SetColor(_color);
	Gotoxy(_pos.x * 2, _pos.y);
	if (SortingLayer::GetInstance()->Mask(_pos) <= (int)_sortingLayer)
		cout << _symbol;
	SetColor();
}

void Item::GetItem()
{
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
	PlaySFX(TEXT("item.mp3"));
}
