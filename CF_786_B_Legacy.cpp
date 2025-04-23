#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#define mid ((l+r)>>1)
#define ll long long
#define pii pair<ll,ll>
using namespace std;
const ll N = 1e6 + 5;
struct Edge {
	ll nxt, val, to;
} edge[N];
ll n, st, head[N], k, cut, Out[N];
ll dis[N], opt, ji[N], val, In[N];
bool vis[N];
void add(ll x, ll y, ll z) {
	edge[++cut] = {head[x], z, y};
	head[x] = cut;
	return ;
}
inline ll read() {
	char ch = getchar();
	ll x = 0ll;
	while (ch < '0' || '9' < ch)
		ch = getchar();
	while ('0' <= ch && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x;
}
void build(ll x, ll l, ll r) {
	if (l == r) {
		In[l] = x + k;
		Out[l] = x;
		add(Out[l],In[l], 0);// 出往入不是入往出
		return ;
	}
	ll lc = x << 1, rc = lc | 1;
	add(x, lc, 0), add(x, rc, 0);
	add(lc + k, x + k, 0), add(rc + k, x + k, 0);
	build(lc, l, mid);
	build(rc, mid + 1, r);
	return ;
}
void modify(ll x, ll l, ll r, ll cl, ll cr, ll u) {
//	cout<<l<<' '<<r<<'\n';
	if (r < cl)return ;
	if (l > cr)return ;
	if (cl <= l && r <= cr) {
		if (opt == 2)add(In[u], x, val); //v->[l,r]
		else add(x + k, Out[u], val);
		return ;
	}
	ll lc = x << 1, rc = lc | 1;
	modify(lc, l, mid, cl, cr, u);
	modify(rc, mid + 1, r, cl, cr, u);
	return ;
}
void dij() {
	memset(dis, 0x3f, sizeof dis);
	dis[st] = 0;
	priority_queue<pii, vector<pii>, greater<pii> >q;
	q.push({0, st});
	while (!q.empty()) {
		int h = q.top().second;
		q.pop();
        if(vis[h]) continue;// 你的dij写错了没判断
        vis[h]=1;
		for (int i = head[h]; i; i = edge[i].nxt) {
			int to = edge[i].to;
			if (dis[to] > dis[h] + edge[i].val) {
				dis[to] = dis[h] + edge[i].val;
				q.push({dis[to], to});
			}
		}
	}
	return ;
}
void out() {
	for (int i = 1; i <= n; i++)
        if(dis[In[i]]>=1e18) printf("-1 "); // 你没判无解
		else printf("%lld ", dis[In[i]]);
	return ;
}
signed main() {
	n = read(), k = n << 2;
	ll q = read();
	st = read();
	build(1, 1, n);
    st=In[st]; // 原来的点对应的线段树节点并不是st本身，这个和线段树结构特点有关。
	while (q--) {
		opt = read();
		ll x = read(), y = read(), z = read();
		if (opt == 1) {
			add(In[x], Out[y], z);
			continue;
		}
		ll a = read();
		val = a;
		modify(1, 1, n, y, z, x); // 参数带错了
	}
	dij();
	out();
	return 0;
}