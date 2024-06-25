#include "MapManager.h"
#include "ObjectManager.h"
#include "Timer.h"
#include <string>

MapManager* MapManager::Instance = nullptr;
bool MapManager::CheckRoad(POS pos) // 현재 내 위치가 로드인지 아닌지 확인하는 함수
{
	return _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::ROAD
		|| _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::PLAYERPOS
		|| _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::ENEMYPOS;
}

void MapManager::Init()
{
	ReadFile();
 }

void MapManager::ReadFile()
{
	std::fstream file("SaveStageData.txt");
	if (file.is_open()) {
		char stage[10];
		file.getline(stage, 10);
		if (file.fail()) {
			std::cout << "file error" << endl;
		}
		std::string name(stage);
		LoadMap(name + ".txt");
	}
}

void MapManager::LoadMap(std::string name)
{
	LayerMask::GetInstance()->RemoveMask(Layer::Wall); // 세 맵을 로드할 때 기존에 있던 레이어 삭제

	EnterAnimation();

	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 2; i < MAP_HEIGHT + 2; ++i) {
			// 다시 getline으로 읽을 때 기본꺼를 clear 해야함(여러 스테이지일 경우)
			readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "맵 로딩에 문제가 생겼어용.." << endl;
			}
			else { // 맵 로드 성공
				for (int j = 0; j < MAP_WIDTH; ++j)
				{
					if (_arrMap[i][j] == (char)OBJ_TYPE::PLAYERPOS)
						ObjectManager::GetInstance()->SpawnPlayer({ j, i});
					if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
						LayerMask::GetInstance()->AddMask({ j, i}, Layer::Wall); // 레이캐스트를 위해 벽 있는 곳에 레이어 추가
				}
			}
		}
		char t[10];
		readMap.getline(t, 10);
		if (readMap.fail()) {
			std::cout << "file error" << endl;
		}
		std::string name(t);
		int time = std::stoi(name);
		Timer::GetInstance()->StartTimer(time);

		for (int i = 2; i < MAP_HEIGHT + 2; ++i) {
			for (int j = 0; j < MAP_WIDTH; ++j)
			{
				if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMYPOS)
					ObjectManager::GetInstance()->SpawnEnemy({ j, i});
			}
		}
	}
}

void MapManager::NextStage() // 다음 스테이지로 넘어감
{
	SaveMap(); // 다음맵이름으로 저장하고
	ReadFile();
}

void MapManager::SaveMap() // 클리어하면 저장할거
{
	int newNum = 0;
	std::fstream readFile("SaveStageData.txt");
	if (readFile.is_open()) {
		char stage[10];
		readFile.getline(stage, 10);
		if (readFile.fail()) {
			std::cout << "file error" << endl;
		}
		std::string name(stage);
		newNum = std::stoi(name.substr(6));
	}
	std::ofstream writeFile("SaveStageData.txt", std::ios_base::ate);
	if (writeFile.is_open()) {
		//readFile.write("stage-" + ++newNum, 10);
		writeFile << "stage-" << ++newNum;
	}
	readFile.close();
}

void MapManager::RetryCurrentStage()
{
	ReadFile();
}
 
void MapManager::Render()
{
	for (int i = 2; i < MAP_HEIGHT + 2; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (SortingLayer::GetInstance()->Mask({ j, i}) > 0) // 상위 레이어가 있는 곳엔 맵을 그리지 않음
				continue;

			Gotoxy(j * 2, i);
			if (_arrMap[i][j] == (char)OBJ_TYPE::WALL) {
				cout << "■";
			}
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
				cout << "  ";
			}
			else if (_arrMap[i][j] == (char)OBJ_TYPE::PLAYERPOS) {
				cout << "  ";
			}
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMYPOS) {
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void MapManager::EnterAnimation()
{
	COORD Resolution = GetConsoleResolution();

	int width = Resolution.X;
	int height = Resolution.Y;
	int animationtime = 10;
	// 5번 깜빡거리기
	for (int i = 0; i < 5; i++) {
		Gotoxy(0, 0);
		SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
		system("cls");
		Sleep(animationtime);

		Gotoxy(0, 0);
		SetColor((int)COLOR::WHITE);
		system("cls");
		Sleep(animationtime);
	}
	// 크로스
	SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
	for (int i = 0; i < width / 2; i++) {
		for (int j = 0; j < height; j += 2) {
			Gotoxy(i * 2, j);
			cout << "  ";
		}
		for (int j = 1; j < height; j += 2) {
			Gotoxy(width - 2 - i * 2, j);
			cout << "  ";
		}
		Sleep(animationtime);
	}
	SetColor((int)COLOR::WHITE);
	system("cls");
}
