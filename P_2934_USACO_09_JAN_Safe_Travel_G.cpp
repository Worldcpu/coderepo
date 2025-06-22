#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v,w;
};
struct EDGE{
    int u,v,w;
};
int n,m,pre[MN],dep[MN],dis[MN],fa[MN],ans[MN];
bool vis[MN];
vector<Edge> adj[MN];
vector<EDGE> eg;

void dij(int st){
    priority_queue<pir,vector<pir>,greater<pir>> q;
    memset(dis,0x3f,sizeof(dis));
    dis[st]=0;
    q.push(pir(0,st));
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
           if(dis[e.v]>dis[u]+e.w){
               dis[e.v]=dis[u]+e.w;
               dep[e.v]=dep[u]+1;
               fa[e.v]=u;
               q.push(pir(dis[e.v],e.v));
           }
        }
    }
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool cmp(EDGE x,EDGE y){
    return dis[x.u]+dis[x.v]+x.w<dis[y.u]+dis[y.v]+y.w;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dij(1);
    for(int u=1;u<=n;u++){
        ans[u]=-1;
        pre[u]=u;
        for(auto e:adj[u]){
            int v=e.v;
            if(fa[u]!=v&&fa[v]!=u&&u<v){
                eg.push_back({u,v,e.w});
            }
        }
    }
    sort(eg.begin(),eg.end(),cmp);
    for(auto p:eg){
        int x=p.u,y=p.v,kw=dis[x]+dis[y]+p.w;
        int rx=root(x),ry=root(y);
        while(rx!=ry){
            if(dep[rx]<dep[ry]) swap(rx,ry);
            ans[rx]=kw-dis[rx];
            pre[rx]=fa[rx];
            rx=root(rx);
        }
    }
    for(int i=2;i<=n;i++) cout<<ans[i]<<'\n';
    return 0;
}
