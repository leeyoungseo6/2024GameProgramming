#include "ReduceSpeedItem.h"
#include "ObjectManager.h"
int ReduceSpeedItem::duration = 3000;

ReduceSpeedItem::ReduceSpeedItem(POS pos)
	: Item(pos, "¢É", (int)COLOR::MINT)
{

}

void ReduceSpeedItem::GetItem()
{
	ObjectManager::GetInstance()->ReduceEnemySpeed();
	Item::GetItem();
}