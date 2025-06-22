#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3520,MOD=1e9+7;
int n,m,f[MN][MN][2];


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        f[0][i][0]=1;
    }
    f[0][0][1]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=n;j++){
            f[i][j][0]%=MOD;
            f[i][j][1]%=MOD;
            if(j-1>=0){
                if(j==1) f[i+1][j-1][1]+=f[i][j][0];
                else f[i+1][j-1][0]+=f[i][j][0];
                f[i+1][j-1][1]+=f[i][j][1];
                if(j==1) f[i+1][j][1]+=f[i][j][0];
                else f[i+1][j][0]+=f[i][j][0];
                f[i+1][j][1]+=f[i][j][1];
            }
            if(j+1<=n){
                f[i+1][j+1][0]+=f[i][j][0];
                f[i+1][j+1][1]+=f[i][j][1];
                f[i+1][j][0]+=f[i][j][0];
                f[i+1][j][1]+=f[i][j][1];
            }
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++) (ans+=f[m][i][1])%=MOD;
    cout<<ans;
    return 0;
}
