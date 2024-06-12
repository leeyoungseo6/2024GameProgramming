#pragma once
#include <string>
#include<fstream>
#include<iostream>
#include "Object.h"
#include"console.h"
#include "LayerMask.h"

enum class OBJ_TYPE {
	WALL='0', ROAD, PLUSTIMEITEM, REDUCEDSPEEDITEM, ANYATTACKITEM
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
	char _arrMap[MAP_WIDTH][MAP_HEIGHT] = {};

	void Init();
	bool CheckRoad(POS player);
	void LoadMap(std::string name);
	void Render();
};

using std::cout;
using std::endl;