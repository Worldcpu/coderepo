#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int n,f[MN][MN],g[MN],pw[MN],ans;
vector<int> adj[MN];

namespace Tree{
    int fa[MN],siz[MN];

    void dfs1(int u,int pre){
        f[u][0]=1;
        siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            fill(g,g+siz[u]+siz[v]+1,0);
            for(int j=0;j<=siz[u];j++){
                for(int k=0;k<=siz[v];k++){
                    g[j+k]=(g[j+k]+f[u][j]*f[v][k]%MOD)%MOD;
                }
            }
            siz[u]+=siz[v];
            for(int j=0;j<=siz[u];j++) f[u][j]=g[j];
        }
        for(int i=siz[u];i>=1;i--){
            f[u][i]=(f[u][i]+f[u][i-1]*((siz[u]-1)-(i-1))%MOD+MOD)%MOD;
        }
    }

}using namespace Tree;

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=2;i<=n;i++){
        cin>>fa[i];
        adj[fa[i]].push_back(i);
    }
    dfs1(1,0);
    for(int i=0;i<=n;i++){
        int k=((i&1)?MOD-1:1);
        ans=(ans+k*f[1][i]%MOD*pw[n-i]%MOD)%MOD;
    }
    cout<<ans;
    return 0;
}