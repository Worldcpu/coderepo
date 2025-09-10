#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 100005;

int n, m, ans[N]; LL al;
struct opt { int typ; LL x, y; } op[N];
char buf[15];
vector<pair<int, int> > e[N];

struct DSU {
	int fa[N << 6];
	void init(int n_) { iota(fa + 1, fa + n_ + 1, 1); }
	int find(int x) { if (x != fa[x]) fa[x] = find(fa[x]); return fa[x]; }
	void merge(int x, int y) { int xx = find(x), yy = find(y); if (xx != yy) fa[xx] = yy; }
} ds;

struct sgt {
	int tot = 1, tg[N << 6], ls[N << 6], rs[N << 6];
	bool leaf(int id) { return (!ls[id] && !rs[id]); }
	void pushdown(int id) {
		if (!ls[id]) ls[id] = ++tot;
		if (!rs[id]) rs[id] = ++tot;
		if (tg[id]) tg[ls[id]] = tg[rs[id]] = tg[id], tg[id] = 0;
	}
	void change(LL l, LL r, int id, LL x, LL y, int v) {
		if (l >= x && r <= y) { tg[id] = v; return; }
		LL mid = (l + r) >> 1; pushdown(id);
		if (x <= mid) change(l, mid, ls[id], x, y, v);
		if (y > mid) change(mid + 1, r, rs[id], x, y, v);
	}
	void link(int u, int v) {
		if (leaf(u) && leaf(v)) e[min(tg[u], tg[v])].push_back({u, v});
		else if (leaf(u)) link(u, ls[v]), link(u, rs[v]);
		else if (leaf(v)) link(ls[u], v), link(rs[u], v);
		else link(ls[u], ls[v]), link(rs[u], rs[v]);
	}
	int query(LL l, LL r, int id, LL x) {
		if (leaf(id)) return id;
		LL mid = (l + r) >> 1;
		if (x <= mid) return query(l, mid, ls[id], x);
		else return query(mid + 1, r, rs[id], x);
	}
	void process() {
		for (int i = 1; i <= tot; i++) if (!leaf(i)) link(ls[i], rs[i]);
		ds.init(tot);
	}
} t;

int main() {
	scanf("%d %d", &n, &m); al = (1ll << n) - 1, t.tg[1] = m + 1;
	for (int i = 1; i <= m; i++) {
		scanf("%s %lld %lld", buf + 1, &op[i].x, &op[i].y);
		op[i].typ = (buf[1] == 'b');
	}
	for (int i = 1; i <= m; i++) if (op[i].typ) t.change(0, al, 1, op[i].x, op[i].y, i);
	t.process();
	for (auto p : e[m + 1]) ds.merge(p.first, p.second);
	for (int i = m; i; i--) {
		for (auto p : e[i]) ds.merge(p.first, p.second);
		if (!op[i].typ) ans[i] = (ds.find(t.query(0, al, 1, op[i].x)) == ds.find(t.query(0, al, 1, op[i].y)));
	}
	for (int i = 1; i <= m; i++) if (!op[i].typ) printf("%d\n", ans[i]);
	return 0;
}
