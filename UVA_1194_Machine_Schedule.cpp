#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1500;
int n,m,K,p[MN];
vector<int> adj[MN];
bool vis[MN];

bool dfs(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||dfs(p[v])){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

bool solve(){
    memset(p,0,sizeof(p));
    cin>>n;
    if(n==0) return 0;    
    cin>>m>>K;
    for(int i=1;i<=n+m;i++) adj[i].clear();
    for(int i=1;i<=K;i++){
        int x,y,z;
        cin>>z>>x>>y;
        if(!x&&!y) continue;
        adj[x].push_back(n+y);
        adj[n+y].push_back(x);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    cout<<ans<<'\n';
    return 1;
}

int main(){
    while (1)
    {
        if(!solve()) break;
    }
    return 0;
}