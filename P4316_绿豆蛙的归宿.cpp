#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v,w;
};
int dg[MN],in[MN],n,m;
double f[MN];
vector<Edge> adj[MN];

void topo(){
    queue<int> q;
    q.push(n);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto e:adj[u]){
            f[e.v]+=(double)(f[u]+e.w)/dg[e.v];
            in[e.v]--;
            if(!in[e.v]) q.push(e.v);
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        in[u]++;
        dg[u]++;
        adj[v].push_back({u,w});
    }
    topo();
    cout<<fixed<<setprecision(2)<<f[1];
    return 0;
}
