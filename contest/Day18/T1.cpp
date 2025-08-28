#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n; cin >> n;
    int ans = 0;
    for (int g = 1; g <= n; g++) {
        int m = n / g;
        ans += m / 2; 
    }
    cout << ans << "\n";
}
