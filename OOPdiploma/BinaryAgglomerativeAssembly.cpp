#include "BinaryAgglomerativeAssembly.h"

BinaryAgglomerativeAssembly::BinaryAgglomerativeAssembly(HashString & _hs) : str(_hs)
{
}

dict BinaryAgglomerativeAssembly::get_assembly(int l, int r)
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
	int prev_step = 1;
	int step = 2;
	r++;

	while (prev_step < len)
	{
		queue < int > indeces;
		for (int i = l; i < r; i += prev_step)
		{
			ll temp_h;
			if (i + prev_step - 1 < r)
			{
				temp_h = str.get_hash(i, i + prev_step - 1);
			}
			else
			{
				temp_h = str.get_hash(i, r - 1);
			}
			indeces.push(hashindex[temp_h]);
		}

		vector < ll > vech;
		for (int i = l; i < r; i += step)
		{
			ll temp_h;
			if (i + step - 1 < r)
			{
				temp_h = str.get_hash(i, i + step - 1);
			}
			else
			{
				temp_h = str.get_hash(i, r - 1);
			}
			vech.push_back(temp_h);
		}

		set < pair<Code, ll> > sortset;
		int k = 0;
		while (!indeces.empty())
		{
			int ind1 = indeces.front();
			indeces.pop();
			if (indeces.empty())
				break;

			int ind2 = indeces.front();
			indeces.pop();

			int r = min(ind1, ind2);
			int q = max(ind1, ind2);
			bool d = ind1 == r ? false : true;
			sortset.insert(mp(Code(q, r, d), vech[k]));
			k++;
		}

		for (auto x : sortset)
		{
			ans.push_back(subword(x.second, 0, x.first));
			all_hashes.push_back(x.second);
			hashindex[x.second] = all_hashes.size() - 1;
		}
		prev_step = step;
		step *= 2;
	}
	str.dp[str.get_hash(l, r - 1)] = ans;
	return ans;
}
