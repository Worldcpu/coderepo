#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=998244353;
int g[2][MN][MN],f[MN][MN],n,K;
string st;

void init(){
    for(int i=1;i<=n+1;i++){
        fill(f[i],f[i]+1+K,0);
    }
}

void solve(){
    cin>>n>>K>>st;
    init();
    st=" "+st;
    f[n+1][0]=1;
    for(int i=n;i>=1;i--){
        for(int j=0;j<=K;j++){
            for(int k=0;k<=j;k++){
                f[i][j]=(f[i][j]+f[i+1][j-k]*g[st[i]-'0'][j-k][k]%MOD)%MOD;
            }
        }
    }
    cout<<f[1][K]<<'\n';
}

void initg(){
    for(int i=0;i<2;i++){
        g[i][0][0]=1;
        g[i][0][1]=(!i);
        for(int j=1;j<=500;j++){
            for(int k=0;k<=500;k++){
                g[i][j][k]=g[i][j-1][k];
                if(k&&(i^j^k)&1){
                    g[i][j][k]=(g[i][j][k]+g[i][j][k-1])%MOD;
                }
            }
        }
    }
}

signed main(){
    initg();
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}