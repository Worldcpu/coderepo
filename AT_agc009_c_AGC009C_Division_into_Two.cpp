#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e9+7;
int f[MN],sum[MN],n,a[MN],A,B;


signed main(){
    cin>>n>>A>>B;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i+2<=n;i++){
        if(a[i+2]-a[i]<A&&a[i+2]-a[i]<B){
            cout<<0;
            return 0;
        }
    }
    if(A<B) swap(A,B);
    f[0]=sum[0]=1;
    for(int i=1,l=0,r=0;i<=n;i++){
        while(r<i&&a[i]-a[r+1]>=A) r++;
        if(l<=r){
            f[i]=(f[i]+(sum[r]-(l?sum[l-1]:0)+MOD)%MOD)%MOD;
        }
        sum[i]=(sum[i-1]+f[i])%MOD;
        if(i>1&&a[i]-a[i-1]<B) l=i-1;
    }
    int ans=0;
    for(int i=n;i>=0;i--){
        (ans+=f[i])%=MOD;
        if(i<n&&a[i+1]-a[i]<B) break;
    }
    cout<<ans;

    return 0;
}
