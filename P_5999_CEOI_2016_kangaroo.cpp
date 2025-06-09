#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e3+15,MOD=1e9+7;
int n,s,t,f[MN][MN];

signed main(){
    cin>>n>>s>>t;
    f[1][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(i!=s&&i!=t){
                f[i][j]=((j*f[i-1][j+1])%MOD+f[i-1][j-1]*(j-(i>s)-(i>t))%MOD)%MOD;
            }
            else f[i][j]=(f[i-1][j]+f[i-1][j-1])%MOD;
        }
    }
    cout<<f[n][1];
    return 0;
}
