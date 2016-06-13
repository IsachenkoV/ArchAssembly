#pragma once

#include "IAssembly.h"
#include "HashString.h"
#include "FullWithClipAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "NaiveAssembly.h"

class HeuristicAssembly : public IAssembly
{
private:
	bool subalgo_known, use_parts;
	HashString& str;
	IAssembly& sub_algo;
	int Kmin, Kmax, use_words;
	dict merge_dicts(dict a, dict b, int l, int i, int r);
	BinaryAgglomerativeAssembly* bin;
	FullWithClipAssembly* fwc;
	NaiveAssembly* naive;
	void get_sub_assembly(int l, int r);
	dict f();

public:
	HeuristicAssembly(HashString& _hs); // auto definition k and lsa
	HeuristicAssembly(HashString& _hs, int _kmin, int _kmax, bool _use_parts); // auto definition lsa
	HeuristicAssembly(HashString& _hs, IAssembly& lsa, bool _use_parts); // auto definition K
	HeuristicAssembly(HashString& _hs, IAssembly& lsa, int _kmin, int _kmax, bool _use_parts);
	dict get_assembly();
};