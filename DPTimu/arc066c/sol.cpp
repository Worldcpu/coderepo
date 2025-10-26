#include <bits/stdc++.h>
#define inf 100000000000000ll
using namespace std;

int read();

int n;
long long f[100005][3];
void chmax(long long &x, long long y) { x = x > y ? x : y; }

int main() {
    n = read();
    f[0][0] = 0, f[0][1] = f[0][2] = -inf;
    for (int i = 1, x; i <= n; ++i) {
        x = read();
        {
            f[i][0] = max(f[i - 1][0], f[i - 1][1]),
            f[i][1] = max(f[i - 1][1], f[i - 1][2]);
            f[i][2] = f[i - 1][2];
        }
        f[i][0] += x, f[i][1] -= x, f[i][2] += x;
        if (x < 0) chmax(f[i][2], f[i][1]), chmax(f[i][1], f[i][0]);
    }
    printf("%lld\n", max(f[n][0], max(f[n][1], f[n][2])));
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}
