#pragma once
#include "Item.h"
#include "Pos.h"

class ReduceSpeedItem : public Item
{
public:
	ReduceSpeedItem(POS pos);
	virtual void GetItem() override;
	static int duration;
};

