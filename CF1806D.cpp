#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,a[MN],f[MN],ans[MN],pw[MN];

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
}

void init(){
    for(int i=0;i<=n;i++){
        f[i]=ans[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<n;i++) cin>>a[i];
    f[0]=1;
    for(int i=1;i<n;i++){
        f[i]=f[i-1]*(i-a[i])%MOD;
    }
    for(int i=1;i<n;i++){
        ans[i]=(ans[i-1]*i%MOD+f[i-1]*(!a[i]))%MOD;
        cout<<ans[i]<<' ';
    }
    cout<<'\n';
}


signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}