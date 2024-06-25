#pragma once
#include "Item.h"

class AnyAttackItem : public Item
{
public:
	AnyAttackItem(POS pos);
	virtual void GetItem() override;
	static int duration;
};

