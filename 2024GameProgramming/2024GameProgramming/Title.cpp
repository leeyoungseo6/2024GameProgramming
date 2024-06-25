#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>;
#include "Title.h"
#include "console.h"
#include "mci.h"

Title* Title::Instance = nullptr;

bool Title::Init() {
	PlayBGM(TEXT("bgm.mp3"), 1000);
	while (true) { // 게임 룰을 볼때 다시 타이틀로 돌아올 수 있어야하기 때문에
		TitleRenderer();
		MENU eNeum = MenuRender();
		switch (eNeum) {
		case MENU::START:
			return true;
		case MENU::QUIT:
			return false;
		}
	}
}
void Title::TitleRenderer() {
	int prevmode = _setmode(_fileno(stdout), _O_U16TEXT); // wcout으로 변경

	wcout << L"██████   █████   ██████ ██   ██ ███████ ████████  █████  ██████  " << endl;
	wcout << L"██   ██ ██   ██ ██      ██  ██  ██         ██    ██   ██ ██   ██ " << endl;
	wcout << L"██████  ███████ ██      █████   ███████    ██    ███████ ██████  " << endl;
	wcout << L"██   ██ ██   ██ ██      ██  ██       ██    ██    ██   ██ ██   ██ " << endl;
	wcout << L"██████  ██   ██  ██████ ██   ██ ███████    ██    ██   ██ ██████  " << endl;
	
	int curmode = _setmode(_fileno(stdout), prevmode); // cout으로 변경
}

MENU Title::MenuRender() {
	// 시작, 정보, 나가기 출력 및 연결
	COORD Resoultion = GetConsoleResolution();
	int x = Resoultion.X / 4;
	int y = Resoultion.Y / 3;
	int yDefault = y;

	Gotoxy(x, y);
	cout << "게임 시작";
	Gotoxy(x, y + 1);
	cout << "게임 종료";

	while (true)
	{
		KEY eKey = KeyController();
		switch (eKey) {
		case KEY::UP: {
			if (y > yDefault) { // 위로 그리기 방지
				Gotoxy(x - 1, y); // 현재 위치 삭제
				cout << " ";
				Gotoxy(x - 1, --y); // 위에 그려주기
				cout << ">";
				Sleep(100);
			}
			break;
		}
		case KEY::DOWN:
			if (y < yDefault + 1) { // 아래로 그리기 방지
				Gotoxy(x - 1, y); // 현재 위치 삭제
				cout << " ";
				Gotoxy(x - 1, ++y); // 아래에 그려주기
				cout << ">";
				Sleep(100);
			}
			break;
		case KEY::SPACE:
			if (yDefault == y) {
				return MENU::START;
			}
			if (yDefault + 2 == y) {
				return MENU::QUIT;
			}
			break;
		}
	}

	return MENU::INFO;
}

KEY Title::KeyController()
{
	// _getch(), _kbhit() // 로 받아도 됨
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		// 여기에서 슬립을 걸어도 상관없지만 부자연스러움 따라서 입력을 받고 이동을하고 나서 슬립을 걸어주는 것이 자연스러움 
		return KEY::UP;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		return KEY::DOWN;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		return KEY::SPACE;
	}
	return KEY::FALL;
}



