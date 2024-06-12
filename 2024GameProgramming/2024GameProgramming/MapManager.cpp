#include "MapManager.h"

bool MapManager::CheckLoad(POS pos) // 현재 내 위치가 로드인지 아닌지 확인하는 함수
{
	return _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::ROAD ? true : false;
}

void MapManager::LoadMap(std::string name)
{
	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			// 다시 getline으로 읽을 때 기본꺼를 clear 해야함(여러 스테이지일 경우)
			readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "맵 로딩에 문제가 생겼어용..";
			}
		}
	}
}

void MapManager::Renderer()
{
	//for (int i = 0; i < MAP_HEIGHT; ++i) {
	//	for (int j = 0; j < MAP_WIDTH; ++j) {
	//		if (_pPlayer->tPos.x == j && _pPlayer->tPos.y == i) { // 플레이어 찍어주기
	//			cout << "⊙";
	//		}
	//		else if (_arrMap[i][j] == (char)OBJ_TYPE::WALL) {
	//			cout << "■";
	//		}
	//		else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
	//			cout << "  ";
	//		}
	//	}
	//	cout << endl;
	//}
}
