#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 1500, MOD = 1e9 + 7;
int n, m, a, b, K;

struct node
{
    int x;
    node(int X = 0) : x(X) {}
    void operator=(int b) { x = b; }
    node operator+(node b) { return node((x + b.x) % MOD); }
    node operator-(node b) { return node((x - b.x + MOD) % MOD); }
    node operator*(node b) { return node(x * b.x % MOD); }
    node operator^(int b)
    {
        int r = 1, a = x;
        while (b)
        {
            if (b & 1)
                r = r * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return node(r);
    }
    node operator/(node b) { return (*this) * (b ^ (MOD - 2)); }
} P, p[MN], q[MN], f[MN][MN], s[MN][MN], g[MN][MN];

node C(int n, int m)
{
    node a = 1, b = 1;
    for (int i = 1; i <= m; i++)
        a = a * (n - i + 1), b = b * i;
    return a / b;
}

signed main()
{
    cin >> n >> m >> a >> b >> K;
    P = (node)a / b;
    for (int i = 0; i <= min(m, K); i++)
    {
        p[i] = C(K, i) * (P ^ i) * ((node(1) - P) ^ (K - i));
    }
    for (int i = 1; i <= m; i++)
    {
        q[i] = q[i - 1] + p[i - 1];
    }
    f[0][m] = s[0][m] = node(1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = p[m - j] * (q[j] * (s[i - 1][m] - s[i - 1][m - j]) - g[i - 1][j]);
            s[i][j] = s[i][j - 1] + f[i][j];
            g[i][j] = g[i][j - 1] + p[j - 1] * s[i][j - 1];
        }
    }
    cout << s[n][m].x;

    return 0;
}