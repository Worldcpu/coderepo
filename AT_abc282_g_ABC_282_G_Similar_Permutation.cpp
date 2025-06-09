#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=110;
int n,K,MOD,f[MN][MN][MN][MN],sum[MN][MN][MN][MN];

signed main(){
    cin>>n>>K>>MOD;
    f[1][0][1][1]=sum[1][0][1][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=K;j++){
            for(int k=1;k<=i;k++){
                for(int p=1;p<=i;p++){
                    f[i][j][k][p]=((f[i][j][k][p]+sum[i-1][j-1][k-1][p-1])%MOD+MOD)%MOD;
                    f[i][j][k][p]=((f[i][j][k][p]+sum[i-1][j][k-1][i-1]-sum[i-1][j][k-1][p-1])%MOD+MOD)%MOD;
                    f[i][j][k][p]=((f[i][j][k][p]+sum[i-1][j][i-1][p-1]-sum[i-1][j][k-1][p-1])%MOD+MOD)%MOD;
                    f[i][j][k][p]=((f[i][j][k][p]+sum[i-1][j-1][i-1][i-1]-sum[i-1][j-1][k-1][i-1]-sum[i-1][j-1][i-1][p-1])%MOD+sum[i-1][j-1][k-1][p-1]%MOD+MOD)%MOD;
                    sum[i][j][k][p]=(((sum[i][j][k-1][p]+sum[i][j][k][p-1]-sum[i][j][k-1][p-1])%MOD+MOD)%MOD+f[i][j][k][p])%MOD;
                }
            }
        }
    }
    cout<<sum[n][K][n][n];
    return 0;
}
