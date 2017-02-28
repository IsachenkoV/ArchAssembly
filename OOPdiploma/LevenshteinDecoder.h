#pragma once
#include "IDecoder.h"
#include "stdafx.h"

class LevenshteinDecoder : IDecoder
{
private:
	string code;
	string file_path;
	int cur_pos;

public:
	LevenshteinDecoder(string path);
	int get_int();
	void decode();
};