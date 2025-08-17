#include <bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;

constexpr int INF = 1e18;
int n;
vector<int> sum;
vector<vector<vector<pir>>> f;

int get(int i, int j, int k) {
    if (f[i][j].empty() || f[i][j][0].first > k) return INF;
    int l = 0, r = (int)f[i][j].size() - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (f[i][j][mid].first <= k) l = mid;
        else r = mid - 1;
    }
    return f[i][j][l].second;
}

void solve() {
    cin >> n;
    sum.assign(n + 1, 0);
    f.assign(n + 1, vector<vector<pir>>(n + 1));

    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    vector<int> g(n + 1);

    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (len == 1) {
                f[l][r].emplace_back(0, 0);
            } else {
                int s = sum[r] - sum[l - 1];
                int lg = (int)ceil(log2(1.0 * s));
                for (int k = l; k < r; k++) {
                    int len1 = sum[k] - sum[l - 1], len2 = sum[r] - sum[k];
                    int K = abs(len1 - len2);
                    g[k] = get(l, k, K) + get(k + 1, r, K) + min(len1, len2) * lg;
                    g[k] = min(g[k], INF);
                    f[l][r].emplace_back(K, g[k]);
                }
                sort(f[l][r].begin(), f[l][r].end());
                for (int k = 1; k < f[l][r].size(); k++) {
                    f[l][r][k].second = min(f[l][r][k].second, f[l][r][k - 1].second);
                }
                if (l == 1 && r == n) {
                    for (int k = 1; k < n; k++) {
                        cout << (g[k] >= INF ? -1 : g[k]) << " \n"[k == n - 1];
                    }
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
