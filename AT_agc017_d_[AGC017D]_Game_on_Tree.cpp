#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int f[MN],n;
vector<int> adj[MN];

void dfs(int u,int pre){
    f[u]=0;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        f[u]^=f[v]+1;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<(f[1]?"Alice":"Bob");
    return 0;
}
