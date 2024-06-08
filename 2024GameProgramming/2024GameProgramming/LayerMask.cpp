#include "LayerMask.h"
LayerMask* LayerMask::pInst = nullptr;

bool LayerMask::Init()
{
	return true;
}

void LayerMask::AddMask(POS pos, Layer layer)
{
	_mask[(int)layer][pos.y][pos.x] = true;
}

void LayerMask::Move(POS oldPos, POS newPos, Layer layer)
{
	_mask[(int)layer][oldPos.y][oldPos.x] = false;
	_mask[(int)layer][newPos.y][newPos.x] = true;
}

int LayerMask::Mask(POS pos)
{
	int result = 0;
	for (int i = 0; i < (int)Layer::Count; i++)
	{
		result |= 1 << (int)(_mask[i][pos.y][pos.x]);
	}

	return result;
}
