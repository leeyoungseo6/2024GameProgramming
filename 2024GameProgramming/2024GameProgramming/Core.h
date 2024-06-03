#pragma once
#include "define.h"
class Core
{
private:
	Core();
	~Core();
public:
	bool Init();
	void Run();
private:
	void Update();
	void Render();
public:
	static Core* GetInstance()
	{
		if (pInst == nullptr)
			pInst = nullptr;
		return pInst;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(pInst);
	}
private:
	static Core* pInst;
};

