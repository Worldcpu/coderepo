#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1250;
const unsigned int MOD=(unsigned)(1<<31)-1;
struct Edge{
    int v,w;
};
int n,m,dis[MN],ans[MN];
vector<Edge> adj[MN];
bool vis[MN];

void dij(){
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;i++) ans[i]=1;
    priority_queue<pir,vector<pir>,greater<pir>> q;
    q.push({0,1});
    ans[1]=1;
    while(!q.empty()){
        int u=q.top().second,d=q.top().first;
        q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(auto e:adj[u]){
            if(dis[e.v]>d+e.w){
                ans[e.v]=1;
                dis[e.v]=d+e.w;
                q.push(pir(dis[e.v],e.v));
            }else if(dis[e.v]==d+e.w){
                ans[e.v]++;
            }
        }
    }
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dij();
    int ret=1;
    for(int i=2;i<=n;i++){
        //cout<<ans[i]<<" ";
        ret=(ret*ans[i])%MOD;
    }
    cout<<ret;
    return 0;
}