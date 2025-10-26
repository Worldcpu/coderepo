#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],res,ans=1e18;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    res=0;
    for(int i=1;i<=n;i++){
        res=__gcd(res,2*a[i]-2*a[1]);
    }
    ans=min(ans,a[1]%res+a[n]-a[1]);
    res=0;
    for(int i=1;i<=n;i++){
        res=__gcd(res,2*a[n]-2*a[i]);
    }
    ans=min(ans,a[n]%res+a[n]-a[1]);
    cout<<ans;
    return 0;
}