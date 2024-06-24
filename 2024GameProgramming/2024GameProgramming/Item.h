#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(POS pos);
	void Update() override {};
	virtual void Render() abstract;
	virtual void GetItem() abstract;
};

