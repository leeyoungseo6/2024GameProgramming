#include "ReduceSpeedItem.h"
#include "ObjectManager.h"
int ReduceSpeedItem::duration = 3000;

ReduceSpeedItem::ReduceSpeedItem(POS pos)
	: Item(pos, "¡Ø", (int)COLOR::LIGHT_GREEN)
{

}

void ReduceSpeedItem::GetItem()
{
	ObjectManager::GetInstance()->ReduceEnemySpeed();
	Item::GetItem();
}