#include "Core.h"
Core* Core::pInst = nullptr;

Core::Core()
{

}

bool Core::Init()
{
	AstarPathFinder::GetInstance()->Init();
	POINT pos = { 0, 5 };
	enemy = new Enemy(pos);
	return true;
}

void Core::Run()
{
	Init();
	while (true)
	{
		Update();
		Render();
	}
}

void Core::Update()
{
	enemy->Update();
}

void Core::Render()
{

}
