#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cmath>

using namespace std;

typedef long long ll;
typedef long double ld;

#define mp make_pair
#define mt(a, b, c) mp(a, mp(b, c))
typedef pair <string, ll> str;

vector < str > dict;
string s;

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
vector < Code > word_concat;
const int MAXLEN = 1005000;
const int p = 31;

bool letters[30];
ll h[MAXLEN], pows[MAXLEN];

vector < string > ans;
vector < string > real_ans;

struct HTNode
{
	int c;
	HTNode* left_son;
	HTNode* right_son;

	HTNode()
	{
		c = -1;
		left_son = right_son = NULL;
	}

	HTNode(int _c)
	{
		c = _c;
		left_son = right_son = NULL;
	}
};

HTNode* tree;
map < int, string > haffm_codes;

inline void init_ans()
{
	for (int i = 0; i < 30; i++)
	{
		if (letters[i])
		{
			char x = 'a' + i;
			string t = "";
			t.push_back(x);
			ans.push_back(t);
		}
	}
}

void stupid_solution()
{
	int sz = s.size();
	for (int i = 0; i < (1 << sz); i++)
	{
		ans.clear();
		init_ans();
		int cur_pos = 0;
		bool bad = false;
		while (cur_pos < sz)
		{
			string temp = "";
			while (cur_pos < sz && (i & (1 << cur_pos)))
			{
				temp.push_back(s[cur_pos]);
				cur_pos++;
			}
			if (cur_pos < sz)
			{
				temp.push_back(s[cur_pos]);
				cur_pos++;
			}

			bool flag = false;
			for (int j = 0; j < ans.size(); j++)
			{
				if (ans[j].compare(temp) == 0)
				{
					flag = true;
					ans.push_back(temp);
					break;
				}
			}
			if (!flag)
			{
				for (int k = 0; k < ans.size(); k++)
				{
					for (int j = 0; j < ans.size(); j++)
					{
						string t = ans[k] + ans[j];
						if (t.compare(temp) == 0)
						{
							ans.push_back(temp);
							flag = true;
							break;
						}
					}
					if (flag)
						break;
				}
			}
			if (!flag)
			{
				bad = true;
				break;
			}
		}
		if (!bad)
		{
			if (real_ans.size() == 0 || real_ans.size() > ans.size())
			{
				real_ans = vector < string >(ans);
			}
		}
	}
}

string code_to_haffm_codes;

void dfs(HTNode* v)
{
	if (v->c != -1)
	{
		haffm_codes[v->c] = code_to_haffm_codes;
		return;
	}

	code_to_haffm_codes.push_back('0');
	dfs(v->left_son);
	code_to_haffm_codes.pop_back();

	code_to_haffm_codes.push_back('1');
	dfs(v->right_son);
	code_to_haffm_codes.pop_back();

	return;
}

void build_haffm_tree()
{
	set < pair <  int, HTNode* > > nodes;
	map < int, int > statistic;
	for (Code x : word_concat)
	{
		statistic[x.q]++;
	}

	for (auto x : statistic)
	{
		nodes.insert(mp(x.second, new HTNode(x.first)));
	}

	while (!nodes.empty())
	{
		int k1 = nodes.begin()->first;
		HTNode* t1 = nodes.begin()->second;
		nodes.erase(nodes.begin());

		int k2 = nodes.begin()->first;
		HTNode* t2 = nodes.begin()->second;
		nodes.erase(nodes.begin());

		int s = k1 + k2;
		HTNode* t = new HTNode();
		t->left_son = t1;
		t->right_son = t2;
		nodes.insert(mp(s, t));

		if (nodes.size() == 1)
		{
			tree = t;
			break;
		}
	}
	code_to_haffm_codes = "";
	dfs(tree);
}

void print_haffm_tree(HTNode* t)
{
	if (t->c != -1)
	{
		printf("%d", t->c);
		return;
	}
	printf("%d", 0);
	print_haffm_tree(t->left_son);
	printf("%d", 1);
	print_haffm_tree(t->right_son);
	return;
}

int get_log(int k)
{
	if (k < 0)
		throw new exception("negative!");
	if (k == 0)
		return 1;
	int i = 1;
	while ((1 << i) < k)
		i++;
	return i;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("asd", "w", stdout);

	getline(cin, s);

	h[0] = s[0] - 'a' + 1;
	pows[0] = 1;
	int sz = min((int)s.size(), MAXLEN);
	for (int i = 1; i < sz; i++)
	{
		pows[i] = pows[i - 1] * p;
		h[i] = h[i - 1] + (s[i] - 'a' + 1) * pows[i];
	}

	dict.clear();
	ans.clear();
	word_concat.clear();
	real_ans.clear();
	// add all letters to dictionary
	for (int i = 0; i < s.length(); i++)
	{
		if (!letters[s[i] - 'a'])
		{
			string temp = "";
			temp += s[i];
			dict.push_back(mp(temp, temp[0] - 'a' + 1));
			letters[s[i] - 'a'] = true;
		}
	}

	int cur_position = 0;
	int all_len = s.length();
	int r_max = -1;
	while (cur_position < all_len)
	{
		int cur_max_len = -1;
		string max_len_str = "";
		bool new_word = false;
		ll cur_hash;
		Code next_code;

		for (int i = 0; i < dict.size(); i++)
		{
			str s1 = dict[i];
			string temp = s1.first;
			int temp_len = temp.size();

			ll dh = h[cur_position + temp_len - 1];
			if (cur_position > 0)
				dh -= h[cur_position - 1];

			if (s1.second*pows[cur_position] == dh && (s.substr(cur_position, temp_len)).compare(temp) == 0)
			{
				if (temp_len > cur_max_len)
				{
					cur_max_len = temp_len;
					max_len_str = temp;
					new_word = false;
					next_code = Code(i, -1, false);
				}

				for (int j = 0; j < dict.size(); j++)
				{
					str s2 = dict[j];
					string temp = s1.first + s2.first;
					int temp_len = temp.size();
					ll temp_hash = s1.second + (s2.second) * pows[s1.first.size()];

					ll dh = h[cur_position + temp_len - 1];
					if (cur_position > 0)
						dh -= h[cur_position - 1];

					if (temp_len > cur_max_len && temp_hash*pows[cur_position] == dh)
					{
						if ((s.substr(cur_position, temp_len)).compare(temp) == 0)
						{
							cur_hash = temp_hash;
							cur_max_len = temp_len;
							max_len_str = temp;
							new_word = true;

							int q = max(i, j), r = min(i, j);
							bool x = (i != q);
							next_code = Code(q, r, x);
						}
					}
				}
			}
		}

		if (new_word)
			dict.push_back(mp(max_len_str, cur_hash));
		r_max = max(r_max, next_code.r);
		//if (word_concat.size() != 0)
		//	next_code.q -= word_concat[word_concat.size() - 1].q;
		word_concat.push_back(next_code);
		cur_position += cur_max_len;
	}

	/* There is stupid solution with O(2^len) and out to output.txt
	stupid_solution();

	for (str s1 : dict)
	{
	cout << s1.first << "\n";
	}
	cout << word_concat.size() << "\n";

	for (Code x : word_concat)
	{
	cout << x.q << " " << x.r << " " << x.d << "\n";
	}

	cout << "\nOOPS\n";
	for (int i = 0; i < real_ans.size(); i++)
	{
	cout << real_ans[i] << "\n";
	}
	*/

	/* old solution
	int r_log = 0;
	while ((1 << r_log) < r_max)
	r_log++;

	// r_log" " -> alphabet -> number of triples" " -> tree -> codes of q -> codes of r -> codes of d
	printf("%d ", r_log);
	int n_i = 0;
	while (dict[n_i].first.size() == 1)
	{
	cout << dict[n_i].first;
	n_i++;
	}

	printf("%d ", word_concat.size());

	build_haffm_tree();
	print_haffm_tree(tree);

	string qs = "", rs = "", ds = "";
	for (auto x : word_concat)
	{
	qs += haffm_codes[x.q];
	string kemp = "";
	for (int i = 0; i <= r_log; i++)
	{
	kemp += (1 << i) & x.r ? "1" : "0";
	}
	reverse(kemp.begin(), kemp.end());
	rs += kemp;
	ds += x.d == true ? "1" : "0";
	}

	string long_string = qs + rs + ds;
	*/

	// new: tree->" "->alphabet" "->number of triples" "->codes
	build_haffm_tree();
	print_haffm_tree(tree);
	printf(" ");

	int n_i = 0;
	while (dict[n_i].first.size() == 1)
	{
		cout << dict[n_i].first;
		n_i++;
	}

	printf(" %d ", word_concat.size());
	string long_string = "";
	int q = 0;
	for (auto x : word_concat)
	{
		int q_log = get_log(q);
		string kemp = "";
		for (int i = 0; i <= q_log; i++)
		{
			kemp += (1 << i) & x.r ? "1" : "0";
		}
		reverse(kemp.begin(), kemp.end());
		long_string = long_string + haffm_codes[x.q] + kemp + (x.d == true ? "1" : "0");
		q++;
	}

	int l_str_size = long_string.size();
	int cur_p = 0;
	while (cur_p < l_str_size)
	{
		unsigned char c = 0;
		for (int i = 0; i < min(8, l_str_size - cur_p); i++)
		{
			int t = long_string[i + cur_p] == '0' ? 0 : 1;
			c += (t << i);
		}
		cur_p += 8;
		printf("%c", c);
	}

	return 0;
}