#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int f[MN][MN],g[MN][MN],n,p[MN],p2[MN],nxt[MN];
bool vis[MN];

void init(){
    for(int i=0;i<=n;i++){
        vis[i]=0;
        p[i]=0;
        p2[i]=nxt[i]=0;
        for(int j=0;j<=n;j++){
            f[i][j]=g[i][j]=0;
        }
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>p[i];
        p2[p[i]]=i;
        if(p[i]) vis[p[i]]=1;
    }
    nxt[n+1]=n+1,nxt[0]=1;
    for(int i=n;i>=1;i--){
        if(!vis[i]) nxt[i]=i;
        else nxt[i]=nxt[i+1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            g[i][j]=g[i][j-1]+(p2[j]<=i);
        }
    }
    if(p[1]) f[1][p[1]]=1;
    else f[1][nxt[1]]=1;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(!f[i][j]) continue;
            if(p[i+1]){
                if(p[i+1]<j){
                    f[i+1][j]=(f[i+1][j]+f[i][j]*i%MOD)%MOD;
                }else{
                    if(!vis[j]){
                        f[i+1][nxt[p[i+1]+1]]=(f[i+1][nxt[p[i+1]+1]]+f[i][j]*i%MOD)%MOD;
                    }
                    (f[i+1][p[i+1]]+=f[i][j])%=MOD;
                }
            }else{
                (f[i+1][nxt[j+1]]+=f[i][j])%=MOD;
                if(g[i+1][j]>=i+1) (f[i+1][j]+=f[i][j]*i%MOD)%=MOD;
                else if(!vis[j]) (f[i+1][nxt[j+1]]+=f[i][j]*i%MOD)%=MOD;
            }
        }
    }
    cout<<f[n][n]<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}