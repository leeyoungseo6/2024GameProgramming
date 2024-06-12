#include "MapManager.h"

bool MapManager::CheckLoad(POS pos) // ���� �� ��ġ�� �ε����� �ƴ��� Ȯ���ϴ� �Լ�
{
	return _arrMap[pos.y][pos.x] == (char)OBJ_TYPE::ROAD ? true : false;
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
				cout << "�� �ε��� ������ ������..";
			}
		}
	}
}

void MapManager::Renderer()
{
	//for (int i = 0; i < MAP_HEIGHT; ++i) {
	//	for (int j = 0; j < MAP_WIDTH; ++j) {
	//		if (_pPlayer->tPos.x == j && _pPlayer->tPos.y == i) { // �÷��̾� ����ֱ�
	//			cout << "��";
	//		}
	//		else if (_arrMap[i][j] == (char)OBJ_TYPE::WALL) {
	//			cout << "��";
	//		}
	//		else if (_arrMap[i][j] == (char)OBJ_TYPE::ROAD) {
	//			cout << "  ";
	//		}
	//	}
	//	cout << endl;
	//}
}
