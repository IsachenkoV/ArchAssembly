#include "HuffmanEncoder.h"

HTNode* HuffmanEncoder::build_tree(const vector<Code>& word_concat)
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
	if (nodes.size() == 1)
	{
		return nodes.begin()->second;
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
			return t;
		}
	}
}

void HuffmanEncoder::get_codes(HTNode* v)
{
	if (v->c != -1)
	{
		haffm_codes[v->c] = code_to_haffm_codes;
		return;
	}

	code_to_haffm_codes.push_back('0');
	get_codes(v->left_son);
	code_to_haffm_codes.pop_back();

	code_to_haffm_codes.push_back('1');
	get_codes(v->right_son);
	code_to_haffm_codes.pop_back();
}

void HuffmanEncoder::print_tree(HTNode * v)
{
}

void HuffmanEncoder::encode(dict d)
{
	ofstream out;
	out.open((path + ".ashf").c_str());

	vector < Code > word_concat;
	for (int i = 0; i < d.size(); i++)
	{
		if (d[i].c.q == -1 || d[i].c.r == -1)
			continue;
		word_concat.push_back(d[i].c);
	}

	// coding of min(i1, i2)
	vector < string > r_s;
	int k = 0;
	for (int i = 0; i < word_concat.size(); i++)
	{
		int q_log = get_log(word_concat[i].q);
		string kemp = "";
		for (int i = 0; i <= q_log; i++)
		{
			kemp += (1 << i) & word_concat[i].r ? "1" : "0";
		}
		reverse(kemp.begin(), kemp.end());
		r_s.push_back(kemp);

		int r = word_concat[i].q;
		word_concat[i].q -= k;
		k = r;
	}

	root = build_tree(word_concat);
	get_codes(root);
	print_tree(root);

	string long_string = "";
	int q = 0;
	for (int i = 0; i < word_concat.size(); i++)
	{
		string tempor = get_code(word_concat[i].q) + r_s[i] + (word_concat[i].d == true ? "1" : "0");
		long_string = long_string + tempor;
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
		out << c;
	}

	out.close();
}

string HuffmanEncoder::get_code(int num)
{
	return haffm_codes[num];
}

HuffmanEncoder::HuffmanEncoder(string file_path) : path(file_path)
{
}
