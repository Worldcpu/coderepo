#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15,MOD=1e9+7;
int f[MN][2],n,a[MN],ans;

signed main(){
    freopen("basic.in","r",stdin);
    freopen("basic.out","w",stdout);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]++;
    }
    f[1][0]=1;
    for(int i=1;i<=n;i++){
        f[a[i]+1][0]=(f[a[i]+1][0]+f[a[i]][0]+f[a[i]+1][0])%MOD;
        f[a[i]+1][1]=(f[a[i]+1][1]+f[a[i]+1][1])%MOD;
        if(i>1){
            f[a[i]-1][1]=(f[a[i]-1][1]+f[a[i]-1][0]+f[a[i]-1][1])%MOD;
        }
    }
    for(int i=1;i<=n+1;i++){
        ans=(ans+f[i][0]+f[i][1])%MOD;
    }
    cout<<(ans-1+MOD)%MOD;
    return 0;
}