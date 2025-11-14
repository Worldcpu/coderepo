#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
struct Edge{
    int u,v,w,vis;
}e[MN];
struct EDge{
    int v,w;
};
int n,m,ans;
vector<EDge> adj[MN];

namespace DSU{
    int pre[MN];

    void initpre(){
        iota(pre+1,pre+1+n,1);
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
}using namespace DSU;

namespace Kruskal{
    
    bool cmpe(Edge x,Edge y){
        return x.w<y.w;
    }

    void kru(){
        sort(e+1,e+1+m,cmpe);
        for(int i=1;i<=m;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru==rv) continue;
            pre[ru]=rv;
            adj[e[i].u].push_back({e[i].v,e[i].w});
            adj[e[i].v].push_back({e[i].u,e[i].w});
            e[i].vis=1;
        }
    }
}using namespace Kruskal;

namespace Tree{
    int dis1_mn[MN],disn_mn[MN],dis1_mx[MN],disn_mx[MN];

    void dfs1(int u,int pre,int dis[]){
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre) continue;
            dis[v]=max(dis[u],w);
            dfs1(v,u,dis);
        }
    }

    void dfs2(int u,int pre,int dis[]){
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre) continue;
            dis[v]=min(dis[u],w);
            dfs2(v,u,dis);
        }
    }

}using namespace Tree;

void init(){
    initpre();
    for(int i=1;i<=n;i++){
        dis1_mn[i]=dis1_mx[i]=disn_mx[i]=disn_mn[i]=0;
        adj[i].clear();
    }
    for(int i=1;i<=m;i++) e[i].vis=0;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
        e[i].vis=0;
    }
    kru();
    dis1_mn[1]=INF;
    dfs2(1,0,dis1_mn);
    dfs1(1,0,dis1_mx);
    dis1_mn[1]=0;

    ans=dis1_mx[n]+dis1_mn[n];
    for(int i=2;i<=n;i++){
        int mx=max(dis1_mx[i],dis1_mx[n]),mn=min(dis1_mn[i],dis1_mn[n]);
        ans=min(ans,mx+mn);
    }
    cout<<ans<<'\n';
}


int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}