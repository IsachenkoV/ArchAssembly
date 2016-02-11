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

string s;
struct lz {
	int d, l;
	char c;

	lz()
	{
	}

	lz(int _d, int _l, char _c) : d(_d), l(_l), c(_c)
	{
	}
};

bool letters[30];

vector < lz > ans;

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
map < char, string > alph_codes;

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
	for (auto x : ans)
	{
		statistic[x.l]++;
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
	freopen("out.lz", "w", stdout);

	getline(cin, s);
	int let_count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (!letters[s[i] - 'a'])
		{
			string temp = "";
			temp += s[i];
			letters[s[i] - 'a'] = true;
			let_count++;
		}
	}

	int len_alph_code = get_log(let_count);
	int cur_let_num = 0;
	for (int i = 0; i < 30; i++)
	{
		if (letters[i])
		{
			string temp = "";
			for (int j = 0; j < len_alph_code; j++)
			{
				temp += (1 << j) & cur_let_num ? "1" : "0";
			}
			cur_let_num++;
			reverse(temp.begin(), temp.end());
			alph_codes[i + 'a'] = temp;
		}
	}

	int cur_pos = 0;
	int all_len = s.length();
	while (cur_pos < all_len)
	{
		int max_pos = 0, max_len = 0;
		for (int i = 0; i < cur_pos; i++)
		{
			int cur_len = 0;
			while (s[cur_pos + cur_len] == s[i + cur_len])
				cur_len++;
			if (cur_len >= max_len)
			{
				max_len = cur_len;
				max_pos = i;
			}
		}
		int d = max_len > 0 ? cur_pos - max_pos : 0;
		ans.push_back(lz(d, max_len, s[cur_pos + max_len]));
		cur_pos += max_len + 1;
	}

	build_haffm_tree();
	print_haffm_tree(tree);

	int l = 0;
	string long_string = "";
	for (auto x : ans)
	{
		int l_len = get_log(l);
		string temp = "";
		for (int j = 0; j < l_len; j++)
		{
			temp += (1 << j) & x.d ? "1" : "0";
		}
		reverse(temp.begin(), temp.end());
		long_string = long_string + temp + haffm_codes[x.d] + alph_codes[x.c];
		l += x.l + 1;
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