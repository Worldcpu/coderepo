#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int ML=19,MN=2e6+15,MOD=1e9+7;
int n,ans,a[MN],f[MN];


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int s=(a[i]-1)&a[i];s;s=(s-1)&a[i]){
            (f[s]+=f[a[i]]+1)%=MOD;
        }
        (ans+=f[a[i]])%=MOD;
    }
    cout<<ans;
    

    return 0;
}