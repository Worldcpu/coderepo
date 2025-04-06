#include<bits/stdc++.h>
using namespace std;
const int MN=32015;
int n,m,w[MN],val[MN],f[500][MN];
vector<int> adj[MN];
void dfs(int u,int bp,int fa){
    if(bp<=0) return;
    for(auto v:adj[u]){
        if(v==fa) continue;
        for(int i=n-w[v];i>=0;i--){
            f[v][i]=f[u][i]+val[v];
        }
        dfs(v,bp-w[v],u);
        for(int i=n;i>=w[v];i--){
            f[u][i]=max(f[u][i],f[v][i-w[v]]);
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u;
        cin>>w[i]>>val[i]>>u;
        val[i]*=w[i];
        adj[i].push_back(u);
        adj[u].push_back(i);
    }
    int ans=-1e9;
    dfs(0,n,-1);
    for(int i=1;i<=n;i++){
        ans=max(ans,f[0][i]);
    }
    cout<<ans;
    return 0;
}