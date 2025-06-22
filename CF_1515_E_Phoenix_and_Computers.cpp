#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520;
int f[MN][MN],n,MOD;

signed main(){
    cin>>n>>MOD;
    f[0][0]=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            f[i+1][j+1]=(f[i+1][j+1]+f[i][j]*(j+1)%MOD)%MOD;
            f[i+1][j]=(f[i+1][j]+f[i][j]*2*j%MOD)%MOD;
            f[i+2][j]=(f[i+2][j]+f[i][j]*2*j%MOD)%MOD;
            if(j>=2){
                f[i+2][j-1]=(f[i+2][j-1]+f[i][j]*(j-1)%MOD*2%MOD)%MOD;
                f[i+3][j-1]=(f[i+3][j-1]+f[i][j]*(j-1)%MOD)%MOD;
            }
        }
    }
    cout<<f[n][1]<<'\n';
    return 0;
}
