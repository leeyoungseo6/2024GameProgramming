#include "MapManager.h"
#include "Core.h"

MapManager* MapManager::Instance = nullptr;
bool MapManager::CheckRoad(POS pos) // ���� �� ��ġ�� �ε����� �ƴ��� Ȯ���ϴ� �Լ�
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
	LayerMask::GetInstance()->RemoveMask(Layer::Wall); // �� ���� �ε��� �� ������ �ִ� ���̾� ����

	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			// �ٽ� getline���� ���� �� �⺻���� clear �ؾ���(���� ���������� ���)
			//readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "�� �ε��� ������ ������.." << endl;
			}
			else { // �� �ε� ���� �� �� �κп� ���̾� �߰�
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (_arrMap[i][j] == (char)OBJ_TYPE::PLAYERPOS)
						Core::GetInstance()->SpawnPlayer({ j, i });
					if (_arrMap[i][j] == (char)OBJ_TYPE::ENEMYPOS)
						Core::GetInstance()->SpawnEnemy({ j, i });
					if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
						LayerMask::GetInstance()->AddMask({ j, i }, Layer::Wall); // ����ĳ��Ʈ�� ���� �� �ִ� ���� ���̾� �߰�
				}
			}
		}
	}
}

void MapManager::NextStage() // ���� ���������� �Ѿ
{
	SaveMap(); // �������̸����� �����ϰ�
	ReadFile();
}

void MapManager::SaveMap() // Ŭ�����ϸ� �����Ұ�
{
}


void MapManager::Render()
{
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (SortingLayer::GetInstance()->Mask({ j, i }) > 0) // ���� ���̾ �ִ� ���� ���� �׸��� ����
				continue;

			Gotoxy(j * 2, i);
			if (_arrMap[i][j] == (char)OBJ_TYPE::WALL) {
				cout << "��";
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
