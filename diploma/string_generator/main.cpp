#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

using namespace std;

const int MAXLEN = 100000;
const int MAXALP = 2;

int main()
{
	freopen("input.txt", "w", stdout);

	srand(time(NULL));
	//(rand() + 1) % 
	int len = MAXLEN;

	for (int i = 0; i < len; i++) {
		int x = (rand() + 1) % MAXALP;
		printf("%c", ('a' + x));
	}
	return 0;
}