#include "GeneralAgglomerativeAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "FullWithClipAssembly.h"
#include "NaiveAssembly.h"

dict GeneralAgglomerativeAssembly::merge_dicts(dict ans1, dict ans2, int l, int i, int r)
{
	vector < int > ans_ind1(ans1.size()), ans_ind2(ans2.size());

	dict cur_dict;

	map < ll, int > added;
	int it1 = 0, it2 = 0;
	while (true)
	{
		subword a, b;
		bool has_a = false;
		bool has_b = false;
		if (it1 < ans1.size())
		{
			has_a = true;
			subword from = ans1[it1];
			int i1 = from.c.q != -1 ? ans_ind1[from.c.q] : -1;
			int i2 = from.c.r != -1 ? ans_ind1[from.c.r] : -1;
			bool x = from.c.d;
			if (i1 < i2)
				x = !x;
			a.hash = from.hash;
			a.len = from.len;
			a.c = Code(max(i1, i2), min(i1, i2), x);
		}

		if (it2 < ans2.size())
		{
			has_b = true;
			subword from = ans2[it2];
			int i1 = from.c.q != -1 ? ans_ind2[from.c.q] : -1;
			int i2 = from.c.r != -1 ? ans_ind2[from.c.r] : -1;
			bool x = from.c.d;
			if (i1 < i2)
				x = !x;
			b.hash = from.hash;
			b.len = from.len;
			b.c = Code(max(i1, i2), min(i1, i2), x);
		}

		bool flag_cont = false;
		if (added.count(a.hash) && it1 < ans1.size())
		{
			ans_ind1[it1] = added[a.hash];
			it1++;
			flag_cont = true;
		}
		if (added.count(b.hash) && it2 < ans2.size())
		{
			ans_ind2[it2] = added[b.hash];
			it2++;
			flag_cont = true;
		}

		if (flag_cont)
			continue;

		if (has_a && has_b)
		{
			if (a.c < b.c)
			{
				cur_dict.push_back(a);
				ans_ind1[it1] = cur_dict.size() - 1;
				added[a.hash] = cur_dict.size() - 1;
				it1++;
			}
			else
			{
				cur_dict.push_back(b);
				ans_ind2[it2] = cur_dict.size() - 1;
				added[b.hash] = cur_dict.size() - 1;
				it2++;
			}
		}
		else
			if (has_a || has_b)
			{
				if (has_a)
				{
					cur_dict.push_back(a);
					ans_ind1[it1] = cur_dict.size() - 1;
					added[a.hash] = cur_dict.size() - 1;
					it1++;
				}
				else
				{
					cur_dict.push_back(b);
					ans_ind2[it2] = cur_dict.size() - 1;
					added[b.hash] = cur_dict.size() - 1;
					it2++;
				}
			}

		if (it1 == ans1.size() && it2 == ans2.size())
		{
			int i1, i2;
			if (ans1.size() == str.alp_size)
			{
				ll hh = str.get_hash(l, i);
				for (int j = 0; j < ans1.size(); j++)
				{
					if (ans1[j].hash == hh)
					{
						i1 = ans_ind1[j];
						break;
					}
				}
			}
			else
			{
				i1 = ans_ind1[ans1.size() - 1];
			}
			if (ans2.size() == str.alp_size)
			{
				ll hh = str.get_hash(i + 1, r);
				for (int j = 0; j < ans2.size(); j++)
				{
					if (ans2[j].hash == hh)
					{
						i2 = ans_ind2[j];
						break;
					}
				}
			}
			else
			{
				i2 = ans_ind2[ans2.size() - 1];
			}
			subword n;
			n.hash = str.get_hash(l, r);
			n.len = r - l + 1;
			n.c = Code(max(i1, i2), min(i1, i2), i1 >= i2);
			cur_dict.push_back(n);
			break;
		}
	}
	return cur_dict;
}

GeneralAgglomerativeAssembly::GeneralAgglomerativeAssembly(HashString & _hs) : str(_hs), sub_algo(IAssembly())
{
	subalgo_known = false;
	k = -1;
	fwc = new FullWithClipAssembly(_hs);
	bin = new  BinaryAgglomerativeAssembly(_hs);
	naive = new NaiveAssembly(_hs);
}

GeneralAgglomerativeAssembly::GeneralAgglomerativeAssembly(HashString & _hs, int _k) : str(_hs), sub_algo(IAssembly()), k(_k)
{
	subalgo_known = false;
	fwc = new FullWithClipAssembly(_hs);
	bin = new  BinaryAgglomerativeAssembly(_hs);
	naive = new NaiveAssembly(_hs);
}

GeneralAgglomerativeAssembly::GeneralAgglomerativeAssembly(HashString & _hs, IAssembly& _lsa) : str(_hs), sub_algo(_lsa)
{
	subalgo_known = true;
	k = -1;
}

GeneralAgglomerativeAssembly::GeneralAgglomerativeAssembly(HashString & _hs, IAssembly& lsa, int k) : str(_hs), sub_algo(lsa), k(k)
{
	subalgo_known = true;
}

void GeneralAgglomerativeAssembly::f()
{
	part_dicts.clear();
	int parts_sz = (str.size() + k - 1) / k;
	int l = 0, r = k - 1;
	for (int i = 0; i < parts_sz; i++)
	{
		if (r >= str.size())
		{
			r = str.size() - 1;
		}
		get_sub_assembly(l, r);
		part_dicts.push_back(make_tuple(str.get_hash(l, r), l, r));
		l += k;
		r += k;
	}

	while (part_dicts.size() > 1)
	{
		// calculate statistic about hashes
		map < pair < ll, ll >, int > stats;
		for (int i = 0; i < part_dicts.size() - 1; i++)
		{
			ll cur_hash = get<0>(part_dicts[i]);
			ll next_hash = get<0>(part_dicts[i + 1]);

			stats[{cur_hash, next_hash}] ++;
		}

		//get pair with max stat
		int max_res = -1;
		pair < ll, ll > hash_max_pair;
		for (auto x : stats)
		{
			if (x.second > max_res)
			{
				max_res = x.second;
				hash_max_pair = x.first;
			}
		}

		//concatenate all this pairs
		bool add_last = true;
		vector < tuple< ll, int, int> > new_parts;
		for (int i = 0; i < part_dicts.size() - 1; i++)
		{
			ll cur_hash = get<0>(part_dicts[i]);
			ll next_hash = get<0>(part_dicts[i + 1]);

			if (cur_hash == hash_max_pair.first && next_hash == hash_max_pair.second)
			{
				if (i == part_dicts.size() - 2)
					add_last = false;
				dict merged = merge_dicts(str.dp[cur_hash], str.dp[next_hash], get<1>(part_dicts[i]), get<2>(part_dicts[i]), get<2>(part_dicts[i + 1]));
				int nl = get<1>(part_dicts[i]), nr = get<2>(part_dicts[i + 1]);
				ll nhash = str.get_hash(nl, nr);
				if (!str.dp.count(nhash) || (str.dp.count(nhash) && str.dp[nhash].size() > merged.size()))
					str.dp[nhash] = merged;
				new_parts.push_back(make_tuple(nhash, nl, nr));
				i++;
			}
			else
			{
				new_parts.push_back(part_dicts[i]);
			}
		}
		if (add_last)
		{
			new_parts.push_back(part_dicts[part_dicts.size() - 1]);
		}
		part_dicts = vector < tuple<ll, int, int> >(new_parts);
	}
}

void GeneralAgglomerativeAssembly::get_sub_assembly(int l, int r)
{
	if (subalgo_known)
	{
		sub_algo.get_assembly(l, r);;
	}
	else
	{
		int cur_len = r - l + 1;
		if (cur_len <= 100)
			fwc->get_assembly(l, r);
		else
			if (cur_len <= 10000)
				bin->get_assembly(l, r);
			else
				naive->get_assembly(l, r);
	}
}

dict GeneralAgglomerativeAssembly::get_assembly()
{
	if (k == -1)
	{
		for (k = 4; k < str.size() / 2; k++)
		{
			f();
		}
	}
	else
		f();

	return str.dp[get<0>(part_dicts[0])];
}
