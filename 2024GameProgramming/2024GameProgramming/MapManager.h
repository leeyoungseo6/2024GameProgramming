#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "LayerMask.h"
#include "SortingLayer.h"
#include "define.h"
#include "Pos.h"
#include "console.h"

enum class OBJ_TYPE {
	WALL='0', ROAD, PLAYERPOS, ENEMYPOS, PLUSTIMEITEM, REDUCEDSPEEDITEM, ANYATTACKITEM
};

class MapManager {
private:
	MapManager() = default;
public:
	static MapManager* GetInstance() {
		if (Instance == nullptr) {
			Instance = new MapManager();
		}
		return Instance;
	}
private:
	static MapManager* Instance;

public:
	char _arrMap[MAP_HEIGHT][MAP_WIDTH] = {};

	void Init();
	bool CheckRoad(POS player);
	void LoadMap(std::string name);
	void Render();
};