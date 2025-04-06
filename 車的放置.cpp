#include<bits/stdc++.h>
using namespace std;
const int MN=1200;
int n,m,t;
int p[MN];
bool vis[MN],stop[MN][MN];
vector<int> adj[MN];

bool match(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||match(p[v])){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>m>>t;
    for(int i=1;i<=t;i++){
        int x,y;
        cin>>x>>y;
        stop[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(stop[i][j]) continue;
            adj[i].push_back(n+j);
            adj[n+j].push_back(i);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans+=match(i);
    }
    cout<<ans;
    return 0;
}