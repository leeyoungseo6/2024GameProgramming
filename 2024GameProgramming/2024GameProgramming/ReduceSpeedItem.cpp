#include "ReduceSpeedItem.h"
#include "ObjectManager.h"
int ReduceSpeedItem::duration = 3000;

ReduceSpeedItem::ReduceSpeedItem(POS pos)
	: Item(pos)
{

}

void ReduceSpeedItem::Render()
{
	SetColor((int)COLOR::LIGHT_GREEN);
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "¡Ø";
	SetColor();
}

void ReduceSpeedItem::GetItem()
{
	ObjectManager::GetInstance()->ReduceEnemySpeed();
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
}