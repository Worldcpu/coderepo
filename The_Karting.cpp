#include<iostream>
#include<cstring>
using namespace std;
constexpr int MN=150;
int f[MN][MN][MN],sum[MN],d[MN],n,m,d0;

void solve(){
    cin>>d0;
    for(int i=2;i<=n;i++) cin>>d[i];
    d[1]=0;
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+d[i];
    }
    memset(f,128,sizeof(f));
    f[0][0][0]=0;
    for(int i=1;i<=n;i++){
        f[i][0][0]=0;
        for(int j=1;j<=i;j++){
            for(int k=0;k<=j;k++){
                f[i][j][k]=max(f[i][j][k],f[i-1][j][k]);
                f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k]);
                f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k+1]+d0+2*sum[i]);
                if(k){
                    f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-1]+d0-2*sum[i]);
                }
            }
        }
    }
    cout<<f[n][m][0]<<'\n';
}

int main(){
    while(cin>>n>>m){
        solve();
    }
    return 0;
}
