#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
struct Edge{
    int v,w;
};
int n;

struct Tree{
    int dis[MN],dep[MN],fa[MN],hson[MN],htop[MN],siz[MN];
    vector<Edge> adj[MN];

    void dfs(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        siz[u]=1;
        for(auto e:adj[u]){
            if(e.v==pre) continue;
            dis[e.v]=dis[u]+e.w;
            dfs(e.v,u);
            siz[u]+=siz[e.v];
            if(siz[hson[u]]<siz[e.v]) hson[u]=e.v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto e:adj[u]){
            if(e.v==fa[u]||e.v==hson[u]) continue;
            dfs2(e.v,e.v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    int getdis(int x,int y){
        if(dep[x]>dep[y]) swap(x,y);
        int lcaa=lca(x,y);
        if(x==lcaa) return dis[y]-dis[x];
        else return dis[x]+dis[y]-2*dis[lcaa];
    }
}t1,t2;

int main(){
    freopen("frame.in","r",stdin);
    freopen("frame.out","w",stdout);
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        t1.adj[u].push_back({v,w});
        t1.adj[v].push_back({u,w});
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        t2.adj[u].push_back({v,w});
        t2.adj[v].push_back({u,w});
    }
    t1.dfs(1,0);
    t1.dfs2(1,1);
    t2.dfs(1,0);
    t2.dfs2(1,1);
    for(int i=1;i<=n;i++){
        int ret=1e9;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            int dis1=t1.getdis(i,j),dis2=t2.getdis(i,j);
            ret=min(ret,dis1+dis2);
        }
        cout<<ret<<'\n';
    }
    

    return 0;
}