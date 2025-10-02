#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=220,MP=62;
int n,m,f[MP+5][MN][MN][2],a[MN],sum[MN];

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    memset(f,-0x3f,sizeof(f));
    for(int i=1;i<=n;i++){
        f[0][i][i][0]=f[0][i][i][1]=0;
    }
    for(int i=0;i<=MP;i++){
        for(int j=1;j<=n+1;j++){
            for(int k=0;k<2;k++){
                f[i][j][j-1][k]=0;
            }
        }
    }
    for(int i=1;i<=MP;i++){
        for(int len=1;len<=n;len++){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1;
                for(int k=0;k<2;k++){
                    if(!((m>>(i-1))&1)&&k){
                        f[i][l][r][k]=f[i-1][l][r][k];
                    }else{
                        for(int p=l-1;p<=r;p++){
                            f[i][l][r][k]=max(f[i][l][r][k],f[i-1][l][p][0]+f[i-1][p+1][r][k]+sum[r]-sum[p]);
                        }
                    }
                }
            }
        }
    }
    cout<<f[MP][1][n][1];
    return 0;
}