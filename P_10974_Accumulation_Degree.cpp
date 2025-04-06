#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct edge{
    int v,w;
};
int T,n,ans;
vector<edge> adj[MN];
int f[MN],dg[MN],d[MN];

void init(){
    ans=0;
    for(int i=1;i<=n;i++){
        f[i]=dg[i]=d[i]=0;
        adj[i].clear();
    }
}

void dfs1(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa) continue;
        dfs1(v,u);
        if(dg[v]>1){
            d[u]+=min(d[v],w);
        }else d[u]+=w;
    }
}

void dfs2(int u,int fa){
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==fa) continue;
        if(dg[u]==1){
            f[v]=d[v]+w;
        }else if(dg[v]==1){
            f[v]=d[v]+min(f[u]-w,w);
        }else{
            f[v]=d[v]+min(f[u]-min(d[v],w),w);
        }
        dfs2(v,u);
    }
}

int main(){
    cin>>T;
    while (T--)
    {
        cin>>n;
        init();
        for(int i=1;i<n;i++){
            int u,v,w;
            cin>>u>>v>>w;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
            dg[u]++;
            dg[v]++;
        }
        dfs1(1,0);
        f[1]=d[1];
        dfs2(1,0);
        
        for(int i=1;i<=n;i++){
            ans=max(ans,f[i]);
        }
        cout<<ans<<'\n';
    }
    
    return 0;
}