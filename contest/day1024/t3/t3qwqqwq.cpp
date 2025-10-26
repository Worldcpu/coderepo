#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 10, mod = 1e9 + 7;
int n, m, k;
int n1;

struct edg
{
    int a, b, c;
    bool operator<(const edg a)
    {
        return c < a.c;
    }
} ed[N];

int p[N];
int find(int x)
{
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

vector<int> G1[N];
vector<pair<int, int>> G[N];
int val[N], sz[N], siz[N];
ll ans = 0;

void dfs1(int u)
{
    siz[u] = 0;
    // cout << u << ": " << val[u] << ";";
    if (u <= n)
        siz[u] = 1;
    else
    {
        for (auto v : G1[u])
        {
            dfs1(v);
            ans = (ans + 1ll * siz[v] * siz[u] % mod * (val[u] - 1) % mod) % mod;
            siz[u] += siz[v];
        }
    }
}

int fa[22][N / 2], mx[22][N / 2];
int dep[N];
void dfs2(int u, int f)
{
    fa[0][u] = f;
    dep[u] = dep[f] + 1;
    for (auto [v, w] : G[u])
    {
        if (v == f)
            continue;
        mx[0][v] = w;
        dfs2(v, u);
    }
}

int query(int u, int v)
{
    int res = 0;
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[i][u]] >= dep[v])
        {
            res = max(res, mx[i][u]);
            u = fa[i][u];
        }
    if (u == v)
        return res;
    for (int i = 20; i >= 0; i--)
        if (fa[i][u] != fa[i][v])
        {
            res = max(res, mx[i][u]);
            res = max(res, mx[i][v]);
            u = fa[i][u], v = fa[i][v];
        }
    res = max(res, mx[0][u]);
    res = max(res, mx[0][v]);
    return res;
}

void solve1()
{
    dfs1(n1);
    dfs2(1, 0);
    // cout << ans << endl;

    for (int i = 1; i <= 20; i++)
        for (int u = 1; u <= n; u++)
        {
            fa[i][u] = fa[i - 1][fa[i - 1][u]];
            mx[i][u] = max(mx[i - 1][u], mx[i - 1][fa[i - 1][u]]);
        }

    // cout << mx[1][3] << endl;

    for (int i = 1; i <= m; i++)
    {
        int x = query(ed[i].a, ed[i].b);
        // cout << ed[i].a << ' ' << ed[i].b << ' ' << x << endl;
        ans = (ans - x + 1 + mod) % mod;
    }

    cout << ans << '\n';
}

void solve()
{
    cin >> n >> m >> k;
    n1 = n;
    ans = 0;
    for (int i = 1; i <= n * 2; i++)
    {
        p[i] = i;
        G[i].clear();
        G1[i].clear();
    }
    for (int i = 1; i <= n; i++)
        sz[i] = 1;
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        ed[i] = {a, b, c};
    }
    sort(ed + 1, ed + m + 1);
    int cnt = n;
    for (int i = 1; i <= m; i++)
    {
        int a = ed[i].a, b = ed[i].b;
        if (find(a) == find(b))
            continue;
        cnt--;
        n1++;
        G1[n1].push_back(find(a));
        G1[n1].push_back(find(b));
        val[n1] = ed[i].c;
        sz[n1] = sz[find(a)] + sz[find(b)];
        p[find(a)] = n1;
        p[find(b)] = n1;
        G[a].push_back({b, ed[i].c});
        G[b].push_back({a, ed[i].c});
    }

    if (cnt >= 3)
        cout << 0 << '\n';
    if (cnt == 2)
    {
        ans = 1;
        for (int i = 1; i <= n1; i++)
            if (find(i) == i)
                ans = ans * sz[i] % mod;
        ans = ans * k % mod;
        cout << ans << '\n';
    }
    if (cnt == 1)
        solve1();
}

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
