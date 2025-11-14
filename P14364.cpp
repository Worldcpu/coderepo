#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=998244353;

int n = 10, m;
string s;
vector<int> c;

signed main() {
    cin >> n >> m >> s;
    if(n>10){
        cout<<0;
        return 0;
    }
    s = " " + s; // 1-based
    c.resize(n);
    for(int i = 0; i < n; i++) cin >> c[i];
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    int ans = 0;
    do {
        int rejected = 0, accepted = 0;
        for(int day = 1; day <= n; day++) {
            int idx = perm[day-1];
            if(rejected >= c[idx]){
                rejected++;
                continue;
            }
            if(s[day] == '1') accepted++;
            else rejected++;
        }
        if(accepted >= m) ans++;
    } while(next_permutation(perm.begin(), perm.end()));

    cout << ans << "\n";
    return 0;
}
