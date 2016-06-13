#pragma once

#include "HashString.h"
#include "IAssembly.h"

class FullWithClipAssembly : public IAssembly
{
private:
	HashString& str;

public:
	FullWithClipAssembly(HashString& _hs);
	dict get_assembly(int l, int r);
};