#include "MapManager.h"

void MapManager::CheckLoad(POS player) // 현재 내 위치가 로드인지 아닌지 확인하는 함수
{

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
				std::cout << "맵 로딩에 문제가 생겼어용.." << std::endl;
			}
		}
	}
}
