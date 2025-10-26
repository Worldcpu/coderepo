#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int u,v,c;
}e[MN];
struct EDGE{
    int v,w;
};
int n,m,dtot;
vector<EDGE> adj[MN];
map<pir,int> mp;

namespace Dijkstra{
    int dis[MN];
    bool vis[MN];
    priority_queue<pir,vector<pir>,greater<pir>> q;

    void dijk(int st){
        memset(dis,0x3f,sizeof(dis));
        memset(vis,0,sizeof(vis));
        q.push(pir(0,st));
        dis[st]=0;
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+e.w){
                    dis[v]=dis[u]+e.w;
                    q.push(pir(dis[v],v));
                }
            }
        }
        
    }
}

int find(int x,int id){
    if(mp[pir(x,id)]) return mp[pir(x,id)];
    else return mp[pir(x,id)]=++dtot; 
}

signed main(){
    cin>>n>>m;
    dtot=n;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].c;   
        int cu=find(e[i].u,e[i].c),cv=find(e[i].v,e[i].c);
        adj[cu].push_back({cv,0});
        adj[cv].push_back({cu,0});
        adj[e[i].u].push_back({cu,1});
        adj[cu].push_back({e[i].u,1});
        adj[e[i].v].push_back({cv,1});
        adj[cv].push_back({e[i].v,1});
    }
    Dijkstra::dijk(1);
    if(Dijkstra::dis[n]>=INF){
        cout<<-1;
    }
    else cout<<Dijkstra::dis[n]/2;

    return 0;
}