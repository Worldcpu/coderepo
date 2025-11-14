#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int n,f[MN][2];
string st[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>st[i];
    f[1][0]=1;
    for(int i=2;i<=n;i++){
        if(st[i]!=st[i-1]){
            f[i][1]=(f[i-1][0])%MOD;
        }
        f[i][0]=(f[i-1][0]+f[i-1][1])%MOD;
    }
    cout<<(f[n][0]+f[n][1])%MOD<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}