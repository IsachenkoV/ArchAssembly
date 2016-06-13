#pragma once

#include "HashString.h"
#include "IAssembly.h"
#include "FullWithClipAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "NaiveAssembly.h"

class GeneralAgglomerativeAssembly : IAssembly
{
private:
	bool subalgo_known;
	HashString& str;
	IAssembly& sub_algo;
	BinaryAgglomerativeAssembly* bin;
	FullWithClipAssembly* fwc;
	NaiveAssembly* naive;
	int k;
	dict merge_dicts(dict a, dict b, int l, int i, int r);
	void f();
	vector < tuple< ll, int, int> > part_dicts;
	void get_sub_assembly(int l, int r);

public:
	GeneralAgglomerativeAssembly(HashString& _hs); // auto definition k and lsa
	GeneralAgglomerativeAssembly(HashString& _hs, int k); // auto definition lsa
	GeneralAgglomerativeAssembly(HashString& _hs, IAssembly& lsa); // auto definition K
	GeneralAgglomerativeAssembly(HashString& _hs, IAssembly& lsa, int k);
	dict get_assembly();
};