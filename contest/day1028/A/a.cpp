#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 998244353;

int64 modpow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}
int64 modinv(int64 x) { return modpow(x, MOD - 2); }

map<int64, int> factorize(int64 x) {
    map<int64, int> res;
    for (int64 d = 2; d * d <= x; d += (d == 2 ? 1 : 2)) {
        while (x % d == 0) {
            res[d]++;
            x /= d;
        }
    }
    if (x > 1) res[x]++;
    return res;
}

int64 tau_of(int64 x) {
    if (x == 1) return 1;
    int64 res = 1;
    for (int64 d = 2; d * d <= x; d += (d == 2 ? 1 : 2)) {
        if (x % d == 0) {
            int cnt = 0;
            while (x % d == 0) {
                x /= d;
                cnt++;
            }
            res *= (cnt + 1);
        }
    }
    if (x > 1) res *= 2;
    return res;
}

struct Node {
    long double marginal;
    int i;
    int t;
    bool operator<(const Node& o) const {
        return marginal > o.marginal; 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int64 k;
    cin >> n >> k;
    vector<int64> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 分解 k
    auto kfac = factorize(k);

    // alpha[p][i]
    unordered_map<int64, vector<int>> alpha;
    vector<int64> reduced = a;
    for (auto [p, e] : kfac) {
        alpha[p] = vector<int>(n);
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            while (reduced[i] % p == 0) {
                reduced[i] /= p;
                cnt++;
            }
            alpha[p][i] = cnt;
        }
    }

    // 初始 ans = ∏ τ(a_i)
    int64 ans = 1;
    for (int i = 0; i < n; i++) {
        int64 t = 1;
        for (auto [p, e] : kfac) {
            t *= (alpha[p][i] + 1);
        }
        t *= tau_of(reduced[i]);
        t %= MOD;
        ans = ans * t % MOD;
    }

    // 对每个质数单独分配
    for (auto [p, e] : kfac) {
        vector<int> c(n);
        for (int i = 0; i < n; i++) c[i] = alpha[p][i] + 1;

        priority_queue<Node> pq;
        for (int i = 0; i < n; i++) {
            long double m = (long double)(c[i] + 1) / (long double)c[i];
            pq.push({-m, i, 0});
        }

        for (int step = 0; step < e; step++) {
            Node cur = pq.top();
            pq.pop();
            int i = cur.i;
            int t = cur.t;

            int64 num = (c[i] + t + 1) % MOD;
            int64 den = (c[i] + t) % MOD;
            ans = ans * num % MOD * modinv(den) % MOD;

            t++;
            long double m = (long double)(c[i] + t + 1) / (long double)(c[i] + t);
            pq.push({-m, i, t});
        }
    }

    cout << ans % MOD << "\n";
    return 0;
}