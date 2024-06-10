#pragma once
#include <string>
#include<fstream>
#include<iostream>
#include "Object.h"

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 15;

enum class OBJ_TYPE {
	WALL, ROAD, PLUSTIMEITEM, REDUCEDSPEEDITEM, ANYATTACKITEM
};

class MapManager {
private:
	MapManager();
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

	bool CheckLoad(POS player);
	void LoadMap(std::string name);
};