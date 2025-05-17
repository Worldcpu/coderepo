#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,q,MOD,h[MN],f[MN][45];
vector<int> adj[MN];

namespace TREE{
    int fa[MN];

    void dfs(int u,int pre){
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
        }
    }
}using namespace TREE;

signed main(){
    cin>>n>>MOD;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        cin>>h[i];
        for(int j=0;j<=40;j++){
            f[i][j]=1;
        }
    }
    cin>>q;
    while(q--){
        int op,x,d,w;
        cin>>op>>x;
        if(op==1){
            cin>>d>>w;
            while(x&&d>=0){
                if(fa[x]&&d>1) f[x][d]=f[x][d]*w%MOD,f[x][d-1]=f[x][d-1]*w%MOD;
                else for(int i=0;i<=d;i++){
                    f[x][i]=f[x][i]*w%MOD;
                }
                x=fa[x];
                d--;
            }
        }else{
            int ret=h[x];
            for(int i=0;x&&i<=40;i++){
                ret=ret*f[x][i]%MOD;
                x=fa[x];
            }
            cout<<ret<<'\n';
        }
    }
    return 0;
}
