#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e3+15,MOD=998244353;
int f[MN][MN],sum[MN],a[MN][MN],n,m,ans=1;

int calc(int x){
    f[0][n]=1;
    for(int i=1;i<=n;i++){
        for(int j=-i;j<=i;j++){
            int k=j+n;
            f[i][k]=0;
            (f[i][k]+=f[i-1][k-1]*a[i][x]%MOD)%=MOD;
            (f[i][k]+=f[i-1][k])%=MOD;
            (f[i][k]+=f[i-1][k+1]*(sum[i]-a[i][x]+MOD)%MOD)%=MOD;
        }
    }
    int ret=0;
    for(int i=1;i<=n;i++){
        ret=(ret+f[n][i+n])%MOD;
    }
    return ret;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            (sum[i]+=a[i][j])%=MOD;
        }
        ans*=(sum[i]+1)%MOD;
        ans%=MOD;
    }
    ans=(ans-1+MOD)%MOD;
    for(int i=1;i<=m;i++){
        ans=(ans-calc(i)+MOD)%MOD;
    }
    cout<<ans;
    return 0;
}