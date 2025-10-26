#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,INF=1e18;
int f[MN][MN],n,m,w[MN];
vector<int> adj[MN];


signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            f[i][j]=INF;
        }
    }
    for(int j=0;j<=n;j++){
        f[1][j]=j*w[1];
    }
    for(int j=n-1;j>=0;j--){
        for(int i=1;i<=n;i++){
            for(auto v:adj[i]){
                f[i][j]=min(f[i][j],f[v][j+1]+j*w[i]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<f[i][0]<<'\n';
    }

    return 0;
}