#include <bits/stdc++.h>
#define x first
#define y second

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 2e5 + 10, M = 4e5 + 10, mod = 998244353;

int n, k;
int h[N], ne[M], e[M], idx;
int f[N], deg[N], bu[N];
int root;
bool c[N];

void add(int a, int b)
{
    ne[++ idx] = h[a], e[idx] = b, h[a] = idx;
}

void dfs(int u, int fa)
{
    bool is_leaf = true;
    int cnt = 0; f[u] = 0;
    for (int i = h[u]; i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        is_leaf = false;
        dfs(j, u);
        f[u] += f[j];
        if (c[j]) cnt ++ ;
    }
    if (is_leaf)
    {
        c[u] = true;
        return;
    }
    f[u] += cnt / k;
    if (cnt == deg[u] - 1 && cnt % k == 0)
        c[u] = true;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- )
    {
        for (int i = 1; i <= n; i ++ )
            c[i] = 0, deg[i] = bu[i] = h[i] = 0;
        root = idx = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i < n; i ++ )
        {
            int a, b;
            scanf("%d%d", &a, &b);
            add(a, b), add(b, a);
            deg[a] ++ , deg[b] ++ ;
        }
        if (k == 1)
        {
            printf("%d\n", n - 1);
            continue;
        }
        for (int i = 1; i <= n; i ++ )
            bu[deg[i]] = i;
        for (int i = k; i > 1; i -- )
            for (int j = i; j <= n; j += k)
                if (bu[j])
                {
                    root = bu[j];
                    break;
                }
        if (!root) 
        {
            for (int i = k + 1; i <= n; i += k)
                if (bu[i])
                {
                    root = bu[i];
                    break;
                }
            if (!root) root = 1;
        }
        
        dfs(root, -1);
        printf("%d\n", f[root]);
    }

    return 0;
}
