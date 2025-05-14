#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 4e6 + 15;

struct Query {
    int x, y, lca, t, id;
} qry[MN];

struct Change {
    int pos, val;
} chg[MN];

int n, m, q, ret, len, tot, qtot, ctot, l, r, now, ans[MN], st[MN], ed[MN], pos[MN], c[MN], top[MN], hson[MN], siz[MN], dep[MN], fa[MN], cnt[MN], v[MN], w[MN];
bool vis[MN];
vector<int> adj[MN];

bool cmp(Query x, Query y) {
    if (x.x / len != y.x / len) return x.x < y.x;
    if (x.y / len != y.y / len) return x.y < y.y;
    return x.t < y.t;
}

void dfs1(int u, int pre) {
    fa[u] = pre;
    dep[u] = dep[pre] + 1;
    siz[u] = 1;
    st[u] = ++tot, pos[tot] = u;
    int maxp = -1;
    for (auto v : adj[u]) {
        if (v == pre) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (maxp < siz[v]) {
            maxp = siz[v];
            hson[u] = v;
        }
    }
    ed[u] = ++tot, pos[tot] = u;
}

void dfs2(int u, int ltop) {
    top[u] = ltop;
    if (!hson[u]) return;
    dfs2(hson[u], ltop);
    for (auto v : adj[u]) {
        if (v == fa[u] || v == hson[u]) continue;
        dfs2(v, v);
    }
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

void add(int c) {
    cnt[c]++;
    ret += v[c] * w[cnt[c]];
}

void del(int c) {
    ret -= v[c] * w[cnt[c]];
    cnt[c]--;
}

void Add(int p) {
    if (vis[p]) del(c[p]);
    else add(c[p]);
    vis[p] ^= 1;
}

void update(int p) {
    int pos = chg[p].pos;
    if (vis[pos]) {
        Add(pos); // 先移除旧颜色
        swap(c[pos], chg[p].val);
        Add(pos);
    } else {
        swap(c[pos], chg[p].val);
    }
}

signed main() {
    cin >> n >> m >> q;
    len = cbrt(2 * n) * cbrt(2 * n); // 分块大小
    for (int i = 1; i <= m; i++) cin >> v[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= q; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 0) {
            ctot++;
            chg[ctot].pos = x;
            chg[ctot].val = y;
        } else {
            qtot++;
            qry[qtot].t = ctot;
            qry[qtot].id = qtot;
            if (st[x] > st[y]) swap(x, y);
            int qlca = lca(x, y);
            if (qlca == x) {
                qry[qtot].x = st[x];
                qry[qtot].y = st[y];
            } else {
                qry[qtot].x = ed[x];
                qry[qtot].y = st[y];
                qry[qtot].lca = qlca;
            }
        }
    }
    sort(qry + 1, qry + 1 + qtot, cmp);

    l = 1, r = 0, now = 0;

    for (int i = 1; i <= qtot; i++) {
        while (now < qry[i].t) update(++now);
        while (now > qry[i].t) update(now--);
        while (l < qry[i].x) Add(pos[l++]);
        while (l > qry[i].x) l--, Add(pos[l]);
        while (r < qry[i].y) r++, Add(pos[r]);
        while (r > qry[i].y) Add(pos[r--]);
        if (qry[i].lca) {
            Add(qry[i].lca);
            ans[qry[i].id] = ret;
            Add(qry[i].lca);
        } else {
            ans[qry[i].id] = ret;
        }
    }

    for (int i = 1; i <= qtot; i++) cout << ans[i] << '\n';
    return 0;
}