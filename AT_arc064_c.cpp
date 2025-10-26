#include<bits/stdc++.h>
#define pir pair<double,int>
using namespace std;
constexpr int MN=5e5+15;
constexpr double eps=1e-12,INF=1e18;
struct EDGE{
    int v;
    double w;
};
struct Node{
    int x,y,r;
}a[MN];
int n,m,xs,ys,xt,yt;
vector<EDGE> adj[MN];

namespace Dijkstra{
    double dis[MN];
    bool vis[MN];
    priority_queue<pir,vector<pir>,greater<pir>> q;

    void dijk(int st){
        fill(dis+1,dis+1+n+2,INF);
        fill(vis+1,vis+1+n+2,0);
        q.push(pir(0,st));
        dis[st]=0;
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v;
                if(dis[v]>dis[u]+e.w){
                    dis[v]=dis[u]+e.w;
                    q.push(pir(dis[v],v));
                }
            }
        }
        
    }
}

double dis(int x,int y){
    return sqrt(1ll*(a[x].x-a[y].x)*(a[x].x-a[y].x)+1ll*(a[x].y-a[y].y)*(a[x].y-a[y].y));
}

signed main(){
    cin>>xs>>ys>>xt>>yt>>n;
    a[n+1]={xs,ys,0};
    a[n+2]={xt,yt,0};
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y>>a[i].r;
    }
    for(int i=1;i<=n+2;i++){
        for(int j=i+1;j<=n+2;j++){
            auto w=max(dis(i,j)-a[i].r-a[j].r,(double)0.0);
            adj[i].push_back({j,w});
            adj[j].push_back({i,w});
        }
    }
    for(int i=1;i<=n;i++){
        auto w=max(dis(n+1,i)-a[i].r,(double)0.0);
        adj[n+1].push_back({i,w});
        adj[i].push_back({n+1,w});
    }
    for(int i=1;i<=n;i++){
        auto w=max(dis(n+2,i)-a[i].r,(double)0.0);
        adj[n+2].push_back({i,w});
        adj[i].push_back({n+2,w});
    }
    Dijkstra::dijk(n+1);
    cout<<fixed<<setprecision(10)<<Dijkstra::dis[n+2];

    return 0;
}