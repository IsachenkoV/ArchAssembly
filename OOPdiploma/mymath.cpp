#include "mymath.h"

ll get_power(int t_power)
{
	ll _p = p;
	ll res = 1LL;
	while (t_power)
	{
		if (t_power & 1)
			res *= _p;
		_p *= _p;
		t_power >>= 1;
	}
	return res;
}

int get_log(int k)
{
	if (k < 0)
		throw new std::exception("negative!");
	if (k == 0)
		return 1;
	int i = 1;
	while ((1 << i) < k)
		i++;
	return i;
}