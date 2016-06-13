#pragma once

#include "encoding.h"
#include "IEncoder.h"

struct HTNode
{
	int c;
	HTNode* left_son;
	HTNode* right_son;

	HTNode()
	{
		c = -1;
		left_son = right_son = NULL;
	}

	HTNode(int _c)
	{
		c = _c;
		left_son = right_son = NULL;
	}

	void print_haffm_tree(HTNode* t)
	{
		if (t->c != -1)
		{
			printf("%d", t->c);
			return;
		}
		printf("%d", 0);
		print_haffm_tree(t->left_son);
		printf("%d", 1);
		print_haffm_tree(t->right_son);
		return;
	}
};

class HuffmanEncoder : IEncoder
{
private:
	map < int, string > haffm_codes;
	string code_to_haffm_codes = "";
	string path;
	HTNode* root;
	HTNode* build_tree(const vector<Code>& word_concat);
	void get_codes(HTNode* v);
	void print_tree(HTNode* v);

public:
	void encode(dict d);
	string get_code(int num);
	HuffmanEncoder(string file_path);
};