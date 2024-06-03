#include <Windows.h>
#include "console.h"

void FullScreen()
{
	/*SetConsoleDisplayMode
	(
		GetStdHandle(STD_OUTPUT_HANDLE),
		CONSOLE_FULLSCREEN_MODE,
		NULL
	);*/
	
	//ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	::SendMessage(GetConsoleWindow(),
		WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void Gotoxy(int x, int y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체
	COORD Cur = { x, y };
	//커서 포지션 세팅 함수
	SetConsoleCursorPosition(hOut, Cur);
}

BOOL GotoPos(int x, int y)
{
	// 콘솔창 핸들
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 관련 구조체
	COORD Cur = { x, y };
	//커서 포지션 세팅 함수
	return SetConsoleCursorPosition(hOut, Cur);
}

COORD CursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buf);
	return buf.dwCursorPosition;
}

void CursorVisible(bool value, DWORD size)
{
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.dwSize = size;
	curInfo.bVisible = value;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void SetColor(int textColor, int bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

int GetColor()
{
	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buf);
	int color = buf.wAttributes & 0xf;
	return color;
}

void LockResize()
{
	HWND console = GetConsoleWindow();
	if (nullptr != console)
	{
		LONG style = GetWindowLong(console, GWL_STYLE);
		style &= ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
		SetWindowLong(console, GWL_STYLE, style);
	}
}

COORD GetConsoleResolution()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	short width = info.srWindow.Right - info.srWindow.Left + 1;
	short height = info.srWindow.Bottom - info.srWindow.Top + 1;
	return COORD{ width, height };
}

void SetFontSize(UINT weight, UINT fontx, UINT fonty)
{
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	GetCurrentConsoleFontEx(hOut, false, &font);
	font.FontWeight = weight;
	font.dwFontSize.X = fontx;
	font.dwFontSize.Y = fonty;

	SetCurrentConsoleFontEx(hOut, false, &font);
}
