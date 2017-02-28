#include "HashString.h"

void HashString::initialize()
{
	alp_size = 0;
	dp.clear();
	fill(letters, letters + 300, false);
	fill(h.begin(), h.end(), 0);
	fill(pows.begin(), pows.end(), 0);

	// get powers and hash of string
	h[0] = s[0] + 1;
	pows[0] = 1;
	int sz = min((int)s.size(), MAXLEN);
	for (int i = 1; i < sz; i++)
	{
		pows[i] = pows[i - 1] * p;
		h[i] = h[i - 1] + (s[i] + 1) * pows[i];
	}
	vector < string > alph;

	// add all letters to dictionary
	dict temp_dict;
	for (int i = 0; i < s.length(); i++)
	{
		if (!letters[s[i]])
		{
			string temp;
			temp = s[i];
			alph.push_back(temp);

			ll temp_h = s[i] + 1;
			temp_h = temp_h * get_power(MAX_POW);

			// all letters have word (-1, -1, 0)
			temp_dict.push_back(subword(temp_h, 1, Code(-1, -1, 0)));
			letters[s[i]] = true;
		}
	}
	// initialize all symbols with all alphabet
	alp_size = temp_dict.size();
	for (auto x : temp_dict)
	{
		dp[x.hash] = dict(temp_dict);
	}
}

HashString::HashString(const string& file_path)
{
	ifstream in;
	in.open(file_path.c_str());
	char c;
	while (in.get(c))
	{
		s += c;
	}
	initialize();
}

ll HashString::get_hash(int l, int r)
{
	ll h_temp = h[r];
	if (l > 0)
		h_temp -= h[l - 1];
	h_temp = h_temp * get_power(MAX_POW - l);
	return h_temp;
}

vector<ll> HashString::get_alph_hashes()
{
	vector < ll > ret_val;
	bool let[300];
	fill(let, let + 300, 0);
	for (int i = 0; i < s.size(); i++)
	{
		if (!let[s[i]])
		{
			ll temp_h = get_hash(i, i);
			alph.push_back(s[i]);
			ret_val.push_back(temp_h);
			let[s[i]] = true;
		}
	}
	return ret_val;
}

size_t HashString::size()
{
	return s.size();
}

vector<char> HashString::get_alph()
{
	vector < char > ret_val;
	bool let[300];
	fill(let, let + 300, 0);
	for (int i = 0; i < s.size(); i++)
	{
		if (!let[s[i]])
		{
			ret_val.push_back(s[i]);
			let[s[i]] = true;
		}
	}
	return ret_val;
}
