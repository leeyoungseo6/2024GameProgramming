#pragma once
#include "Item.h"

class AnyAttackItem : public Item
{
public:
	AnyAttackItem(POS pos);
	void Render() override;
	void GetItem() override;
	static int duration;
};

