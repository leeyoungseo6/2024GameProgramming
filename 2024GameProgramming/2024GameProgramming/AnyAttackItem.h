#pragma once
#include "Item.h"

class AnyAttackItem : public Item
{
public:
	AnyAttackItem(POS pos);
	void GetItem() override;
	static int duration;
};

