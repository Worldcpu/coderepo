#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,dep[MN];
vector<int> adj[MN];

void dfs(int u,int pre){
    dep[u]=dep[pre]+1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    double ans=0;
    for(int i=1;i<=n;i++){
        ans+=1/(double)dep[i];
    }
    cout<<fixed<<setprecision(12)<<ans;
    return 0;
}
