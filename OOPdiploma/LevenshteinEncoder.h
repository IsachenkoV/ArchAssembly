#pragma once

#include "IEncoder.h"
#include "HashString.h"

class LevenshteinEncoder : IEncoder
{
private:
	string path; // путь к архиву
	HashString& hs;
public:
	void encode(dict d);
	string get_code(int num);
	LevenshteinEncoder(string file_path, HashString& _hs);
};