#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e4+15;
int n,m,dtot,match[MN],H[MN][MN],L[MN][MN],ans;
char mp[MN][MN];
vector<int> adj[MN];

namespace Hungry{
    int p[MN];
    bool vis[MN];

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
}using namespace Hungry;


int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j==1||mp[i][j-1]=='#') ++dtot;
            H[i][j]=dtot;
        }
    }
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            if(i==1||mp[i-1][j]=='#') ++dtot;
            L[i][j]=dtot;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='*'){
                adj[H[i][j]].push_back(L[i][j]);
            }
        }
    }
    for(int i=1;i<=dtot;i++){
        memset(vis,0,sizeof(vis));
        ans+=Hungry::match(i);
    }
    cout<<ans;
    return 0;
}