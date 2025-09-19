#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int n,m,etot,bel[MN],dg[MN],cnt;
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
                if(low[v]>dfn[u]){
                    vise[id]=1;
                }
            }else if(v!=pre){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }

    void dfs(int u){
        visd[u]=1;
        bel[u]=etot;
        for(auto e:adj[u]){
            if(vise[e.id]||visd[e.v]) continue;
            dfs(e.v);
        }       
    }

    void solve(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i,i);
        }
        for(int i=1;i<=n;i++){
            if(!visd[i]){
                etot++;
                dfs(i);
            }
        }
    }

}


int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    Tarjan::solve();
    for(int u=1;u<=n;u++){
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(bel[u]!=bel[v]){
                dg[bel[u]]++;
                dg[bel[v]];;
            }
        }
    }
    for(int i=1;i<=etot;i++){
        cnt+=(dg[i]==1);
    }
    cout<<((cnt+1)>>1)<<'\n';
    return 0;
}