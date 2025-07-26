#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
const char endl = '\n';

const int N = 45,
          D = 1e5 + 5;
const int mod = 1e9 + 7;

int n, d, r[N], f[N][N][N * N], max, ans;
int fac[D], inv[D];

int binpow(int a, int b) {
    int res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}

inline int C(int n, int m) {
    return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {

       freopen("shooter.in","r",stdin);
    freopen("shooter.out","w",stdout);
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 阶乘
    fac[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        fac[i] = 1ll * fac[i - 1] * i % mod;
    }

    // 逆元
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= 100000; i++) {
        inv[i] = static_cast<long long>(mod - (mod / i)) * inv[mod % i] % mod;
    }

    // 阶乘的逆元
    for (int i = 2; i <= 100000; i++) {
        inv[i] = static_cast<long long>(inv[i - 1]) * inv[i] % mod;
    }

    cin >> n >> d;

    for (int i = 1; i <= n; i++) {
        cin >> r[i];

        max = std::max(max, r[i]);
    }

    std::sort(r + 1, r + 1 + n);

    f[0][0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= max * (i - j + 2); k++) {
                int t = r[i + 1];

                if (j >= 1) {
                    f[i + 1][j][k + t] = (f[i + 1][j][k + t] + 1ll * f[i][j][k] * 2 * j) % mod;
                }

                if (j >= 2 && k) {
                    f[i + 1][j - 1][k + t * 2 - 1] = (f[i + 1][j - 1][k + t * 2 - 1] + 1ll * f[i][j][k] * j * (j - 1)) % mod;
                }

                f[i + 1][j + 1][k + 1] = (f[i + 1][j + 1][k + 1] + f[i][j][k]) % mod;
            }
        }
    }

    for (int i = 0; i <= n * max; i++) {
        ans = (ans + 1ll * C(d - i + n, n) * f[n][1][i] % mod) % mod;
    }

    cout << ans << endl;

    return 0;
}