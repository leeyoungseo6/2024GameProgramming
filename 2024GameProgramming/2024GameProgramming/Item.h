#pragma once
#include "Object.h"

class Item : public Object
{
public:
	Item(POS pos, string symbol, int color);
	void Update() override {}; // �ʿ����
	void Render() override;
	virtual void GetItem();
private:
	string _symbol;
	int _color;
};

