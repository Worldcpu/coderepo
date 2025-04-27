#include<bits/stdc++.h>
using namespace std;
constexpr int MN=520;
int p[MN],n,m;
bool mp[MN][MN],vis[MN];

bool dfs(int u){
    for(int i=1;i<=n;i++){
        if(mp[u][i]&&!vis[i]&&i!=u){
            vis[i]=1;
            if(!p[i]||dfs(p[i])){
                p[i]=u;
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        mp[i][i]=1;
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mp[u][v]=1;
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                mp[i][j]|=(mp[i][k]&&mp[k][j]);
            }
        }
    }
    int ans=n;
    for(int i=1;i<=n;i++){
        memset(vis,0,sizeof(vis));
        ans-=dfs(i);
    }
    cout<<ans;
    return 0;
}