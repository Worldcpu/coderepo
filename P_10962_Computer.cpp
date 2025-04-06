#include<bits/stdc++.h>
using namespace std;
const int MN=6;
struct edge
{
    int v,w;
};
vector<edge> adj[MN];
int n,f[MN][2],g[MN];

void dfs1(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa) continue;
        dfs1(v,u);
        if(f[u][0]<f[v][0]+w){
            f[u][1]=f[u][0];
            f[u][0]=f[v][0]+w;
        }else if(f[u][1]<f[v][0]+w){
            f[u][1]=f[v][0]+w;
        }
    }
}

void dfs2(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa) continue;
        if(f[v][0]+w<f[u][0]){
            g[v]=max(g[u],f[u][0])+w;
        }else g[v]=max(g[u],f[u][1])+w;
        dfs2(v,u);
    }
}

int main(){
    while (cin>>n)
    {
        for(int i=1;i<=n;i++){
            adj[i].clear();
            f[i][0]=f[i][1]=g[i]=0;
        }
        for(int i=2;i<=n;i++){
            int v,w;
            cin>>v>>w;
            adj[i].push_back({v,w});
            adj[v].push_back({i,w});
        }
        dfs1(1,0);
        dfs2(1,0);
        for(int i=1;i<=n;i++){
            cout<<max(g[i],f[i][0])<<'\n';
        }
    }
    
}
