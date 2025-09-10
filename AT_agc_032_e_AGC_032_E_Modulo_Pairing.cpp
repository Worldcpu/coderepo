#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,K,a[MN],ans=1e18;

bool check(int k){
    k*=2;
    int ret=0;
    for(int i=1;i<=k/2;i++){
        ret=max(ret,a[i]+a[k-i+1]);
    }
    for(int i=1;i<=(n-k)/2;i++){
        int v=a[i+k]+a[n-i+1];
        if(v<K){
            return 0;
        }
        v-=K;
        ret=max(ret,v);
    }
    ans=min(ans,ret);
    return 1;
}

signed main(){
    cin>>n>>K;
    n<<=1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    int l=-1,r=n/2+1;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    cout<<ans;

    return 0;
}