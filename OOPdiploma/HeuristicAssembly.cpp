#include "HeuristicAssembly.h"
#include "FullWithClipAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "NaiveAssembly.h"

dict HeuristicAssembly::merge_dicts(dict ans1, dict ans2, int l, int i, int r)
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

HeuristicAssembly::HeuristicAssembly(HashString & _hs) : str(_hs), sub_algo(IAssembly())
{
	Kmin = Kmax = -1;
	subalgo_known = false;
	use_parts = true;
	use_words = 1;
	fwc = new FullWithClipAssembly(_hs);
	bin = new  BinaryAgglomerativeAssembly(_hs);
	naive = new NaiveAssembly(_hs);
}

HeuristicAssembly::HeuristicAssembly(HashString & _hs, int _kmin, int _kmax, bool _use_parts) : str(_hs), sub_algo(IAssembly())
{
	subalgo_known = false;
	use_parts = _use_parts;
	use_words = 1;
	fwc = new FullWithClipAssembly(_hs);
	bin = new BinaryAgglomerativeAssembly(_hs);
	naive = new NaiveAssembly(_hs);
	Kmin = _kmin;
	Kmax = _kmax;
}

HeuristicAssembly::HeuristicAssembly(HashString & _hs, IAssembly & lsa, bool _use_parts) : str(_hs), sub_algo(lsa)
{
	Kmin = Kmax = -1;
	subalgo_known = true;
	use_parts = _use_parts;
	use_words = 1;
}

HeuristicAssembly::HeuristicAssembly(HashString & _hs, IAssembly & lsa, int _kmin, int _kmax, bool _use_parts) : str(_hs), sub_algo(lsa)
{
	subalgo_known = true;
	use_parts = _use_parts;
	use_words = 1;
	Kmin = _kmin;
	Kmax = _kmax;
}

void HeuristicAssembly::get_sub_assembly(int l, int r)
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

dict HeuristicAssembly::f()
{
	set < pair < int, ll > > queue_of_hashes; // in pair: first - left position, second - hash
	vector < pair < int, int > > segments;
	dict ans;

	int len = str.size();
	segments.push_back(mp(0, len - 1)); // all word

	while (!segments.empty())
	{
		pair < ll, int > max_part; // hash and len
		int max_part_len = -1;
		bool flag = false;
		//for every len
		for (int k = Kmin; k < Kmax; k++)
		{
			//find the best word
			map < ll, pair < int, int> > all_len;
			for (auto segm : segments)
			{
				for (int i = segm.first; i < segm.second - k + 2; i++)
				{
					int l = i, r = i + k - 1;
					ll h_temp = str.get_hash(l, r);

					if (!all_len.count(h_temp))
					{
						all_len[h_temp] = mp(k, r);
					}
					else
					{
						auto x = all_len[h_temp];
						if (x.second < l)
						{
							all_len[h_temp] = mp(x.first + k, r);
						}
					}
				}
			}
			//get best word
			for (auto x : all_len)
			{
				if (!flag || max_part.second <= x.second.first)
				{
					max_part = mp(x.first, x.second.first);
					max_part_len = k;
					flag = true;
				}
			}
		}
		//goes through old segments and erase word
		vector < pair < int, int > > new_segms;
		if (flag)
		{
			//delete finded part from segms
			bool finded = false;
			for (auto x : segments)
			{
				int left_unused = x.first, right_unused = x.first;
				for (int i = x.first; i < x.second - max_part_len + 2; i++)
				{
					int l = i, r = i + max_part_len - 1;
					ll h_temp = str.get_hash(l, r);

					if (h_temp == max_part.first)
					{
						if (!finded)
						{
							finded = true;
							get_sub_assembly(l, r);
						}
						queue_of_hashes.insert(mp(l, h_temp));
						right_unused--;
						if (right_unused >= left_unused)
						{
							int d = right_unused - left_unused + 1;
							if (d < Kmin)
							{
								get_sub_assembly(left_unused, right_unused);;
								queue_of_hashes.insert(mp(left_unused, str.get_hash(left_unused, right_unused)));
							}
							else
								new_segms.push_back(mp(left_unused, right_unused));
						}
						i += max_part_len - 1;
						left_unused = i + 1;
						right_unused = i + 1;
					}
					else
					{
						right_unused++;
					}
				}
				right_unused = x.second;
				if (right_unused >= left_unused)
				{
					int d = right_unused - left_unused + 1;
					if (d < Kmin)
					{
						get_sub_assembly(left_unused, right_unused);;
						queue_of_hashes.insert(mp(left_unused, str.get_hash(left_unused, right_unused)));
					}
					else
						new_segms.push_back(mp(left_unused, right_unused));
				}
			}
			segments = vector < pair < int, int > >(new_segms);

			//using parts in max_part dictionary try to delete more parts
			if (use_parts)
			{
				auto max_part_dict = str.dp[max_part.first];
				bool have_no_word_to_use = true;
				int num_of_word = rand() % (max(1, (int)max_part_dict.size() - str.alp_size - 1));
				for (int i = 0; i < max_part_dict.size(); i++)
				{
					if (max_part_dict[i].c.q == -1) // symbol
						continue;
					if (max_part_dict[i].len >= 4) // bad len
					{
						num_of_word--;
					}
					if (num_of_word == -1)
					{
						max_part_len = max_part_dict[i].len;
						max_part.first = max_part_dict[i].hash;
						have_no_word_to_use = false;
					}
				}
				if (!have_no_word_to_use)
				{
					new_segms.clear();
					for (auto x : segments)
					{
						int left_unused = x.first, right_unused = x.first;
						for (int i = x.first; i < x.second - max_part_len + 2; i++)
						{
							int l = i, r = i + max_part_len - 1;
							ll h_temp = str.get_hash(l, r);

							if (h_temp == max_part.first)
							{
								queue_of_hashes.insert(mp(l, h_temp));
								right_unused--;
								if (right_unused >= left_unused)
								{
									int d = right_unused - left_unused + 1;
									if (d < Kmin)
									{
										get_sub_assembly(left_unused, right_unused);
										queue_of_hashes.insert(mp(left_unused, str.get_hash(left_unused, right_unused)));
									}
									else
										new_segms.push_back(mp(left_unused, right_unused));
								}
								i += max_part_len - 1;
								left_unused = i + 1;
								right_unused = i + 1;
							}
							else
							{
								right_unused++;
							}
						}
						right_unused = x.second;
						if (right_unused >= left_unused)
						{
							int d = right_unused - left_unused + 1;
							if (d < Kmin)
							{
								get_sub_assembly(left_unused, right_unused);
								queue_of_hashes.insert(mp(left_unused, str.get_hash(left_unused, right_unused)));
							}
							else
								new_segms.push_back(mp(left_unused, right_unused));
						}
					}
					segments = vector < pair < int, int > >(new_segms);
				}
			}
		}
		else // flag = false -> algo has no answer (best string)
		{
			for (auto x : segments)
			{
				if (x.second - x.first + 1 > 100)
					cerr << "BAD\n";
				get_sub_assembly(x.first, x.second);
			}
		}
		bool ans_is_empty = true;
		for (auto it = queue_of_hashes.begin(); it != queue_of_hashes.end(); it++)
		{
			if (ans_is_empty)
			{
				ans_is_empty = false;
				ans = str.dp[it->second];
			}
			else
			{
				int i = it->first - 1;
				it++;
				int r;
				if (it != queue_of_hashes.end())
					r = it->first - 1;
				else
					r = len - 1;
				it--;
				ans = merge_dicts(ans, str.dp[it->second], 0, i, r);
			}
		}
	}
	return ans;
}

dict HeuristicAssembly::get_assembly()
{
	if (Kmin != -1 && Kmax != -1)
		return f();

	dict cur_ans;
	for (Kmin = 4; Kmin < 4 + str.size() / 4; Kmin++)
	{
		for (Kmax = Kmin + str.size() / 5; Kmax < str.size() / 2; Kmax++)
		{
			dict ans = f();
			if (cur_ans.size() == 0 || ans.size() < cur_ans.size())
				cur_ans = dict(ans);
		}
	}

	return cur_ans;
}
