#include<bits/stdc++.h>
using namespace std;
const int MN=3831;
int n,m,a[MN],f[MN][MN][2],ans;
void solve(){
    ans=0;
    memset(f,128,sizeof(f));
    // memset(g,128,sizeof(g));
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    f[1][0][0]=0;
    f[1][1][1]=0;
    // g[1][1][1]=a[1];
    // g[1][0][0]=0;
    for(int i=2;i<=n;i++){
        f[i][0][0]=f[i-1][0][0];
        // g[i][0][0]=g[i-1][0][0];
        for(int j=1;j<=m;j++){
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
            f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
            // g[i][j][0]=max(g[i-1][j][0],g[i-1][j][1]);
            // g[i][j][1]=max(g[i-1][j-1][0],g[i-1][j-1][1]+a[i]);
        }
    }
    ans=max(f[n][m][0],f[n][m][1]);
    memset(f,128,sizeof(f));
    f[1][0][0]=0;
    f[1][1][1]=a[1];
    for(int i=2;i<=n;i++){
        f[i][0][0]=f[i-1][0][0];
        // g[i][0][0]=g[i-1][0][0];
        for(int j=1;j<=m;j++){
            f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
            f[i][j][1]=max(f[i-1][j-1][0],f[i-1][j-1][1]+a[i]);
            // g[i][j][0]=max(g[i-1][j][0],g[i-1][j][1]);
            // g[i][j][1]=max(g[i-1][j-1][0],g[i-1][j-1][1]+a[i]);
        }
    }
    cout<<max(ans,f[n][m][1]);
}
int main(){
    int T;
    cin>>T;
    while (T--)
    {
        solve();
    }
    
}