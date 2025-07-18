#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15,INF=1e9;
int T,n,ans,a[MN],f[MN][3],g[MN][3];
vector<int> adj[MN];

void dfs(int u,int pre){
    int col=a[u];
    if(col){
        f[u][col^3]=g[u][col^3]=INF;
        f[u][col]=0,g[u][col]=-INF; 
    }
    else f[u][1]=f[u][2]=0,g[u][1]=g[u][2]=-INF;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs(v,u);
        for(int j=1;j<=2;j++){
            if(col+j==3) continue;
            int retf=INF,retg=INF;
            for(int k=1;k<=2;k++){
                if(f[v][k]==INF) continue;
                retf=min(retf,f[v][k]+(j!=k));
                retg=min(retg,f[u][j]+f[v][k]+(j!=k));
            }
            f[u][j]=max(f[u][j],retf);
            g[u][j]=max(g[u][j],retg);
        }
    }
    ans=max(ans,min(g[u][1],g[u][2]));
}

void clear(){
    ans=0;
    for(int i=1;i<=n;i++) adj[i].clear();
}

void solve(){
    cin>>n;
    clear();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    cout<<(ans+1)/2+1<<'\n';
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
