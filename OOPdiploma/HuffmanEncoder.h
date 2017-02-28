#pragma once

#include "encoding.h"
#include "IEncoder.h"
#include "HashString.h"

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
	map < int, string > haffm_codes; // коды Хаффмана некоторых чисел
	string code_to_haffm_codes = "";
	string path; // путь к архиву
	HTNode* root; // корень дерева Хаффмана
	HTNode* build_tree(const vector<Code>&  word_concat); // функция для построения дерева Хаффмана
	void get_codes(HTNode* v); // функция для построения кодов натуральных чисел
	void print_tree(HTNode* v); // функция для печати дерева Хаффмана
	HashString& hs;
	vector < int > hftr;
	int trsz;

public:
	void encode(dict d);
	string get_code(int num);
	HuffmanEncoder(string file_path, HashString& hs);
};