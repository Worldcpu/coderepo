#include<bits/stdc++.h>
using namespace std;
constexpr int MN=101;
int f[MN][MN][MN],C[MN][MN];
int g[MN][MN],pw[MN],inv[MN],n,m,K,MOD;

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=1ll*pw[i-1]*i%MOD;
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return C[a][b];
}

signed main(){
    cin>>n>>m>>K>>MOD;
    init();
    g[1][1]=1;
    for(int i=2;i<=n;i++){
        g[i][1]=1;
        for(int j=2;j<=i;j++){
            for(int k=1;k<=i;k++){
                g[i][j]=max(g[i][j],g[k-1][j-1]+g[i-k][j-1]);
            }
        }
    }
    if(K>g[n][m]){
        cout<<0;
        return 0;
    }
    f[1][1][1]=1;
    for(int i=0;i<=n;i++) f[0][i][0]=1;
    for(int i=0;i<=n;i++) f[1][i][0]=1;
    f[1][1][0]=0;
    for(int i=2;i<=n;i++){
        f[i][1][1]=pw[i];
        for(int j=2;j<=min(i,m);j++){
            for(int k=0;k<=min(i-j+1,K);k++){
                for(int p=1;p<=i;p++){
                    for(int l=0;l<=k;l++){
                        (f[i][j][k]+=(long long)f[p-1][j-1][l]*f[i-p][j-1][k-l]%MOD*getC(i-1,p-1)%MOD)%=MOD;
                    }
                }
            }
        }
        for(int j=min(i,m)+1;j<=m;j++) f[i][j][0]=pw[i];
    }
    cout<<f[n][m][K];
    return 0;
}
