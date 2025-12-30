#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e7;
int n, m;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
long long f[N];
long long p[N], tot;
map<ll, int> mp;
void get()
{
    f[0] = f[1] = 1;
    //vis[0] = vis[1] = true;
    p[++tot] = 1;
    for (int i = 2; i < N / 100; ++i)
    {
        f[i] = f[i - 1] + f[i - 2];
        if (f[i] > 1ll << 40)
            break;
        //   mp[f[i]] = 1;
        p[++tot] = f[i];
        //   cout << f[i] << endl;
    }
}
int g[N], a[N], pre[N];
int main()
{
    //freopen("f.in", "r", stdin);
    // freopen("f.out", "w", stdout);
    n = read();
    get();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    memset(g, 0x3f, sizeof(g));
    g[0] = 0;
    int tmp = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= tot; ++j)
        {
            if (mp.find(p[j] - a[i]) != mp.end())
            {
                tmp++;
                mp.clear();
                break;
            }
        }
        mp[a[i]]++;
    }
    cout << tmp << endl;
    return 0;
}
