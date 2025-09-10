#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e3+15,MM=1e6+15,INF=1e18,MOD=1e9+7;
int n,m,a[MN],w[MN],st[MM],ctot,ans,f[MN][MN];
vector<int> adj[MN];

namespace Tree{
    int dep[MN],maxp[MN],siz[MN],dfn[MN],rt,sum;
    bool vis[MN];

    void dfs1(int u,int pre){ // getrt
        siz[u]=1;
        maxp[u]=0;
        for(auto v:adj[u]){
            if(v==pre||vis[v]) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            maxp[u]=max(maxp[u],siz[v]);
        }
        maxp[u]=max(maxp[u],sum-siz[u]);
        if(maxp[u]<maxp[rt]) rt=u;
    }

    void dfs2(int u,int pre){
        for(int i=1;i<=ctot;i++) f[u][i]=0;
        for(int i=1;i<=ctot;i++){
            if(w[i]>=a[u]){
                (f[u][st[w[i]/a[u]]]+=f[pre][i])%=MOD;
            }
        }
        for(auto v:adj[u]){
            if(vis[v]||v==pre) continue;
            dfs2(v,u);
            for(int i=1;i<=ctot;i++){
                (f[u][i]+=f[v][i])%=MOD;
            }
        }
    }

    void calc(int u){
        f[0][ctot]=1;
        dfs2(u,0);
        for(int i=1;i<=ctot;i++){
            (ans+=f[u][i])%=MOD;
        }
        f[u][ctot]=0;
    }

    void solve(int u){
        vis[u]=1;
        calc(u);
        for(auto v:adj[u]){
            if(vis[v]) continue;
            sum=siz[v];
            maxp[rt=0]=INF;
            dfs1(v,0);
            solve(rt);
        }
    }

}using namespace Tree;

void init(){
    rt=ans=0;
    sum=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        vis[i]=0;
        a[i]=0;
        dfn[i]=maxp[i]=dep[i]=siz[i]=dfn[i]=0;
    }
    for(int i=1;i<=ctot;i++){
        st[w[i]]=0;
        w[i]=0;
    }
    ctot=0;
}

void prework(){
    for(int i=m,ls=0;i>=1;i--){
        int x=m/i;
        w[st[x]=x!=ls?++ctot:ctot]=x;
        ls=x;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=ctot;j++){
            f[i][j]=0;
        }
    }
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    prework();
    maxp[rt=0]=sum=n;
    dfs1(1,0);
    solve(rt);
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}