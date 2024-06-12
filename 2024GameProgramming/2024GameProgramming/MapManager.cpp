#include "MapManager.h"
#include"console.h"

MapManager* MapManager::Instance = nullptr;
bool MapManager::CheckLoad(POS pos) // ���� �� ��ġ�� �ε����� �ƴ��� Ȯ���ϴ� �Լ�
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
			// �ٽ� getline���� ���� �� �⺻���� clear �ؾ���(���� ���������� ���)
			//readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "�� �ε��� ������ ������.." << endl;
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
				cout << "��";
			}
			else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
				cout << "  ";
			}
		}
		cout << endl;
	}
}
