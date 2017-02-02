#pragma once
#include "Windows.h"

#define ZMem(val) {ZeroMemory(&val, sizeof(val));}
#define SAFE_RELEASE(val) {if (val){val->Release(); val = nullptr;}}