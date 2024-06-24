#include "AnyAttackItem.h"
#include "ObjectManager.h"
int AnyAttackItem::duration = 3000;

AnyAttackItem::AnyAttackItem(POS pos)
	: Item(pos)
{

}

void AnyAttackItem::Render()
{
	SetColor((int)COLOR::LIGHT_VIOLET);
	Gotoxy(_pos.x * 2, _pos.y);
	cout << "£À";
	SetColor();
}

void AnyAttackItem::GetItem()
{
	ObjectManager::GetInstance()->EnableAnyAttack();
	LayerMask::GetInstance()->RemoveMask(_pos, _layer);
	SortingLayer::GetInstance()->RemoveLayer(_pos, _sortingLayer);
}
