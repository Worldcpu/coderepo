#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3520;
int T,n,K,f[MN][MN],sum[MN][MN],MOD;

void solve(){
    cin>>n>>K>>MOD;
    f[0][0]=1;
    for(int i=0;i<=K;i++){
        f[1][i]=1;
        sum[0][i]=1;
        sum[1][i]=i+1;
    }
    for(int i=2;i<=n+1;i++){
        int ret=0;
        for(int j=K;j>=0;j--){
            f[i][j]=sum[i-1][K];
            (ret+=sum[i-2][K-j-1])%=MOD;
            f[i][j]=(f[i][j]-ret+MOD)%MOD;
        }
        for(int j=0;j<=K;j++){
            sum[i][j]=f[i][j];
            if(j){
                (sum[i][j]+=sum[i][j-1])%=MOD;
            }
        }
    }
    cout<<f[n+1][0]<<'\n';
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=K;j++){
            f[i][j]=sum[i][j]=0;
        }
    }
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
