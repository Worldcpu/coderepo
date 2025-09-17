#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int v,w;
};
int S,T,n,m,K,a[MN],ans;
vector<Edge> adj[MN],G[MN];

namespace Dijkstra{
    int dis[MN];
    bool vis[MN];
    void initdijk(){
        for(int i=1;i<=n+2;i++){
            dis[i]=INF;
            vis[i]=0;
        }
    }
    void dijk(){
        initdijk();
        priority_queue<pir,vector<pir>,greater<pir>> q;
        dis[S]=0;
        q.push({0,S});
        while(!q.empty()){
            auto [d,u]=q.top(); q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push({dis[v],v});
                }
            }
        }
    }
}using namespace Dijkstra;

void init(){
    for(int i=0;i<=n+2;i++){
        adj[i].clear();
        G[i].clear();
    }
    S=n+1;
    T=n+2;
    ans=INF;
}

void builde(int bit,int flag){
    for(int i=1;i<=n+2;i++) adj[i]=G[i];
    for(int i=1;i<=K;i++){
        if(((a[i]>>bit)&1)^flag) adj[S].push_back({a[i],0});
        else adj[a[i]].push_back({T,0});
    }
}

void solve(){
    cin>>n>>m>>K;
    init();
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        if(u!=v){
            adj[u].push_back({v,w});
            G[u].push_back({v,w});
        }
    }
    for(int i=1;i<=K;i++) cin>>a[i];
    for(int bit=0;bit<17;bit++){
        builde(bit,0);
        dijk();
        ans=min(ans,dis[T]);
        builde(bit,1);
        dijk();
        ans=min(ans,dis[T]);
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
