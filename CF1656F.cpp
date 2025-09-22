#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int a[MN],sum[MN],ans,n;

int calc(int x,int t){
    return (a[1]+t)*(sum[n-1]-sum[x]+t*(n-x-1))+(a[n]+t)*(sum[x]+t*x)-t*t*(n-1);
}

void init(){
    ans=-1e18;
    for(int i=1;i<=n;i++){
        a[i]=sum[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
    }
    if(a[1]*(n-2)+sum[n]>0||a[n]*(n-2)+sum[n]<0){
        cout<<"INF\n";
        return;
    }
    for(int i=1;i<n;i++){
        ans=max(ans,calc(i,-a[i]));
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}