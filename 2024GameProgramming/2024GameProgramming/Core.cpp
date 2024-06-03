#include "Core.h"
Core* Core::pInst = nullptr;

bool Core::Init()
{
	return true;
}

void Core::Run()
{
	while (true)
	{
		Update();
		Render();
	}
}

void Core::Update()
{

}

void Core::Render()
{

}
