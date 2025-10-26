#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e5+15,INF=1e18;
int n,m,K,d,disK[MN],disn[MN],ans=INF;
bool vis[MN];
vector<int> adj[MN];

namespace Dijkstra{
    int dis[MN];
    priority_queue<pir,vector<pir>,greater<pir>> q;

    int sum(int l,int r){
        return (l+r)*(r-l+1)/2;
    }

    int calc(int x){
        return x/d*sum(1,d)+sum(d+1-x%d,d);
    }

    void dijk(int st){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        dis[st]=0;
        q.push(pir(0,st));
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto v:adj[u]){
                if(disK[v]>=d){
                    ans=min(ans,dis[u]+calc(disn[v]+1));
                    continue;
                }
                if(dis[v]>dis[u]+d-disK[v]){
                    dis[v]=dis[u]+d-disK[v];
                    q.push(pir(dis[v],v));
                }
            }
        }
    }

}

void bfs(int st,int dis[]){
    queue<int> q;
    fill(dis+1,dis+1+n,INF);
    fill(vis+1,vis+1+n,0);
    q.push(st);
    dis[st]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[st]=1;
        for(auto v:adj[u]){
            if(vis[v]) continue;
            vis[v]=1;
            dis[v]=dis[u]+1;
            q.push(v);
        }
    }
}


signed main(){
    cin>>n>>m>>K>>d;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs(K,disK);
    bfs(n,disn);
    Dijkstra::dijk(1);
    cout<<min(Dijkstra::dis[n],ans);
    return 0;
}