#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
struct Edge{
    int v,w;
};
int n,m,S,T;
vector<Edge> adj[MN];

namespace Dijkstra{
    int dis[MN];
    bool vis[MN];

    void dijk(int st){
        memset(dis,0x3f,sizeof(dis));
        priority_queue<pir,vector<pir>,greater<pir>> q;
        dis[st]=0;
        q.push(pir(0,st));       
        while(!q.empty()){
            int u=q.top().second;
            q.pop();
            if(vis[u]) continue;
            vis[u]=1;
            for(auto e:adj[u]){
                int v=e.v,w=e.w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    q.push(pir(dis[v],v));
                }
            }
        }
    }
}

int getpos(int i,int j,int k){
    return 2*(m-1)*(i-1)+2*(j-1)+k;
}

void add(int x,int y){
    int w;
    cin>>w;
    adj[x].push_back({y,w});
    adj[y].push_back({x,w});
}


signed main(){
    cin>>n>>m;
    T=2*(n-1)*(m-1)+1;
    for(int j=1;j<m;j++){
        add(getpos(1,j,2),T);
    }
    for(int i=2;i<n;i++){
        for(int j=1;j<m;j++){
            add(getpos(i-1,j,1),getpos(i,j,2));
        }
    }
    for(int j=1;j<m;j++){
        add(getpos(n-1,j,1),S);
    }
    for(int i=1;i<n;i++){
        add(getpos(i,1,1),S);
        for(int j=2;j<m;j++){
            add(getpos(i,j-1,2),getpos(i,j,1));
        }
        add(getpos(i,m-1,2),T);
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            add(getpos(i,j,1),getpos(i,j,2));
        }
    }
    Dijkstra::dijk(S);
    cout<<Dijkstra::dis[T];
    return 0;
}