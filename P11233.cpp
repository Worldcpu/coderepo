#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],sum[MN],f[MN];
unordered_map<int,int> lst;

void init(){
    lst.clear();
    for(int i=1;i<=n;i++){
        sum[i]=f[i]=a[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=2;i<=n;i++){
        sum[i]=sum[i-1]+a[i]*(a[i]==a[i-1]);
    }
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        if(lst[a[i]]){
            f[i]=max(f[i],f[lst[a[i]]+1]+a[i]+sum[i]-sum[lst[a[i]]+1]);
        }
        lst[a[i]]=i;
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