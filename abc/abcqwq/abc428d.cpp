#include <bits/stdc++.h>
#define int long long
using namespace std;

int c, d, ans;

long long isqrt(long long n) {
    long long r = sqrtl((long double)n);
    while ((r+1)*(r+1) <= n) ++r;
    while (r*r > n) --r;
    return r;
}

long long ipow10(int k) {
    long long r = 1;
    while (k--) r *= 10;
    return r;
}

void solve() {
    cin >> c >> d;
    ans = 0;
    long long L = c + 1, R = c + d;
    int Llen = to_string(L).size();
    int Rlen = to_string(R).size();
    for (int i = Llen; i <= Rlen; i++) {
        long long a = max(ipow10(i - 1), c + 1LL);
        long long b = min(ipow10(i) - 1, c + d);
        if (a > b) continue;
        long long qwq = c * ipow10(i);
        long long low = qwq + a, high = qwq + b;
        long long la = isqrt(low);
        if (la * la < low) la++;
        long long lb = isqrt(high);
        if (lb >= la) ans += lb - la + 1;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
}
