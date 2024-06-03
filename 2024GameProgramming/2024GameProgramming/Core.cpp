#include "Core.h"
Core* Core::pInst = nullptr;

bool Core::Init()
{
	while (true)
	{
		Update();
		Render();
	}
}

void Core::Run()
{

}

void Core::Update()
{

}

void Core::Render()
{

}
