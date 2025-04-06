#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MN = 1e5 + 15, MP = 105;
int n, m, p;
ll f[MP][MN], l, r, x, y, q[MN], suma[MN], sumd[MN], a[MN];

ll getg(int i, int pos)
{
    return (f[i - 1][pos] + suma[pos]);
}

int main()
{
    cin >> n >> m >> p;
    for (int i = 2; i <= n; i++)
    {
        cin >> x;
        sumd[i] = sumd[i - 1] + x;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        a[i] = y - sumd[x];
    }
    sort(a + 1, a + 1 + m);
    for (int i = 1; i <= m; i++)
    {
        suma[i] = suma[i - 1] + a[i];
    }
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;

    for (int i = 1; i <= p; i++)
    {
        l = 1, r = 0;
        q[++r] = 0;
        for (int j = 1; j <= m; j++)
        {
            while (l < r && (getg(i, q[l + 1]) - getg(i, q[l])) <= a[j] * (q[l + 1] - q[l]))
                l++;
            f[i][j] = min(f[i - 1][j], getg(i, q[l]) + a[j] * (j - q[l]) - suma[j]);
            if (getg(i, j) >= 0x3f3f3f3f3f3f3f3fll)
                continue;
            while (l < r && (getg(i, j) - getg(i, q[r])) * (q[r] - q[r - 1]) <= (j - q[r]) * (getg(i, q[r]) - getg(i, q[r - 1])))
                r--;
            q[++r] = j;
        }
    }
    cout << f[p][m];
    return 0;
}