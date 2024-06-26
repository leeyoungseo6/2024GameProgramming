#include "PlusTimeItem.h"
#include "Timer.h"

PlusTimeItem::PlusTimeItem(POS pos)
	: Item(pos, "¢Á", (int)COLOR::SKYBLUE)
{

}

void PlusTimeItem::GetItem()
{
	Timer::GetInstance()->AddTime(5);
	Item::GetItem();
}
