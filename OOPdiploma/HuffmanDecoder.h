#pragma once
#include "IDecoder.h"
#include "stdafx.h"
#include "HuffmanEncoder.h"

class HuffmanDecoder : IDecoder
{
private:
	int get_int(HTNode* v);
	string file_path;
	string code;
	HTNode* root;
	int cur_pos;

public:
	HuffmanDecoder(string path);
	void decode();
};
