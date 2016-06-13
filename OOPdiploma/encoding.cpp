#include "encoding.h"

bool operator<(Code a, Code b)
{
	if (a.q < b.q)
		return true;
	if (a.q > b.q)
		return false;
	if (a.r < b.r)
		return true;
	if (a.r > b.r)
		return false;
	return a.d < b.d;
}