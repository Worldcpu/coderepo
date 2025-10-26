#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,INF=1e9;
struct Edge{
    int v,w;
};
int n,a[MN],res,ans1,ans2;
vector<Edge> adj[MN];

void dfs(int u,int pre,int tot){
    res+=tot;
    for(auto e:adj[u]){
        int v=e.v,w=e.w;
        if(v==pre) continue;
        dfs(v,u,tot+w-a[u]);
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    ans1=INF,ans2=0;
    for(int i=1;i<=n;i++){
        res=0;
        dfs(i,0,0);
        if(ans1>res){
            ans1=res;
            ans2=i;
        }
    }
    cout<<ans2<<'\n'<<ans1<<'\n';
    return 0;
}