#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e3+15,MOD=998244353;
int f[MN][MN][2],n,pw[MN],inv[MN],ans,g[MN];
vector<int> adj[MN];

namespace Tree{
    int siz[MN];

    void dfs(int u,int pre){
        siz[u]=1;
        f[u][0][0]=f[u][1][1]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
            for(int j=siz[u]+siz[v];j>=1;j--){
                for(int k=max(1ll,j-siz[u]);k<=min(siz[v],j);k++){
                    f[u][j][0]=(f[u][j][0]+f[u][j-k][0]*(f[v][k][0]+f[v][k][1])%MOD)%MOD;
                    f[u][j][1]=(f[u][j][1]+f[u][j-k][1]*f[v][k][0]%MOD)%MOD;
                }
            }
            siz[u]+=siz[v];
        }
    }
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tree::dfs(1,0);
    for(int i=0;i<=n;i++){
        g[i]=((f[1][i][0]+f[1][i][1])%MOD*pw[i]%MOD*pw[n-i])%MOD;
    }
    for(int i=0;i<n;i++){
        ans=(ans+(g[i]-g[i+1]+MOD)%MOD*(n-i)%MOD)%MOD;
    }
    cout<<ans*inv[n]%MOD;

    return 0;
}