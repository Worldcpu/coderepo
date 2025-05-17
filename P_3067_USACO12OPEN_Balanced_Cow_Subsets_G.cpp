#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=25,MV=2e6+15;
int n,tot,a[MN],ans[1 << 20]; 
vector<int> vct[MV];
unordered_map<int,int> mv;

void dfs1(int x, int sum, int now) {
    if(x == n/2) {
        if(!mv[sum]) mv[sum] = ++tot;
        vct[mv[sum]].push_back(now);
        return;
    }
    dfs1(x+1, sum, now);
    dfs1(x+1, sum + a[x], now | (1 << x));
    dfs1(x+1, sum - a[x], now | (1 << x));
}

void dfs2(int x, int sum, int now) {
    if(x == n) {
        if(mv.count(sum)) {
            int qwq = mv[sum];
            for(int awa : vct[qwq]) ans[awa | now] = 1;
        }
        return;
    }
    dfs2(x+1, sum, now);
    dfs2(x+1, sum + a[x], now | (1 << x)); // 修正位移为x
    dfs2(x+1, sum - a[x], now | (1 << x));
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    dfs1(0, 0, 0);
    dfs2(n/2, 0, 0);
    int awa = 0;
    for(int i = 1; i < (1 << n); i++) awa += ans[i];
    cout << awa;
    return 0;
}