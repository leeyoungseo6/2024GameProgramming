#pragma once
enum class MENU {
	START,
	INFO,
	QUIT
};
enum class KEY {
	UP, DOWN, LEFT, RIGHT, SPACE, FALL
};
class Title
{
private:
	Title() = default;
public:
	static Title* GetInstance() {
		if (Instance == nullptr) {
			Instance = new Title();
		}
		return Instance;
	}
private:
	static Title* Instance;
public:
	void TitleRenderer();
	bool Init();
	MENU MenuRender();
	KEY KeyController();
	void EnterAnimation();
};

using std::wcout;
using std::cout;
using std::endl;