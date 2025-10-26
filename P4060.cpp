#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;

constexpr int MN = 5e5 + 15;
int n, m, f[MN][2], num[MN], tot, ans;
pir a[MN];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) { 
        cin >> a[i].first >> a[i].second;
    }
    sort(a + 1, a + 1 + m);

    for (int p = 0; p < 31; p++) {
        tot = 0;
        memset(f, 0x3f, sizeof(f));

        if (a[1].first > 1) num[++tot] = 2;
        if (a[1].second & (1 << p)) num[++tot] = 1;
        else num[++tot] = 0;

        for (int i = 2; i <= m; i++) {
            if (a[i].first - a[i - 1].first >= 3) {
                num[++tot] = 2;
                num[++tot] = 2;
            } else if (a[i].first - a[i - 1].first == 2) {
                num[++tot] = 2;
            }
            if (a[i].second & (1 << p)) num[++tot] = 1;
            else num[++tot] = 0;
        }

        if (a[m].first < n) num[++tot] = 2;

        if (num[1] == 0) f[1][0] = 0;
        else if (num[1] == 1) f[1][1] = 1;
        else if (num[1] == 2) f[1][0] = 0, f[1][1] = 1;

        for (int i = 2; i <= tot; i++) {
            if (num[i] == 0) {
                f[i][0] = f[i - 1][0];
                f[i][1] = f[i - 1][1] + 1;
            } else if (num[i] == 1) {
                f[i][0] = f[i - 1][1];
                f[i][1] = f[i - 1][0] + 1;
            } else { 
                f[i][0] = min(f[i - 1][0], f[i - 1][1]);
                f[i][1] = min(f[i - 1][0], f[i - 1][1]) + 1;
            }
        }

        ans += min(f[tot][0], f[tot][1]) * (1LL << p);
    }

    cout << ans;
    return 0;
}
