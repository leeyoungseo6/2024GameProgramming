#include "AnyAttackItem.h"
#include "ObjectManager.h"
int AnyAttackItem::duration = 3000;

AnyAttackItem::AnyAttackItem(POS pos)
	: Item(pos, "¢»", (int)COLOR::LIGHT_VIOLET)
{

}

void AnyAttackItem::GetItem()
{
	ObjectManager::GetInstance()->EnableAnyAttack();
	Item::GetItem();
}
