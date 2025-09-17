#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;;
struct Edge{
    int v,w;
};
int n,m,b,a[MN],mxc;
vector<Edge> adj[MN];


namespace Dijkstra{
    int dis[MN];
    bool vis[MN];

    void init(){
        for(int i=1;i<=n;i++){
            dis[i]=INF;
            vis[i]=0;
        }
    }

    void dijkstra(int st,int mid){
        priority_queue<pir,vector<pir>,greater<pir>> q;
        init();
        q.push(pir(0,st));
        dis[st]=0;
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+e.w&&a[v]<=mid){
                    dis[v]=dis[u]+e.w;
                    q.push(pir(dis[v],v));
                }
            }
        }
    }

}using namespace Dijkstra;

bool check(int k){
    dijkstra(1,k);
    return dis[n]<=b;
}

int main(){
    cin>>n>>m>>b;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mxc=max(mxc,a[i]);
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int l=0,r=mxc,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;

    return 0;
}