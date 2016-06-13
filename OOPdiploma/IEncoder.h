#pragma once
#include "stdafx.h"

class IEncoder
{
public:
	virtual void encode(dict d);
	virtual string get_code(int num);
};