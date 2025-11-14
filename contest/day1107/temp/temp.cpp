#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,T,a[MN],ans;

signed main(){
    cin>>n>>T;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]%=T;
    }
    sort(a+1,a+1+n);
    for(int i=1;i<n;i++){
        ans=max(ans,abs(a[i]-a[i+1]));
    }
    ans=max(ans,a[1]-a[n]+T);
    if(ans==T){
        cout<<0;
    }else cout<<(T-ans-1)/2+1;

    return 0;
}
