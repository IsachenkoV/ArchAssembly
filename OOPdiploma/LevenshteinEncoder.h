#pragma once

#include "IEncoder.h"

class LevenshteinEncoder : IEncoder
{
private:
	string path;

public:
	void encode(dict d);
	string get_code(int num);
	LevenshteinEncoder(string file_path);
};