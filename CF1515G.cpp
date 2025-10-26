#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int v,w;
};
int n,m,q,res[MN];
vector<Edge> adj[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot,st[MN],top,col[MN],vdcc,db[MN];
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto e:adj[u]){
            if(!dfn[e.v]){
                tarjan(e.v);
                low[u]=min(low[u],low[e.v]);
            }else if(vis[e.v]){
                low[u]=min(low[u],dfn[e.v]);
            }
        }
        if(low[u]==dfn[u]){
            int p;
            vdcc++;
            do{
                p=st[top--];
                vis[p]=0;
                col[p]=vdcc;
                db[vdcc]=p;
            }while(p!=u);
        }
    }

    
}using namespace Tarjan;

namespace Tree{
    int dis[MN];
    bool vis[MN];

    void dfs1(int u,int cid){
        vis[u]=1;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(col[v]!=cid) continue;
            if(vis[v]){
                res[cid]=__gcd(abs(dis[u]-dis[v]+w),res[cid]);
                continue;
            }
            dis[v]=dis[u]+w;
            dfs1(v,cid);
        }
    }
    
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    for(int i=1;i<=n;i++){
        if(!Tarjan::dfn[i]){
            Tarjan::tarjan(i);
        }
    }
    for(int i=1;i<=n;i++){
        if(!Tree::vis[i]){
            Tree::dfs1(i,col[i]);
        }
    }

    cin>>q;
    while(q--){
        int v,s,t;
        cin>>v>>s>>t;
        if(s%__gcd(res[col[v]],t)==0){
            cout<<"YES\n";
        }else cout<<"NO\n";
    }

    



    return 0;
}