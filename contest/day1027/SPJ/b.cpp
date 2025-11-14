#include "../../testlib.h"
#include <bitset>
using namespace std;
const int MAXN=77000;
const int MAXM=110000;
const int M=(1e5/32+1)*32;
bitset<MAXM> A, B, C, A2, B2;
int a[MAXN], b[MAXN];
inline void shift(bitset<MAXM>& b, int k)
{
	if (k>=0) b<<=k; else b>>=-k;
}
int first(bitset<MAXM> b)
{
	for (int i=0; i<M; i++)
		if (b[i]) return i;
}
int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	int n=inf.readInt();
	for (int i=1; i<=n; i++) a[i]=inf.readInt();
	for (int i=1; i<=n; i++) b[i]=inf.readInt();
	for (int i=1; i<=n; i++) A.set(a[i]);
	for (int i=1; i<=n; i++) B.set(b[i]);
	int dx=ouf.readInt(), dy=ouf.readInt();
	C=A; shift(C, dx); C&=B;
	B2=B; B2^=C; shift(C, -dx);
	A2=A; A2^=C; shift(A2, dy);
	if(A2==B2) quitf(_ok, "The answer is correct.");
	else quitf(_wa, "The answer is wrong.");
	return 0;
}
