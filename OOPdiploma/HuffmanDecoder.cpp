#include "HuffmanDecoder.h"
#include "stdafx.h"
#include "HuffmanEncoder.h"

int HuffmanDecoder::get_int(HTNode* v)
{
	if (v->c != -1)
		return v->c;
	if (code[cur_pos] == '0')
	{
		cur_pos++;
		return get_int(v->left_son);
	}
	cur_pos++;
	return get_int(v->right_son);
}

HuffmanDecoder::HuffmanDecoder(string path) : file_path(path)
{
}

void HuffmanDecoder::decode()
{
	ifstream in;
	in.open(file_path.c_str(), ifstream::binary);
	ofstream out;
	out.open((file_path + ".out").c_str());

	vector < string > ans;
	// restore alphabet
	int alp_size, empty_part, tree_size;
	in >> alp_size >> empty_part >> tree_size;

	stack < HTNode* > t_stack;

	for (int i = 0; i < tree_size; i++)
	{
		int x;
		in >> x;
		if (x == 1)
		{
			in >> x;
			t_stack.push(new HTNode(x - 1));
		}
		else
		{
			HTNode* r = t_stack.top();
			t_stack.pop();
			HTNode* l = t_stack.top();
			t_stack.pop();
			HTNode* delta = new HTNode(-1);
			delta->left_son = l;
			delta->right_son = r;
			t_stack.push(delta);
		}
	}
	root = t_stack.top();

	char temp;
	in.get(temp);

	for (int i = 0; i < alp_size; i++)
	{
		char x;
		in.get(x);
		string temp = "";
		temp += x;
		ans.push_back(temp);
	}

	// restore code
	char c = 0;
	
	while (in.read(&c, 1))
	{
		for (int i = 0; i < 8; i++)
		{
			if (c & (1 << i))
			{
				code += "1";
			}
			else
			{
				code += "0";
			}
		}
	}

	cur_pos = 0;
	int prev_q = 0;
	while (cur_pos < code.size() - empty_part)
	{
		int q = get_int(root) + prev_q;
		int q_log = get_log(q);
		int r = 0;
		for (int i = 0; i <= q_log; i++)
		{
			int k = code[cur_pos] == '1' ? 1 : 0;
			r += (k << (q_log - i));
			cur_pos++;
		}
		int d = code[cur_pos] == '1' ? 1 : 0;
		cur_pos++;

		string temp = "";
		if (d == 1)
		{
			temp = ans[q] + ans[r];
		}
		else
		{
			temp = ans[r] + ans[q];
		}
		ans.push_back(temp);
		prev_q = q;
	}

	out << ans[ans.size() - 1];
	in.close();
	out.close();
}

