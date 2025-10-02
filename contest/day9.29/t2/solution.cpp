#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>

const int N = 110;
const int mod = 1e8 + 7;
int n, m, a[N][N];
int f[N][N][3], g[N][N][3], h[N][N][3], cnt[N][N][3];
char ch;

inline int add (int x, int y) {
    x += y;
    if (x >= mod) x -= mod;
    return x;
}

inline int sub (int x, int y) {
    x -= y;
    if (x < 0) x += mod;
    return x;
}

void Main() {
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    memset(cnt, 0, sizeof(cnt));
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) {
            std::cin >> ch;
            if (ch >= '0' && ch <= '9') 
                a[i][j] = ch - '0';
            else if (ch == '+') a[i][j] = 10;
            else a[i][j] = 11;
        }
    h[1][1][a[1][1] == 0] = 1; //k
    g[1][1][a[1][1] == 0] = a[1][1]; //ka
    cnt[1][1][a[1][1] == 0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            if (a[i][j] == 10) {
                f[i][j][2] = add(add(f[i - 1][j][0], f[i - 1][j][1]), add(f[i][j - 1][0], f[i][j - 1][1]));
                f[i][j][2] = add(f[i][j][2], add(add(g[i - 1][j][0], g[i - 1][j][1]), add(g[i][j - 1][0], g[i][j - 1][1])));
                cnt[i][j][2] = add(add(cnt[i - 1][j][0], cnt[i - 1][j][1]), add(cnt[i][j - 1][0], cnt[i][j - 1][1]));
                h[i][j][2] = cnt[i][j][2]; //k
            } else if (a[i][j] == 11) {
                f[i][j][2] = add(add(f[i - 1][j][0], f[i - 1][j][1]), add(f[i][j - 1][0], f[i][j - 1][1]));
                h[i][j][2] = add(add(g[i - 1][j][0], g[i - 1][j][1]), add(g[i][j - 1][0], g[i][j - 1][1])); //k += ka
                cnt[i][j][2] = add(add(cnt[i - 1][j][0], cnt[i - 1][j][1]), add(cnt[i][j - 1][0], cnt[i][j - 1][1]));
            } else {
                if (a[i][j] == 0) {
                    f[i][j][0] = add(f[i - 1][j][0], f[i][j - 1][0]);
                    cnt[i][j][0] = add(cnt[i - 1][j][0], cnt[i][j - 1][0]);
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i - 1][j][0] % mod, 1ll * h[i - 1][j][0] * a[i][j] % mod));
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i][j - 1][0] % mod, 1ll * h[i][j - 1][0] * a[i][j] % mod));
                    h[i][j][0] = add(h[i - 1][j][0], h[i][j - 1][0]);

                    f[i][j][1] = add(f[i - 1][j][2], f[i][j - 1][2]);
                    cnt[i][j][1] = add(cnt[i - 1][j][2], cnt[i][j - 1][2]);
                    g[i][j][1] = add(g[i][j][1], add(10ll * g[i - 1][j][2] % mod, 1ll * h[i - 1][j][2] * a[i][j] % mod));
                    g[i][j][1] = add(g[i][j][1], add(10ll * g[i][j - 1][2] % mod, 1ll * h[i][j - 1][2] * a[i][j] % mod));
                    h[i][j][1] = add(h[i - 1][j][2], h[i][j - 1][2]);
                } else {
                    f[i][j][0] = add(add(f[i - 1][j][0], f[i - 1][j][2]), add(f[i][j - 1][0], f[i][j - 1][2]));
                    cnt[i][j][0] = add(add(cnt[i - 1][j][0], cnt[i - 1][j][2]), add(cnt[i][j - 1][0], cnt[i][j - 1][2]));
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i - 1][j][0] % mod, 1ll * h[i - 1][j][0] * a[i][j] % mod));
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i - 1][j][2] % mod, 1ll * h[i - 1][j][2] * a[i][j] % mod));
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i][j - 1][0] % mod, 1ll * h[i][j - 1][0] * a[i][j] % mod));
                    g[i][j][0] = add(g[i][j][0], add(10ll * g[i][j - 1][2] % mod, 1ll * h[i][j - 1][2] * a[i][j] % mod));
                    h[i][j][0] = add(add(h[i - 1][j][0], h[i - 1][j][2]), add(h[i][j - 1][0], h[i][j - 1][2]));
                }
            }
        }
    std::cout << add(add(g[n][m][0], g[n][m][1]), add(f[n][m][0], f[n][m][1])) << '\n';
}

int main() {
    // freopen("D://fre/in", "r", stdin);
    // freopen("D://fre/out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    int type, T = 1;
    std::cin >> type >> T;
    while (T--) Main();
    std::cerr << std::clock() << " ms";
    return 0;
}