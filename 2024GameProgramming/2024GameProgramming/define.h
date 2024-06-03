#pragma once
#include <iostream>
using std::cout;
using std::wcout;
using std::endl;
#include <Windows.h>
#define SAFE_DELETE(p) if (pInst != nullptr) { delete pInst; pInst = nullptr; }