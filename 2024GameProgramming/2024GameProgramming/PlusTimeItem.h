#pragma once
#include "Item.h"

class PlusTimeItem : public Item
{
public:
	PlusTimeItem(POS pos);
	virtual void GetItem() override;
	static int duration;
};

