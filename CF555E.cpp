#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,id;
};
int col[MN],n,m,q;
vector<int> G[MN];
vector<Edge> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],edcc,dtot;
    bool gb[MN],vis[MN];

    void tarjan(int u,int pre){
        low[u]=dfn[u]=++dtot;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(!dfn[v]){
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>dfn[u]){
                    gb[e.id]=1;
                }
            }else if(v!=pre){
                low[u]=min(low[u],dfn[v]);
            }
        }
    }

    void dfs(int u){
        vis[u]=1;
        if(u) col[u]=edcc;
        for(auto e:adj[u]){
            int v=e.v,id=e.id;
            if(gb[id]||vis[v]) continue;
            dfs(v);
        }
    }

    void solve(){
        for(int i=1;i<=n;i++){
            if(!dfn[i]) tarjan(i,i);
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]){
                edcc++;
                dfs(i);
            }
        }
    }

}

namespace Tree{
    int hson[MN],htop[MN],siz[MN],dep[MN],fa[MN],cfa[MN],cfb[MN];

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        siz[u]=1;
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:G[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    void dfs3(int u,int pre){
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs3(v,u);
            cfa[u]+=cfa[v];
            cfb[u]+=cfb[v];
        }
    }

}using namespace Tree;

namespace DSU{
    int pre[MN];

    void initpre(){
        for(int i=0;i<MN;i++){
            pre[i]=i;
        }
    }
    
    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

}using namespace DSU;


int main(){
    cin>>n>>m>>q;
    initpre();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    Tarjan::solve();
    for(int u=1;u<=n;u++){
        for(auto e:adj[u]){
            if(col[u]!=col[e.v]){
                G[col[u]].push_back(col[e.v]);
                pre[root(col[e.v])]=root(col[u]);
            }
        }
    }   
    for(int i=1;i<=Tarjan::edcc;i++){
        if(pre[i]==i){
            dfs1(i,0);
            dfs2(i,i);   
        }
    }
    for(int i=1;i<=q;i++){
        int x,y;
        cin>>x>>y;
        int cx=col[x],cy=col[y],clca=lca(cx,cy);
        if(root(cx)!=root(cy)){
            cout<<"No\n";
            return 0;
        }
        cfa[cx]++;
        cfa[clca]--;
        cfb[cy]++;
        cfb[clca]--;
    }
    for(int i=1;i<=Tarjan::edcc;i++){
        if(pre[i]==i){
            dfs3(i,0);
        }
    }
    for(int i=1;i<=Tarjan::edcc;i++){
        if(cfa[i]&&cfb[i]){
            cout<<"No\n";
            return 0;
        }
    }
    cout<<"Yes\n";

    
    
    return 0;
}