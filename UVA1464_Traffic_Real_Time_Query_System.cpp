#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,vis[MN],tot;
pir e[MN];
vector<int> adj[MN],G[MN];

namespace YFTree{
    int dfn[MN],low[MN],s[MN],top,dtot,ftot;

    void inityf(){
        ftot=n;
    }

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
        vis[u]=tot;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]==dfn[u]){
                    ++ftot;
                    int p;
                    do{
                        p=s[top--];
                        G[ftot].push_back(p);
                        G[p].push_back(ftot);
                    }while(p!=v);
                    G[ftot].push_back(u);
                    G[u].push_back(ftot);
                }
            }else low[u]=min(low[u],dfn[v]);
        }
    }

}using namespace YFTree;

namespace Tree{
    int dep[MN],fa[MN],siz[MN],hson[MN],htop[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        fa[u]=pre;
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

    int dis(int x,int y){
        if(vis[x]!=vis[y]) return 0;
        int ret=dep[x]+dep[y]-(dep[lca(x,y)]<<1);
        return ret/2-1;
    }

}using namespace Tree;

void init(){
    dtot=tot=0;
    for(int i=1;i<=ftot;i++){
        adj[i].clear();
        G[i].clear();
        low[i]=dfn[i]=0;
        dep[i]=hson[i]=fa[i]=vis[i]=htop[i]=siz[i]=0;
    }
    ftot=n;
}

void solve(){
    init();
    inityf();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        e[i]=pir(u,v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]){
            tot++;
            vis[i]=1;
            tarjan(i);
            dfs1(i,0);
            dfs2(i,i);
        }
    }
    int q;
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int a=e[x].first,b=e[x].second,c=e[y].first,d=e[y].second;
        int ans=max({dis(a,c),dis(a,d),dis(b,c),dis(b,d)});
        cout<<ans<<'\n';
    }

}

int main(){
    while(1){
        cin>>n>>m;
        if(!n&&!m) break;
        solve();
    }
    return 0;
}
