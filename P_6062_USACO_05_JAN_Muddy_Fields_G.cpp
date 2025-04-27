#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6,MP=1200;
int n,m,p[MN<<2],h[MP][MP],s[MP][MP],sumh=1,sums=1;
bool vis[MN];
char mp[MP][MP];
vector<int> adj[MN];

bool dfs(int u){
    for(auto v:adj[u]){
        if(!vis[v]){
            vis[v]=1;
            if(!p[v]||dfs(v)){
                p[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='*'){
                h[i][j]=(mp[i-1][j]=='*'?h[i-1][j]:sumh++);
                s[i][j]=(mp[i][j-1]=='*'?s[i][j-1]:sums++);
                adj[h[i][j]].push_back(s[i][j]);
            }
        }
    }
    int ans=0;
    for(int i=1;i<sumh;i++){
        memset(vis,0,sizeof(vis));
        ans+=dfs(i);
    }
    cout<<ans;
    return 0;
}