#include "MapManager.h"

void MapManager::CheckLoad(POS player) // ���� �� ��ġ�� �ε����� �ƴ��� Ȯ���ϴ� �Լ�
{

}

void MapManager::LoadMap(std::string name)
{
	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			// �ٽ� getline���� ���� �� �⺻���� clear �ؾ���(���� ���������� ���)
			readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				std::cout << "�� �ε��� ������ ������.." << std::endl;
			}
		}
	}
}
