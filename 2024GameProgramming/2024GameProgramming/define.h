#pragma once
#include <iostream>
#include <vector>
using std::cout;
using std::wcout;
using std::endl;
using std::vector;
#include <Windows.h>
#define SAFE_DELETE(p) if (pInst != nullptr) { delete pInst; pInst = nullptr; }

#define MAP_WIDTH 21
#define MAP_HEIGHT 20