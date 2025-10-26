#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN = 120, INF = 1e18;
int n, m, s, t, a[MN], K[MN], b[MN], c[MN], f[MN][MN][MN], sumk[MN];

bool check(int d)
{
    memset(f, -0x3f, sizeof(f));
    f[0][0][0] = 0;
    for (int i = 1; i <= t; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= t; k++)
            {
                if (k > 0 && ~f[i - 1][j][k - 1])
                {
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + sumk[j]);
                }
                if (j>0&&i-((a[j]-1)/sumk[j-1]+1)>=0&&k-((a[j]-1)/sumk[j-1]+1)>=0&&(~f[i-((a[j]-1)/sumk[j-1]+1)][j-1][k-((a[j]-1)/sumk[j-1]+1)]))
                {
                    f[i][j][k] = max(f[i - ((a[j] - 1) / sumk[j - 1] + 1)][j - 1][k - ((a[j] - 1) / sumk[j - 1] + 1)], f[i][j][k]);
                }
                if (d != 0 && j > 0 && i - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1) >= 0 && k + ((b[j] - 1) / d + 1) - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1) >= 0 && k + ((b[j] - 1) / d + 1) - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1) <= i && (~f[i - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1)][j - 1][k + ((b[j] - 1) / d + 1) - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1)]))
                {
                    f[i][j][k] = max(f[i][j][k], f[i - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1)][j - 1][k + ((b[j] - 1) / d + 1) - ((a[j] - 1 - c[j]) / sumk[j - 1] + 1)]);
                    if (a[j] == c[j])
                        f[i][j][k] += sumk[j - 1];
                }
                if (f[i][j][k] >= s)
                    return 1;
            }
        }
    }
    return 0;
}

signed main()
{
    cin >> m >> s >> t >> n;
    sumk[0] = m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> K[i] >> b[i] >> c[i];
        sumk[i] = sumk[i - 1] + K[i];
    }
    int l = 0, r = 1e9, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    cout << ans;
    return 0;
}