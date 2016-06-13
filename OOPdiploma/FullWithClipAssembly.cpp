#include "IAssembly.h"
#include "HashString.h"
#include "FullWithClipAssembly.h"

FullWithClipAssembly::FullWithClipAssembly(HashString& _hs) : str(_hs)
{
}

dict FullWithClipAssembly::get_assembly(int l, int r)
{
	ll h_temp = str.get_hash(l, r);
	if (str.dp.count(h_temp))
		return str.dp[h_temp];

	dict cur_ans;
	bool flag = false;
	for (int i = l; i < r; i++)
	{
		dict ans1 = get_assembly(l, i);
		dict ans2 = get_assembly(i + 1, r);
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
				n.hash = h_temp;
				n.len = r - l + 1;
				n.c = Code(max(i1, i2), min(i1, i2), i1 >= i2);
				cur_dict.push_back(n);
				break;
			}
		}

		if (!flag || (cur_dict.size() < cur_ans.size()))
		{
			cur_ans = dict(cur_dict);
			flag = true;
		}
	}

	str.dp[h_temp] = dict(cur_ans);
	return str.dp[h_temp];
}