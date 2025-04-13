#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e4+15;
struct edge{
    int v,w;
};
vector<edge> adj[MN];
int n,p,K,dis[MN];
bool vis[MN];

void dij(){
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    priority_queue<pir,vector<pir>,greater<pir>> q;
    q.push(pir(0,1));
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            dis[e.v]=min(dis[e.v],max(dis[u],e.w));
            if(!vis[e.v]){
                q.push({dis[e.v],e.v});
            }
        }
    }

}

int main(){
    cin>>n>>p>>K;
    if(K>=p){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=p;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        for(int j=1;j<=K;j++){
            adj[u+(j-1)*n].push_back({v+j*n,0});
            adj[v+(j-1)*n].push_back({u+j*n,0});
            adj[u+j*n].push_back({v+j*n,w});
            adj[v+j*n].push_back({u+j*n,w});
        }
    }
    for(int i=1;i<=K;i++){
        adj[n+(i-1)*n].push_back({n+i*n,0});
    }
    dij();
    if(dis[n+K*n]>=1061109567) cout<<-1;
    else cout<<dis[n+K*n];
    return 0;
}