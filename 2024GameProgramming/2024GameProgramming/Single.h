#pragma once
class Single
{
private:
	Single();
private:
	static Single* pInstance;
public:
	static Single* GetInstance()
	{
		if (pInstance == nullptr)
			pInstance = new Single;
		return pInstance;
	}
};

