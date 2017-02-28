#pragma once
#include "stdafx.h"

class IEncoder
{
public:
	virtual void encode(dict d);		 // функция кодирования найденной схемы конкатенации
	virtual string get_code(int num);	 // префиксный код натурального числа num
};