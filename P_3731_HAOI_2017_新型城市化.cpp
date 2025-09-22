#include <bits/stdc++.h>
#define int long long
#define pir pair<int, int>
using namespace std;
constexpr int MN = 5e5 + 15, INF = 1e9;
struct Edge
{
    int v, w, id;
};
int n, m, S, T, bel[MN];
vector<int> adj[MN];
set<pir> ans;
vector<Edge> G[MN];

namespace Dinic
{
    int cur[MN], dep[MN];

    void add(int u, int v, int w)
    {
        int us = G[u].size(), vs = G[v].size();
        G[u].push_back({v, w, vs});
        G[v].push_back({u, 0, us});
    }

    bool bfs(int S, int T)
    {
        memset(dep, -1, sizeof(dep));
        queue<int> q;
        dep[S] = 0;
        q.push(S);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto e : G[u])
            {
                int v = e.v;
                if (dep[v] == -1 && e.w)
                {
                    dep[v] = dep[u] + 1;
                    q.push(v);
                }
            }
        }
        memset(cur, 0, sizeof(cur));
        return dep[T] != -1;
    }

    int dfs(int u, int lim, int T)
    {
        if (u == T)
            return lim;
        for (int &i = cur[u]; i < G[u].size(); i++)
        {
            int v = G[u][i].v;
            if (dep[v] == dep[u] + 1 && G[u][i].w)
            {
                int p = dfs(v, min(lim, G[u][i].w), T);
                if (p)
                {
                    G[u][i].w -= p;
                    G[v][G[u][i].id].w += p;
                    return p;
                }
                else
                    dep[v] = -1;
            }
        }
        return 0;
    }

    int dinic(int S, int T)
    {
        int ans = 0, flow;
        while (bfs(S, T))
        {
            while (flow = dfs(S, INF, T))
                ans += flow;
        }
        return ans;
    }

}

namespace Tarjan
{
    int dfn[MN], low[MN], vtot, dtot, st[MN], top;
    bool vis[MN];

    void tarjan(int u)
    {
        low[u] = dfn[u] = ++dtot;
        st[++top] = u;
        vis[u] = 1;
        for (auto e : G[u])
        {
            int v = e.v, w = e.w;
            if (!e.w)
                continue;
            if (!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (vis[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (low[u] == dfn[u])
        {
            ++vtot;
            int p;
            do
            {
                p = st[top--];
                vis[p] = 0;
                bel[p] = vtot;
            } while (p != u);
        }
    }

    void solve(int S, int T)
    {
        for (int i = S; i <= T; i++)
        {
            if (!dfn[i])
                tarjan(i);
        }
    }

}

namespace Color
{
    int col[MN];
    bool vis[MN];

    void dfs(int u, int pre)
    {
        if (vis[u])
            return;
        vis[u] = 1;
        col[u] = col[pre] ^ 1;
        for (auto v : adj[u])
        {
            if (v == pre || vis[v])
                continue;
            dfs(v, u);
        }
    }

}
using namespace Color;

signed main()
{
    cin >> n >> m;
    S = 0, T = n + 1;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
            dfs(i, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        if (col[i] == 1)
        {
            Dinic::add(S, i, 1);
            for (auto v : adj[i])
            {
                Dinic::add(i, v, 1);
            }
        }
        else
            Dinic::add(i, T, 1);
    }
    int mxflow = Dinic::dinic(S, T);
    cerr << "QWQ\n";
    Tarjan::solve(S, T);
    for (int i = 1; i <= n; i++)
    {
        if (col[i] == 1)
        {
            for (auto e : G[i])
            {
                int v = e.v, w = e.w;
                if (e.w || v == S || v == T)
                    continue;
                if (bel[i] != bel[v])
                {
                    ans.insert(i < v ? pir(i, v) : pir(v, i));
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto p : ans)
        cout << p.first << ' ' << p.second << '\n';
    return 0;
}