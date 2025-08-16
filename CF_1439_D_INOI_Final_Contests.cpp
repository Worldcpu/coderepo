#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int f[MN][MN],g[MN][MN],C[MN][MN],n,m,MOD;

void init(){
    for(int i=0;i<MN;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }
}

int sum(int x){
    return x*(x+1)/2%MOD;
}

signed main(){
    cin>>n>>m>>MOD;
    init();
    g[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            (g[i][i]+=(i+1)*g[j-1][j-1]%MOD*g[i-j][i-j]%MOD*C[i-1][j-1]%MOD)%=MOD;
            (f[i][i]+=(sum(i-j)+sum(j-1))%MOD*g[j-1][j-1]%MOD*g[i-j][i-j]%MOD*C[i-1][j-1]%MOD)%=MOD;
            (f[i][i]+=(i+1)*C[i-1][j-1]%MOD*(f[j-1][j-1]*g[i-j][i-j]%MOD+f[i-j][i-j]*g[j-1][j-1]%MOD)%MOD)%=MOD;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            f[i][j]=f[i-1][j],g[i][j]=g[i-1][j];
            for(int k=1;k<=j;k++){
                g[i][j]=(g[i][j]+g[k][k]*g[i-k-1][j-k]%MOD*C[j][k]%MOD)%MOD;
                (f[i][j]+=(f[i-k-1][j-k]*g[k][k]%MOD+f[k][k]*g[i-k-1][j-k]%MOD)%MOD*C[j][k]%MOD)%=MOD;
                
            }
        }
    }
    cout<<f[n][m];

    return 0;
}