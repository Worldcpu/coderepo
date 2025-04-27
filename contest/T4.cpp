#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=520;
struct Edge{
    int v,w;
};
int n,m,p[MN];
bool vis[MN];
pir dis[MN];
vector<Edge> adj[MN];

void dij(int s){
    for(int i=1;i<=n;i++){
        dis[i].first=1e9;
        dis[i].second=p[i];
        vis[i]=0;
    }
    priority_queue<pir,vector<pir>,greater<pir>> q;
    dis[s].first=0;
    dis[s].second=p[s];
    q.push({p[1],s});
    while(!q.empty()){
        pir f=q.top();
        q.pop();
        int u=f.second;
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[f.second]){
            if(dis[e.v].first+dis[e.v].second>dis[u].first+e.w+max(dis[u].second,p[e.v])){
                dis[e.v].first=dis[u].first+e.w;
                dis[e.v].second=max(dis[u].second,p[e.v]);
                q.push({dis[e.v].first+dis[e.v].second,e.v});
            }
        }
    }
}

int main(){
    int q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    while(q--){
        int u,v;
        cin>>u>>v;
        dij(u);
        cout<<dis[v].first+dis[v].second<<'\n';
    }
    return 0;
}