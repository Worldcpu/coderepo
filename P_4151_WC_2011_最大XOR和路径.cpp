#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MP=65;
struct Edge{
    int v,w;
};
int n,m,ans,dis[MN];
bool vis[MN];
vector<Edge> adj[MN];

struct xxj{
    int p[MP];
    
    void insert(int x){
        for(int i=63;i>=0;i--){
            if((x>>i)&1){
                if(!p[i]){
                    p[i]=x;
                    break;
                }
                x^=p[i];
            }
        }
    }

    int getmx(int x){
        int ans=x;
        for(int i=63;i>=0;i--){
            if((ans^p[i])>ans) ans^=p[i];
        }
        return ans;
    }

}xj;

void dfs(int u,int fa){
    vis[u]=1;
    for(auto e:adj[u]){
        if(vis[e.v]) xj.insert(dis[e.v]^e.w^dis[u]);
        else dis[e.v]=dis[u]^e.w,dfs(e.v,u);
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
    dfs(1,0);
    cout<<xj.getmx(dis[n]);
    return 0;
}
