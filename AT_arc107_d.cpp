#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int f[MN][MN],n,K;


signed main(){
    cin>>n>>K;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j>=1;j--){
            f[i][j]=f[i-1][j-1];
            if(j*2<=i) f[i][j]=(f[i][j]+f[i][j*2])%MOD;
        }
    }
    cout<<f[n][K];

    return 0;
}