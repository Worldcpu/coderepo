#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353;
int n,K,c,f[MN];

signed main(){
    cin>>n>>K>>c;
    f[1]=c;
    for(int i=2;i<=n;i++){
        f[i]=(f[i-1]*2%MOD+f[max(1ll,i-(K-1))]*(c-2)%MOD)%MOD;
    }
    cout<<f[n];
    return 0;
}