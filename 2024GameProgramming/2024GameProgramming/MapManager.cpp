#include "MapManager.h"
#include"console.h"

MapManager* MapManager::Instance = nullptr;
bool MapManager::CheckLoad(POS pos) // 현재 내 위치가 로드인지 아닌지 확인하는 함수
{
	return _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::ROAD ? true : false;
}

void MapManager::Init()
{
	std::fstream stageData("SaveStageData.txt");
	if (stageData.is_open()) {
		char stage[10];
		stageData.getline(stage, 10);
		if (stageData.fail()) {
			std::cout << "file error" << endl;
		}
		std::string name(stage);
		LoadMap(name + ".txt");
		//LoadMap("stage-1.txt");
	}
 }

void MapManager::LoadMap(std::string name)
{
	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			// 다시 getline으로 읽을 때 기본꺼를 clear 해야함(여러 스테이지일 경우)
			//readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "맵 로딩에 문제가 생겼어용.." << endl;
			}
		}
	}
}

void MapManager::Renderer()
{
	Gotoxy(0, 0);
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (_arrMap[i][j] == (char)OBJ_TYPE::WALL) {
				cout << "■";
			}
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
				cout << "  ";
			}
		}
		cout << endl;
	}
}
