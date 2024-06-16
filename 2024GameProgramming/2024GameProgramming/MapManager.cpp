#include "MapManager.h"
#include "Core.h"

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
	std::fstream stageData("SaveStageData.txt");
	if (stageData.is_open()) {
		char stage[10];
		stageData.getline(stage, 10);
		if (stageData.fail()) {
			std::cout << "file error" << endl;
		}
		std::string name(stage);
		LoadMap(name + ".txt");
	}
}

void MapManager::LoadMap(std::string name)
{
	LayerMask::GetInstance()->RemoveMask(Layer::Wall); // 세 맵을 로드할 때 기존에 있던 레이어 삭제

	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			// 다시 getline으로 읽을 때 기본꺼를 clear 해야함(여러 스테이지일 경우)
			//readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "맵 로딩에 문제가 생겼어용.." << endl;
			}
			else { // 맵 로드 성공 시 벽 부분에 레이어 추가
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (_arrMap[i][j] == (char)OBJ_TYPE::PLAYERPOS)
						Core::GetInstance()->SpawnPlayer({ j, i });
					if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMYPOS)
						Core::GetInstance()->SpawnEnemy({ j, i });
					if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
						LayerMask::GetInstance()->AddMask({ j, i }, Layer::Wall); // 레이캐스트를 위해 벽 있는 곳에 레이어 추가
				}
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
}


void MapManager::Render()
{
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (SortingLayer::GetInstance()->Mask({ j, i }) > 0) // 상위 레이어가 있는 곳엔 맵을 그리지 않음
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
