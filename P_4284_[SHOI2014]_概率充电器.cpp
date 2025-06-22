#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v;
    double w;
};
int n;
double ans,f[MN];
vector<Edge> adj[MN];

void dfs1(int u,int pre){
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        dfs1(e.v,u);
        f[u]=f[u]+e.w*f[e.v]-e.w*f[e.v]*f[u];
    }
}

void dfs2(int u,int pre){
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        dfs2(e.v,u);
        if(f[e.v]*e.w!=1){
            double pa=e.w*(f[u]-f[e.v]*e.w)/(1-f[e.v]*e.w);
            f[e.v]=f[e.v]+pa-f[e.v]*pa;
        }
    }
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        double w;
        cin>>u>>v>>w;
        w/=100.0;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++){
        cin>>f[i];
        f[i]/=100.0;
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) ans+=f[i];
    cout<<fixed<<setprecision(6)<<ans;
    return 0;
}
