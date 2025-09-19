#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{int v,id;};
int n,m,etot,bel[MN],ans,ecnt;
vector<int> G[MN];
vector<Edge> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot;
    bool vise[MN],visd[MN];
    void tarjan(int u,int pre){
        low[u]=dfn[u]=++dtot;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(!dfn[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>dfn[u]) vise[id]=1;
            }else if(v!=pre) low[u]=min(low[u],dfn[v]);
        }
    }
    void dfs(int u){
        visd[u]=1; bel[u]=etot;
        for(auto e:adj[u]){
            if(vise[e.id]||visd[e.v]) continue;
            dfs(e.v);
        }
    }
    void solve(){
        for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,i);
        for(int i=1;i<=n;i++) if(!visd[i]){etot++; dfs(i);}
    }
}

namespace Tree{
    int dep[MN]; bool vis[MN];
    vector<int> vct;
    void dfs1(int u,int pre){
        vct.push_back(u); vis[u]=1;
        for(auto v:G[u]) if(v!=pre && !vis[v]) dfs1(v,u);
    }
    void dfs2(int u,int pre){
        dep[u]=dep[pre]+1;
        for(auto v:G[u]) if(v!=pre) dfs2(v,u);
    }
    void initdep(){for(int i=1;i<=etot;i++) dep[i]=0;}
    void solve(int u){
        if(G[u].empty()){ans++; return;}
        vct.clear(); initdep(); dfs1(u,0);
        initdep(); dfs2(u,0);
        int st=u,ed=u,lf=0;
        for(auto p:vct) if(dep[p]>dep[st]) st=p;
        initdep(); dfs2(st,0);
        for(auto p:vct){
            if(dep[p]>dep[ed]) ed=p;
            if(G[p].size()==1) lf++;
        }
        ans+=dep[ed]+lf-2;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v; cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    Tarjan::solve();
    for(int u=1;u<=n;u++)
        for(auto e:adj[u])
            if(bel[u]!=bel[e.v]){
                G[bel[u]].push_back(bel[e.v]);
            }
    for(int i=1;i<=etot;i++)
        if(!Tree::vis[i]){Tree::solve(i); ecnt++;}
    cout<<n-ans+ecnt-1;
    return 0;
}
