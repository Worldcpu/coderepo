#include "../testlib.h"
#include <bits/stdc++.h>

const int K = 64;
using ll = long long;
std::bitset<256> ba, bb, bc;
int readAns(InStream& stream, TResult bad_verdict, ll a, ll b, ll c) {
	int k = stream.readInt(-1, K, "k");
	if (k == -1) return -1;
	ba.reset(), bb.reset(), bc.reset(), ba ^= a, bb ^= b, bc ^= c;
	for (int i = 1; i <= k; ++i) {
		int o = stream.readInt(1, 4, "op");
		if (o == 1) ba <<= 1;
		else if (o == 2) bb >>= 1;
		else if (o == 3) ba ^= bb;
		else bb ^= ba;
	}
	if (ba != bc || bb != bc) 
		stream.quitf(bad_verdict, "invalid construction on (%lld, %lld, %lld)", a, b, c);
	return k;
}

int resmax = 0;
void check() {
	ll a = inf.readLong(), b = inf.readLong(), c = inf.readLong();
	int pk = readAns(ouf, _wa, a, b, c);
	int jk = readAns(ans, _fail, a, b, c);
	if (pk == -1 && jk != -1) 
		ouf.quitf(_wa, "Jury has found an answer on (%lld, %lld, %lld) while participant hasn't", a, b, c);
	if (pk != -1 && jk == -1) 
		ans.quitf(_fail, "Participant has found an answer on (%lld, %lld, %lld) while jury hasn't", a, b, c);
	resmax = std::max(resmax, pk);
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);
	int t = inf.readInt();
	for (int i = 1; i <= t; ++i) check();
	if (!ouf.seekEof()) ouf.quitf(_pe, "extra output");
	if (!ans.seekEof()) ans.quitf(_fail, "extra output on jury solution");
	quitf(_ok, "ok maximum cost is %d", resmax);
}