#include "MapManager.h"
#include "ObjectManager.h"
#include "Timer.h"
#include <string>

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
	LayerMask::GetInstance()->RemoveMask(Layer::Wall); // �� ���� �ε��� �� ������ �ִ� ���̾� ����

	EnterAnimation();

	std::fstream readMap(name);
	if (readMap.is_open()) {
		for (int i = 2; i < MAP_HEIGHT + 2; ++i) {
			// �ٽ� getline���� ���� �� �⺻���� clear �ؾ���(���� ���������� ���)
			readMap.clear();
			readMap.getline(_arrMap[i], MAP_WIDTH);
			if (readMap.fail()) {
				cout << "�� �ε��� ������ ������.." << endl;
			}
			else { // �� �ε� ����
				for (int j = 0; j < MAP_WIDTH; ++j)
				{
					if (_arrMap[i][j] == (char)OBJ_TYPE::PLAYERPOS)
						ObjectManager::GetInstance()->SpawnPlayer({ j, i});
					if (_arrMap[i][j] == (char)OBJ_TYPE::WALL)
						LayerMask::GetInstance()->AddMask({ j, i}, Layer::Wall); // ����ĳ��Ʈ�� ���� �� �ִ� ���� ���̾� �߰�
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

void MapManager::NextStage() // ���� ���������� �Ѿ
{
	SaveMap(); // �������̸����� �����ϰ�
	ReadFile();
}

void MapManager::SaveMap() // Ŭ�����ϸ� �����Ұ�
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
			if (SortingLayer::GetInstance()->Mask({ j, i}) > 0) // ���� ���̾ �ִ� ���� ���� �׸��� ����
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

void MapManager::EnterAnimation()
{
	COORD Resolution = GetConsoleResolution();

	int width = Resolution.X;
	int height = Resolution.Y;
	int animationtime = 10;
	// 5�� �����Ÿ���
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
	// ũ�ν�
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
