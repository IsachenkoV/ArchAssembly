#include "IAssembly.h"
#include "FullWithClipAssembly.h"
#include "FullAssembly.h"
#include "BinaryAgglomerativeAssembly.h"
#include "GeneralAgglomerativeAssembly.h"
#include "HeuristicAssembly.h"
#include "NaiveAssembly.h"
#include "LevenshteinEncoder.h"
#include "HuffmanEncoder.h"

int main()
{
	string inp = "input.txt";
	string out = "output.txt";

	HashString hs = HashString(inp);
	NaiveAssembly asd = NaiveAssembly(hs);
	BinaryAgglomerativeAssembly bas = BinaryAgglomerativeAssembly(hs);
	GeneralAgglomerativeAssembly gas = GeneralAgglomerativeAssembly(hs);
	HeuristicAssembly has = HeuristicAssembly(hs);

	dict ans = gas.get_assembly();

	LevenshteinEncoder encoder = LevenshteinEncoder("my_archive");
	HuffmanEncoder enc2 = HuffmanEncoder("my_arch");
	encoder.encode(ans);
	enc2.encode(ans);
}