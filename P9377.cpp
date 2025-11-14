#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15,INF=1e18,MK=18;
struct Edge{
    int v,w;
};
int K,n,m,s,a[MN];
vector<Edge> adj[MN];

namespace Dijkstra{
    struct Node{
        int u,i,j;
    };
    int dis[MN];
    bool vis[MN],visd[MN][MK][MK];

    void dijk(int st){
        priority_queue<pir,vector<pir>,greater<pir>> pq;
        fill(dis,dis+n,INF);
        dis[st]=0;
        pq.push(pir(0,st));
        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    pq.push(pir(dis[v],v));
                }
            }

            queue<Node> q;
            q.push({u,0,0});
            visd[u][0][0]=1;
            while(!q.empty()){
                auto [v,i,j]=q.front();
                q.pop();
                if(i==K&&dis[v]>dis[u]+a[j]){
                    dis[v]=dis[u]+a[j];
                    pq.push(pir(dis[v],v));
                } 
                if(i<K){
                    if(!visd[v][i+1][j]){
                        visd[v][i+1][j]=1;
                        q.push({v,i+1,j});
                    }
                    if(!visd[v^(1<<i)][i+1][j+1]){
                        visd[v^(1<<i)][i+1][j+1]=1;
                        q.push({v^(1<<i),i+1,j+1});
                    }
                }
            }
        }
    }
}using namespace Dijkstra;


signed main(){
    cin>>K>>m>>s;
    for(int i=1;i<=K;i++){
        cin>>a[i];
    }
    n=(1<<K);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dijk(s);
    for(int i=0;i<n;i++){
        cout<<dis[i]<<' ';
    }
    return 0;
}