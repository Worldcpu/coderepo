#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,a[MN],sum[MN],ans;
bitset<MN> f;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    f[1]=1;
    for(int i=1;i<=n;i++){
        if(f[i]) ans=max(ans,sum[i]-i+1);
        f|=f<<a[i];
        f[i]=0;
    }
    for(int i=n+1;i<=2*n;i++){
        if(f[i]) ans=max(ans,sum[n]-i+1);
    }
    cout<<ans;
    

    return 0;
}