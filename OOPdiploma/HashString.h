#pragma once

#include "stdafx.h"

class HashString
{
private:
	string s;
	bool* letters = new bool[300];
	vector<ll> h = vector <ll>(MAXLEN);
	vector<ll> pows = vector <ll>(MAXLEN);

	void initialize();

public:
	map < ll, dict > dp = map <ll, dict>();
	int alp_size;

	HashString(const string& file_path);

	ll get_hash(int l, int r);
	vector < ll > get_alph_hashes();
	size_t size();
};
