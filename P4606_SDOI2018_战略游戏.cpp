#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e6+15;
int n,m,q,ftot,s[MN];
vector<int> adj[MN],G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],s[MN],top,dtot;

    void init(){
        ftot=n;
    }

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]==dfn[u]){
                    int p;
                    ++ftot;
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

}

namespace Tree{
    int dfn[MN],dep[MN],dis[MN],siz[MN],fa[MN],hson[MN],htop[MN],dtot;

    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        dis[u]=dis[pre]+(u<=n);
        fa[u]=pre;
        hson[u]=0;
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        dfn[u]=++dtot;
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:G[u]){
            if(v==hson[u]||v==fa[u]) continue;
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

    bool cmpdfn(int x,int y){
        return dfn[x]<dfn[y];
    }

}using namespace Tree;

void init(){
    Tarjan::top=Tarjan::dtot=0;
    dtot=0;
    for(int i=1;i<=ftot;i++){
        dfn[i]=dep[i]=dis[i]=siz[i]=hson[i]=htop[i]=fa[i]=0;
        Tarjan::low[i]=Tarjan::dfn[i]=0;
        G[i].clear();
        adj[i].clear();
    }
    ftot=0;
}

void solve(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tarjan::init();
    Tarjan::tarjan(1);
    Tarjan::top--;
    dfs1(1,0);
    dfs2(1,1);
    cin>>q;
    while(q--){
        int sz;
        cin>>sz;
        for(int i=1;i<=sz;i++){
            cin>>s[i];
        }
        sort(s+1,s+1+sz,cmpdfn);
        int ans=-2*sz;
        for(int i=1;i<sz;i++) ans+=dis[s[i]]+dis[s[i+1]]-(dis[lca(s[i],s[i+1])]<<1);
        ans+=dis[s[sz]]+dis[s[1]]-(dis[lca(s[sz],s[1])]<<1);
        if(lca(s[1],s[sz])<=n){
            ans+=2;
        }
        cout<<(ans/2)<<'\n';
    }
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
