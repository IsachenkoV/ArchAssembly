#pragma once

#include "stdafx.h"

class HashString
{
private:
	string s; // исходная строка
	bool* letters = new bool[300]; // использованные буквы алфавита
	vector<ll> h = vector <ll>(MAXLEN); // хеш-функция
	vector<ll> pows = vector <ll>(MAXLEN); // степени простого числа P
	vector<char> alph = vector <char>();
	void initialize(); 

public:
	map < ll, dict > dp = map <ll, dict>(); // контейнер для хранения найденных схем конкатенации
	int alp_size; // размер алфавита

	HashString(const string& file_path);

	ll get_hash(int l, int r); // функция для нахождения хеша подстроки
	vector < ll > get_alph_hashes(); // нахождения хешей всех букв
	size_t size(); // размер строки
	vector <char> get_alph();
};
