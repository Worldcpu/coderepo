#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 520; // 原来 MN = 520

int n;
string s;

struct SubAuto {
    // 存储每个字母出现的位置（1-based）
    vector<int> pos[26];

    void init(const string &st) {
        for (int c = 0; c < 26; ++c) pos[c].clear();
        for (int i = 1; i <= n; ++i) {
            pos[st[i] - 'a'].push_back(i);
        }
    }

    // 返回在位置 cur 之后（> cur）的、字符 ch 的下一个位置；找不到返回 0
    int next_pos(int cur, int ch) const {
        const auto &vec = pos[ch];
        auto it = lower_bound(vec.begin(), vec.end(), cur + 1);
        if (it == vec.end()) return 0;
        return *it;
    }
} autom;

vector<vector<long long>> dp; // -1 表示未计算

long long dfs(int x, int y, int now) {
    // x: 当前在第一个串的位置（0..n）
    // y: 当前在第二个串的位置（0..n）
    // now: 终点（当 x == now 时计为 1）
    if (x > now) return 0;
    if (x == now) return 1;
    if (dp[x][y] != -1) return dp[x][y];
    long long res = 0;
    for (int c = 0; c < 26; ++c) {
        int nx1 = autom.next_pos(x, c);
        int nx2 = autom.next_pos(y, c);
        if (nx1 && nx2) {
            res += dfs(nx1, nx2, now);
        }
    }
    dp[x][y] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> s)) return 0;
    n = (int)s.length();
    s = " " + s; // 1-based
    autom.init(s);

    long long ans = 0;
    // 与原程序行为一致：对每个 i（作为 now），清空记忆并计算 dfs(0,i,i)
    for (int i = 1; i <= n; ++i) {
        dp.assign(n + 1, vector<long long>(n + 1, -1));
        ans += dfs(0, i, i);
    }

    cout << ans << '\n';
    return 0;
}
