#pragma once

#include "HashString.h"
#include "IAssembly.h"

class BinaryAgglomerativeAssembly : public IAssembly
{
private:
	HashString& str;

public:
	BinaryAgglomerativeAssembly(HashString& _hs);
	dict get_assembly(int l, int r);
};