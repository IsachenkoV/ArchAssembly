#pragma once
#include "IAssembly.h"
#include "HashString.h"

class NaiveAssembly : public IAssembly
{
private:
	HashString& str;

public:
	NaiveAssembly(HashString& _hs);
	dict get_assembly(int l, int r);
};