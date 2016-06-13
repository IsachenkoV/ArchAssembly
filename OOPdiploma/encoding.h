#pragma once

#include <stdlib.h>
#include <string>

using namespace std;

struct Code {
	int q, r;
	bool d;

	Code()
	{
		q = r = 0;
		d = false;
	}

	Code(int _q, int _r, bool _d) : q(_q), r(_r), d(_d)
	{
	}
};

bool operator<(Code a, Code b);