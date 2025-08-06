#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4520,MOD=1e9+7;
int f[MN][MN],n,m,K,d,ans;

signed main(){
    cin>>n>>m>>K;
    d=(n+m-1)/(K-1);
    f[0][0]=1;
    for(int i=1;i<=d;i++){
        for(int j=0;j<K;j++){
            for(int k=j;k<=i*K&&k<=m;k++){
                f[i][k]=(f[i][k]+f[i-1][k-j])%MOD;
            }
        }
    }
    for(;m>=1;m-=K-1,--d) ans=(ans+f[d][m])%MOD;
    cout<<ans;
    return 0;
}
