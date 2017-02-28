#pragma once

#include "HashString.h"
#include "IAssembly.h"
#include "FullWithClipAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "NaiveAssembly.h"

class GeneralAgglomerativeAssembly : IAssembly
{
private:
	bool subalgo_known; // указан ли алгоритм для нахождения схемы конкатенации для подслов
	HashString& str;
	IAssembly& sub_algo; // алгоритм для нахождения схемы конкатенации для подслов
	BinaryAgglomerativeAssembly* bin;
	FullWithClipAssembly* fwc;
	NaiveAssembly* naive;
	int k; // параметр разбиения строки
	dict merge_dicts(dict a, dict b, int l, int i, int r); // функция для объединения схем конкатенации
	void f();
	vector < tuple< ll, int, int> > part_dicts; // вектор с границами разбиения строки
	void get_sub_assembly(int l, int r); // автоматическое определение алгоритма для нахождения схемы конкатенации подслов

public:
	GeneralAgglomerativeAssembly(HashString& _hs); // автоматическое определение k и sub_algo
	GeneralAgglomerativeAssembly(HashString& _hs, int k); // автоматическое определение sub_algo
	GeneralAgglomerativeAssembly(HashString& _hs, IAssembly& lsa); // автоматическое определение k
	GeneralAgglomerativeAssembly(HashString& _hs, IAssembly& lsa, int k);
	dict get_assembly();
};