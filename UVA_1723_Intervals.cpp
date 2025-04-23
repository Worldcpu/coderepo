#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e4+15,INF=1e9;
struct Edge{
    int v,w;
};
int n,T,dis[MN];
vector<Edge> adj[MN];
bool vis[MN];

void init(){
    for(int i=1;i<=n;i++){
        adj[i].clear();
        dis[i]=-INF;
        vis[i]=0;
    }
}

void spfa(){
    queue<int> q;
    q.push(0);
    vis[0]=1;
    dis[0]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(auto e:adj[u]){
            if(dis[e.v]<dis[u]+e.w){
                dis[e.v]=dis[u]+e.w;
                if(!vis[e.v]){
                    q.push(e.v);
                    vis[e.v]=1;
                }
            }
        }
    }
}

void solve(){
    int maxp=-1;
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b+1,c});
        maxp=max(maxp,b+1);
    }
    for(int i=1;i<=maxp;i++){
        adj[i-1].push_back({i,0});
        adj[i].push_back({i-1,-1});
    }
    spfa();
    cout<<dis[maxp]<<'\n';
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}