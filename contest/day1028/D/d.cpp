#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int f[4][MN][MN],sum[MN][MN],n,m,a[4][MN],ans;


signed main(){
    cin>>n>>m;
    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }

    memset(f,128,sizeof(f));
    if(!a[1][1]){
        for(int i=1;i<=m;i++){
            f[1][1][i]=1;
            sum[1][1]++;
        }
    }else sum[1][1]=f[1][1][a[1][1]]=1;

    for(int i=1;i<=2;i++){
        for(int j=1;j<=n;j++){
            if(i==1&&j==1) continue;
            if(a[i][j]){
                int k=a[i][j];
                f[i][j][k]=(sum[i-1][j]+sum[i][j-1])%MOD;
                if(f[i-1][j][k]>0){
                    f[i][j][k]=(f[i][j][k]-f[i-1][j][k]+MOD)%MOD;
                }
                if(f[i][j-1][k]>0){
                    f[i][j][k]=(f[i][j][k]-f[i][j-1][k]+MOD)%MOD;
                }
                sum[i][j]+=f[i][j][k];
                continue;
            }
            for(int k=1;k<=m;k++){
                if(a[i-1][j]==k||a[i][j-1]==k||a[i+1][j]==k||a[i][j+1]==k) continue;
                f[i][j][k]=(sum[i-1][j]+sum[i][j-1])%MOD;
                if(f[i-1][j][k]>0){
                    f[i][j][k]=(f[i][j][k]-f[i-1][j][k]+MOD)%MOD;
                }
                if(f[i][j-1][k]>0){
                    f[i][j][k]=(f[i][j][k]-f[i][j-1][k]+MOD)%MOD;
                }
                cerr<<i<<' '<<j<<' '<<k<<" DP: "<<f[i][j][k]<<'\n';
                sum[i][j]+=f[i][j][k];
            }
            ans+=sum[i][j];
        }
    }
    cout<<ans;
    

    return 0;
}