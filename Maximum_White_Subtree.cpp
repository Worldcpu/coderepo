#include<iostream>
#include<vector>
using namespace std;
const int MN=2e5+15;
int n,f[MN],c[MN],ans[MN];
vector<int> adj[MN];
void dfs1(int u,int fa){
    f[u]=c[u] ? 1 : -1;
    for(auto v:adj[u]){
        if(fa==v) continue;
        dfs1(v,u);
        f[u]+=max(f[v],0);
    }
}
void dfs2(int u,int fa){
    for(auto v:adj[u]){
        if(fa==v) continue;
        int fu=f[u],fv=f[v];
        if(fv>0){
            fu-=fv;
        }
        if(fu>0){
            fv+=fu;
        }
        f[v]=ans[v]=fv;
        dfs2(v,u);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    ans[1]=f[1];
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}