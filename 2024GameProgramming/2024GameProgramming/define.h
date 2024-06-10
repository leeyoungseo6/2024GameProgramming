#pragma once
#include <iostream>
#include <vector>
#include <stack>
using std::cout;
using std::wcout;
using std::endl;
using std::max;
using std::vector;
using std::stack;
#include <Windows.h>
#define SAFE_DELETE(p) if (pInst != nullptr) { delete pInst; pInst = nullptr; }