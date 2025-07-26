#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=301,MOD=998244353;
int f[MN][MN][MN],g[MN][MN][MN],n,m;

signed main(){
    cin>>n>>m;
    for(int i=0;i<MN;i++){
        for(int j=0;j<MN;j++){
            for(int k=0;k<MN;k++){
                g[i][j][k]=n+1;
            }
        }
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        for(int k=l;k<=r;k++){
            g[l][r][k]=min(g[l][r][k],l);
        }
    }
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=l;k<=r;k++){
                g[l][r][k]=min({g[l][r][k],g[l][r-1][k],g[l+1][r][k]});
            }
        }
    }
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n+1;j++){
            f[i][i-1][j]=1;
        }
    }
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            for(int k=r;k>=l;k--){
                f[l][r][k]=(f[l][r][k]+f[l][r][k+1]+f[l][k-1][g[l][r][k]]*f[k+1][r][k+1]%MOD)%MOD;
            }
        }
    }
    cout<<f[1][n][1]<<'\n';
    return 0;
}