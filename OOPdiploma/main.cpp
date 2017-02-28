#include "IAssembly.h"
#include "FullWithClipAssembly.h"
#include "FullAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "GeneralAgglomerativeAssembly.h"
#include "HeuristicAssembly.h"
#include "NaiveAssembly.h"
#include "LevenshteinEncoder.h"
#include "HuffmanEncoder.h"
#include "LevenshteinDecoder.h"
#include "HuffmanDecoder.h"

extern "C"
__declspec(dllexport)
void 
__cdecl
encode_file(const char* path, int sz, int* args)
{
	string fpath = string(path);

	ofstream cerr;
	cerr.open("C:\\Users\\Владимир\\Documents\\err.txt");
	cerr << fpath;
	cerr.close();

	HashString hs = HashString(fpath);

	if (args[1] == 1)
	{
		HuffmanEncoder encoder = HuffmanEncoder(fpath, hs);
		dict res = dict();
		if (sz == 2)
		{
			NaiveAssembly naive = NaiveAssembly(hs);
			FullWithClipAssembly fwc = FullWithClipAssembly(hs);
			BinaryAgglomerativeAssembly bin = BinaryAgglomerativeAssembly(hs);
			switch (args[0])
			{
			case 3:
				res = naive.get_assembly(0, hs.size() - 1);
				break;
			case 4:
				res = fwc.get_assembly(0, hs.size() - 1);
				break;
			case 5:
				res = fwc.get_assembly(0, hs.size() - 1);
				break;
			case 6:
				res = bin.get_assembly(0, hs.size() - 1);
				break;
			}
		}
		if (sz == 4)
		{
			bool auto_algo = false;
			IAssembly subalgo;
			switch (args[2])
			{
			case 1:
				subalgo = NaiveAssembly(hs);
				break;
			case 2:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 3:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 4:
				subalgo = BinaryAgglomerativeAssembly(hs);
				break;
			case 5:
				auto_algo = true;
				break;
			}

			GeneralAgglomerativeAssembly* gaa = new GeneralAgglomerativeAssembly(hs);
			if (args[3] == -1 && auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs);
			}
			if (args[3] != -1 && auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs, args[3]);
			}
			if (args[3] == -1 && !auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs, subalgo);
			}
			if (args[3] != -1 && !auto_algo)
				gaa = new GeneralAgglomerativeAssembly(hs, subalgo, args[3]);
			res = gaa->get_assembly();
		}
		if (sz == 7)
		{
			bool auto_algo = false;
			IAssembly subalgo;
			switch (args[2])
			{
			case 1:
				subalgo = NaiveAssembly(hs);
				break;
			case 2:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 3:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 4:
				subalgo = BinaryAgglomerativeAssembly(hs);
				break;
			case 5:
				auto_algo = true;
				break;
			}
			HeuristicAssembly* ha = new HeuristicAssembly(hs);
			int mink = args[3], maxk = args[4];
			bool use_ds = false;
			if (args[5] == 1)
				use_ds = true;

			if (mink == -1 && maxk == -1 && auto_algo)
				ha = new HeuristicAssembly(hs);
			if (mink != -1 && maxk != -1 && auto_algo)
				ha = new HeuristicAssembly(hs, mink, maxk, use_ds);
			if (mink == -1 && maxk == -1 && !auto_algo)
				ha = new HeuristicAssembly(hs, subalgo, use_ds);
			if (mink != -1 && maxk != -1 && !auto_algo)
				ha = new HeuristicAssembly(hs, subalgo, mink, maxk, use_ds);
			res = ha->get_assembly();
		}

		encoder.encode(res);
	}
	else
	{
		LevenshteinEncoder encoder = LevenshteinEncoder(fpath, hs);
		dict res = dict();
		if (sz == 2)
		{
			NaiveAssembly naive = NaiveAssembly(hs);
			FullWithClipAssembly fwc = FullWithClipAssembly(hs);
			BinaryAgglomerativeAssembly bin = BinaryAgglomerativeAssembly(hs);
			switch (args[0])
			{
			case 3:
				res = naive.get_assembly(0, hs.size() - 1);
				break;
			case 4:
				res = fwc.get_assembly(0, hs.size() - 1);
				break;
			case 5:
				res = fwc.get_assembly(0, hs.size() - 1);
				break;
			case 6:
				res = bin.get_assembly(0, hs.size() - 1);
				break;
			}
		}
		if (sz == 4)
		{
			bool auto_algo = false;
			IAssembly subalgo;
			switch (args[2])
			{
			case 1:
				subalgo = NaiveAssembly(hs);
				break;
			case 2:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 3:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 4:
				subalgo = BinaryAgglomerativeAssembly(hs);
				break;
			case 5:
				auto_algo = true;
				break;
			}

			GeneralAgglomerativeAssembly* gaa = new GeneralAgglomerativeAssembly(hs);
			if (args[3] == -1 && auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs);
			}
			if (args[3] != -1 && auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs, args[3]);
			}
			if (args[3] == -1 && !auto_algo)
			{
				gaa = new GeneralAgglomerativeAssembly(hs, subalgo);
			}
			if (args[3] != -1 && !auto_algo)
				gaa = new GeneralAgglomerativeAssembly(hs, subalgo, args[3]);
			res = gaa->get_assembly();
		}
		if (sz == 7)
		{
			bool auto_algo = false;
			IAssembly subalgo;
			switch (args[2])
			{
			case 1:
				subalgo = NaiveAssembly(hs);
				break;
			case 2:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 3:
				subalgo = FullWithClipAssembly(hs);
				break;
			case 4:
				subalgo = BinaryAgglomerativeAssembly(hs);
				break;
			case 5:
				auto_algo = true;
				break;
			}
			HeuristicAssembly* ha = new HeuristicAssembly(hs);
			int mink = args[3], maxk = args[4];
			bool use_ds = false;
			if (args[5] == 1)
				use_ds = true;

			if (mink == -1 && maxk == -1 && auto_algo)
				ha = new HeuristicAssembly(hs);
			if (mink != -1 && maxk != -1 && auto_algo)
				ha = new HeuristicAssembly(hs, mink, maxk, use_ds);
			if (mink == -1 && maxk == -1 && !auto_algo)
				ha = new HeuristicAssembly(hs, subalgo, use_ds);
			if (mink != -1 && maxk != -1 && !auto_algo)
				ha = new HeuristicAssembly(hs, subalgo, mink, maxk, use_ds);
			res = ha->get_assembly();
		}
		encoder.encode(res);
	}
}

extern "C"
__declspec(dllexport)
void
__cdecl
decode_file(const char* path, int type)
{
	if (type == 1)
	{
		HuffmanDecoder hd = HuffmanDecoder(string(path));
		hd.decode();
	}
	else
	{
		LevenshteinDecoder levd = LevenshteinDecoder(string(path));
		levd.decode();
	}
}

int main()
{
	//string s = "C:\\Users\\Владимир\\Documents\\doc.txt";
	//int args[2];
	//args[0] = 3;
	//args[1] = 1;
	//encode_file(s.c_str(), 2, args);
	
	string s = "C:\\Users\\Владимир\\Documents\\doc.txt.ashf";
	int type = 1;
	decode_file(s.c_str(), type);
}