#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=119,MV=2520,MOD=1e9+7,D=1001;
int f[MN][MV],n,a[MN],g[MV],sum,ans;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    f[0][D]=g[D]=1;
    for(int i=1;i<=n;i++){
        for(int j=-sum;j<=sum;j++){
            f[i][j+D]=(f[i-1][j+D]+f[i][j+D])%MOD;
            if(j){
                f[i][j+a[i]+D]=(f[i][j+a[i]+D]+f[i-1][j+D])%MOD;
                f[i][j+a[i]+D]=(f[i][j+a[i]+D]+g[j+D])%MOD;
            }
        }
        g[a[i]+D]=g[D];
        g[D]=f[i][D];
        sum+=abs(a[i]);
    }
    for(int i=-sum;i<=sum;i++){
        ans=(ans+f[n][i+D])%MOD;
    }
    cout<<ans;

    return 0;
}