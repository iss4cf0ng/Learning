#pragma once
#include "Windows.h"
#include "stdio.h"
#include "tchar.h"

#ifdef _DEBUG
#define DEBUG(...) (_ftprintf(stderr, __VA_ARGS__))
#else
#define DEBUG(...) (0)
#endif

class hexdump
{
};

