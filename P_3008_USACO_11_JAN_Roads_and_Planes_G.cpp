#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e4+15;
struct edge{
    int v,w;
    bool ish=0;
};
int t,r,p,s,dg[MN],c[MN],dis[MN],tot;
vector<edge> adj[MN],padj[MN];
vector<pir> hd;
vector<int> dcc[MN];
bool vis[MN];
queue<int> q;

void dfs(int u,int fa,int color){
    c[u]=color;
    dcc[color].push_back(u);
    for(auto e:adj[u]){
        if(e.v==fa||e.ish||c[e.v]) continue;
        dfs(e.v,u,color);
    }
}

void dij(int cdcc){
    priority_queue<pir,vector<pir>,greater<pir>> pq;
    for(auto t:dcc[cdcc]){
        if(dis[t]>=1e9) continue;
        pq.push(pir(dis[t],t));
    }
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            if(dis[e.v]>dis[u]+e.w){
                dis[e.v]=dis[u]+e.w;
                pq.push(pir(dis[e.v],e.v));
            }
        }
        for(auto e:padj[u]){
            dis[e.v]=min(dis[e.v],dis[u]+e.w);
        }
    }
}

void topo(){
    for(int i=1;i<=tot;i++){
        if(!dg[i]) q.push(i);
    }
    while(!q.empty()){
        int f=q.front();
        q.pop();
        dij(f);
        for(auto d:dcc[f]){
            for(auto e:padj[d]){
                if(--dg[c[e.v]]==0) q.push(c[e.v]);
            }
        }
    }
}

int main(){
    memset(dis,0x3f,sizeof(dis));
    cin>>t>>r>>p>>s;
    for(int i=1;i<=r;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w,0});
        adj[v].push_back({u,w,0});
    }
    for(int i=1;i<=p;i++){
        int u,v,w;
        cin>>u>>v>>w;
        padj[u].push_back({v,w,1});
    }
    for(int i=1;i<=t;i++){
        if(!c[i]){
            dfs(i,0,++tot);
        }
    }
    for(int i=1;i<=t;i++){
        for(auto e:padj[i]){
            dg[c[e.v]]++;
        }
    }
    dis[s]=0;
    topo();
    for(int i=1;i<=t;i++){
        if(dis[i]>=1e9) cout<<"NO PATH\n";
        else cout<<dis[i]<<'\n';
    }
    return 0;
}