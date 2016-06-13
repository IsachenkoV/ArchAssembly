#pragma once

#include "HashString.h"
#include "IAssembly.h"

class FullAssembly : public IAssembly
{
private:
	HashString& str;

public:
	FullAssembly(HashString& _hs);
	dict get_assembly(int l, int r);
};