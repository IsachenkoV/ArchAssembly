#include "NaiveAssembly.h"

NaiveAssembly::NaiveAssembly(HashString & _hs) : str(_hs)
{
}

dict NaiveAssembly::get_assembly(int l, int r)
{
	if (str.dp.count(str.get_hash(l, r)))
		return str.dp[str.get_hash(l, r)];
	dict ans;
	map <ll, int> hashindex;
	vector < ll > all_hashes = str.get_alph_hashes();
	for (int i = 0; i < all_hashes.size(); i++)
	{
		hashindex[all_hashes[i]] = i;
		ans.push_back(subword(all_hashes[i], 0, Code(-1, -1, false)));
	}

	int len = r - l + 1;
	r++;
	
	ll cur_hash = str.get_hash(l, l);
	int ind1 = hashindex[cur_hash];

	for (int i = l + 1; i < r; i++)
	{
		cur_hash = str.get_hash(i, i);
		int ind2 = hashindex[cur_hash];

		int r = min(ind1, ind2);
		int q = max(ind1, ind2);
		bool d = ind1 == r ? false : true;
		ans.push_back(subword(str.get_hash(l, i), i - l + 1, Code(q, r, d)));

		ind1 = ans.size() - 1;
	}

	return str.dp[str.get_hash(l, r - 1)] = ans;
}
