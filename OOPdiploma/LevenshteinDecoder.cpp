#include "LevenshteinDecoder.h"

int LevenshteinDecoder::get_int()
{
	int c = 0;
	while (cur_pos < code.size() && code[cur_pos] == '1')
	{
		cur_pos++;
		c++;
	}
	cur_pos++;
	if (c == 0)
		return 0;

	int n = 1, p = c - 1;
	while (p)
	{
		string temp = "";
		int nn = 0;
		for (int i = 0; i < n; i++)
		{
			temp += code[cur_pos];
			int k = code[cur_pos] == '1' ? 1 : 0;
			nn += (k << (n - i - 1));
			cur_pos++;
		}
		n = nn + (1 << n);
		p--;
	}
	return n;
}

LevenshteinDecoder::LevenshteinDecoder(string path) : file_path(path)
{
	code = "";
}

void LevenshteinDecoder::decode()
{
	ifstream in;
	in.open(file_path.c_str(), ifstream::binary);
	ofstream out;
	out.open((file_path + ".out").c_str());

	vector < string > ans;
	// restore alphabet
	int alp_size, empty_part;
	in >> alp_size >> empty_part;
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
		int q = get_int() + prev_q;
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
