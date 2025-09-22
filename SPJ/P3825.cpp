// Author: HeRaNO
#include "testlib.h"

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);

	int n = inf.readInt();

	std::string jans = ans.readToken(), pans;

	if (jans == "-1")
	{
		pans = ouf.readToken("-1");
		quitf(_ok, "OK");
	}

	pans = ouf.readToken("[ABC]+");

	if (pans.size() != n)
		quitf(_wa, "the length of participant's answer differs from jury.");

	if (pans == jans)
		quitf(_ok, "OK");

	int d = inf.readInt();
	std::string S = inf.readToken();

	for (int i = 0; i < n; i++)
		if (toupper(S[i]) == pans[i])
			quitf(_wa, "at position %d, map conflicts with the car chosen.", i + 1);

	int m = inf.readInt();
	for (int k = 1; k <= m; k++)
	{
		int i = inf.readInt() - 1; inf.readSpace();
		char hi = inf.readChar();
		int j = inf.readInt() - 1; inf.readSpace();
		char hj = inf.readChar();
		if (pans[i] == hi && pans[j] != hj)
			quitf(_wa, "answer doesn't meet the requirement %d.", k);
	}

	quitf(_ok, "OK");
	return 0;
}