#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>

typedef long long ll;
const int Q = 20001;
const int N = 100001;
const ll P = 1ll << 31;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

int T;
struct Query {
	int n,m,a,id;
	friend bool operator <(const Query &x,const Query &y) {
		return x.a < y.a;
	}
} q[Q];

int mk[N],p[N],tot; ll sgm[N],pw[N],mu[N];
int number[N];
bool cmp(int x,int y) { return sgm[x] < sgm[y]; }

void Seive() {
	sgm[1] = pw[1] = mu[1] = 1;
	for(int i = 2;i < N;i++) {
		if(!mk[i]) {
			p[++tot] = i;
			sgm[i] = i + 1, pw[i] = i;
			mu[i] = P - 1;
		}
		for(int j = 1;j <= tot && p[j] * i < N;j++) {
			mk[i * p[j]] = true;
			if(i % p[j]) {
				pw[i * p[j]] = p[j];
				sgm[i * p[j]] = sgm[i] * (p[j] + 1);
				mu[i * p[j]] = P - mu[i];
			} else {
				pw[i * p[j]] = pw[i] * p[j];
				if(i == pw[i]) sgm[i * p[j]] = sgm[i] * p[j] + 1;
				else sgm[i * p[j]] = sgm[i / pw[i]] * sgm[pw[i] * p[j]];
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	return;
}

ll fen[N],Ans[N];
void Add(int x,ll v) {
	for(;x < N;x += x & (-x)) fen[x] = (fen[x] + v) % P;
}
ll Sum(int l,int r) {
	ll res = 0; l--;
	for(;r;r -= r & (-r)) res = (res + fen[r]) % P;
	for(;l;l -= l & (-l)) res = (res - fen[l] + P) % P;
	return res;
}

int main() {
	T = read();
	for(int i = 1;i <= T;i++) q[i].n = read(), q[i].m = read(), q[i].a = read();
	for(int i = 1;i <= T;i++) q[i].id = i;
	std::sort(q + 1,q + 1 + T);
	Seive();
	for(int i = 1;i < N;i++) number[i] = i;
	std::sort(number + 1,number + N,cmp);
	int rg = 1;
	for(int i = 1;i <= T;i++) {
		while(sgm[number[rg]] <= q[i].a && rg < N) {
			for(int j = 1;number[rg] * j < N;j++)
				Add(number[rg] * j,(1ll * sgm[number[rg]] * mu[j]) % P);
			rg++;
		}
		ll ans = 0;
		for(int l = 1;l <= q[i].n && l <= q[i].m;l++) {
			int r = std::min(q[i].n / (q[i].n / l),q[i].m / (q[i].m / l));
			ans = (ans + 1ll * Sum(l,r) * (q[i].n / l) % P * (q[i].m / l)) % P;
			l = r;
		}
		// std::printf("%lld\n",ans);
		Ans[q[i].id] = ans;
	}
	for(int i = 1;i <= T;i++) std::printf("%lld\n",Ans[i]);
	return 0;
}

