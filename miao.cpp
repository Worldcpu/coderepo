#include <bits/stdc++.h>
using namespace std;
const int MN = 2e5;
struct Node
{
    int nxt, to, w;
} node[MN];
int head[MN], tottt, T, in[MN], out[MN], n, m, id, tp[MN];
inline void insert(int u, int v)
{
    node[++tottt].to = v;
    node[tottt].nxt = head[u];
    head[u] = tottt;
    in[v]++;
}
vector<pair<int, int>> vec;
void start()
{
    vec.clear();
    tottt = id = 0;
    memset(tp, 0, sizeof(tp));
    memset(head, 0, sizeof(head));
    memset(in, 0, sizeof(in));
}
bool Sort()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        tp[u] = ++id;
        for (int i = head[u]; i; i = node[i].nxt)
        {
            int v = node[i].to;
            in[v]--;
            if (!in[v])
                q.push(v);
        }
    }
    if (id < n)
        return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--)
    {
        cin >> n >> m;
        start();
        for (int i = 1, u, v, ty; i <= m; ++i)
        {
            cin >> ty >> u >> v;
            if (ty == 1)
                insert(u, v);
            else
                vec.push_back(make_pair(u, v));
        }
        if (!Sort())
        {
            cout << "NO\n";
            continue;
        }
        else
        {
            cout << "YES\n";
            for (int i = 1; i <= n; ++i)
                for (int j = head[i]; j; j = node[j].nxt)
                {
                    int v = node[j].to;
                    cout << i << " " << v << '\n';
                }
            for (int i = 0; i < vec.size(); ++i)
            {
                int u = vec[i].first, v = vec[i].second;
                if (tp[u] < tp[v])
                    cout << u << " " << v << '\n';
                else
                    cout << v << " " << u << '\n';
            }
        }
    }
    return 0;
}