#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520+15;
int n,mp[MN][MN],ans;
vector<int> adj[MN];

namespace Hungry{
    int p[MN];
    bool vis[MN];

    bool dfs(int u){
        if(vis[u]) return 0;
        vis[u]=1;
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
}using namespace Hungry;

void init(){
    ans=0;
    for(int i=0;i<=2*n;i++){
        adj[i].clear();
        p[i]=0;
    }
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>mp[i][j];
        }
    }   
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(mp[i][j]==1){
                adj[i].push_back(j+n);
                adj[j+n].push_back(i);
            }
        }
    }
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    if(ans==n){
        cout<<"Yes\n";
    }else cout<<"No\n";
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}