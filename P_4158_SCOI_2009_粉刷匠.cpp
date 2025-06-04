#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55,MT=3e3;
int n,m,t,sum[MN][MN],f[MN][MT],g[MN][MN][MN];

signed main(){
    cin>>n>>m>>t;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char x;
            cin>>x;
            sum[i][j]+=sum[i][j-1];
            if(x=='1'){
                sum[i][j]++;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            for(int k=1;k<=m;k++){
                for(int p=j-1;p<k;p++){
                    g[i][j][k]=max(g[i][j][k],g[i][j-1][p]+max(sum[i][k]-sum[i][p],k-p-sum[i][k]+sum[i][p]));

                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=t;j++){
            for(int k=0;k<=min(m,j);k++){
                f[i][j]=max(f[i][j],f[i-1][j-k]+g[i][k][m]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=t;i++) ans=max(ans,f[n][i]);
    cout<<ans;
    return 0;
}
