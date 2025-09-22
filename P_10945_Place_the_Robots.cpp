#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e4+15;
int n,m,dtot,H[MN][MN],L[MN][MN],ans,tcnt;
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

void init(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            mp[i][j]=0;
            H[i][j]=0;
            L[i][j]=0;
        }
    }
    for(int i=1;i<=dtot;i++){
        adj[i].clear();
        p[i]=0;
        
    }
    dtot=ans=0;
}

void solve(){
    cin>>n>>m;
    init();
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
            if(mp[i][j]=='o'){
                adj[H[i][j]].push_back(L[i][j]);
            }
        }
    }
    for(int i=1;i<=dtot;i++){
        memset(vis,0,sizeof(vis));
        ans+=match(i);
    }
    cout<<"Case :"<<tcnt<<'\n'<<ans<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        tcnt++;
        solve();
    }
}