#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,h[MN],f[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    f[1]=h[1];
    for(int i=2;i<=n;i++){
        f[i]=min(f[i-1]+h[i]-1,f[i-2]+h[i-1]+max(0ll,h[i]-i+1));
    }
    cout<<f[n]<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}