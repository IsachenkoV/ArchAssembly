#pragma once

#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker, "/STACK:20000000")

#include "haffman.h"
#include "mymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <fstream>

#define MAXSUBWORDLEN 50

using namespace std;

struct subword {
	ll hash;
	Code c;
	int len;
	subword() {}
	subword(ll _h, int _l, Code _c) : hash(_h), c(_c), len(_l) {}
};

typedef vector < subword > dict;