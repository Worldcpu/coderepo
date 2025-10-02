#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int f[MN][MN],n,m,w[MN],v[MN],bw[MN],bv[MN],in[MN];
vector<int> adj[MN];
vector<int> G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot,bel[MN],vtot,st[MN],top;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]) low[u]=min(low[u],dfn[v]);
        }
        if(low[u]==dfn[u]){
            vtot++;
            int p;
            do{
                p=st[top--];
                bel[p]=vtot;
                vis[p]=0;
                bw[vtot]+=w[p];
                bv[vtot]+=v[p];
            }while(p!=u);
        }
    }

}using namespace Tarjan;

void dfs(int u){
    for(int i=bw[u];i<=m;i++){
        f[u][i]=bv[u];
    }
    for(auto v:G[u]){
        dfs(v);
        for(int i=m;i>=bw[u];i--){
            for(int j=0;j<=i-bw[u];j++){
                f[u][i]=max(f[u][i],f[u][i-j]+f[v][j]);
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=n;i++){
        cin>>v[i];
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(!x) continue;
        adj[x].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
    for(int u=1;u<=n;u++){
        for(auto v:adj[u]){
            if(bel[u]!=bel[v]){
                G[bel[u]].push_back(bel[v]);
                in[bel[v]]++;
                cerr<<bel[u]<<' '<<bel[v]<<'\n';
            }
        }
    }
    cerr<<"-----------------\n";
    memset(f,128,sizeof(f));
    for(int i=1;i<=vtot;i++){
        if(!in[i]) G[0].push_back(i);
        cerr<<w[i]<<' '<<v[i]<<'\n';
    }
    dfs(0);
    cout<<f[0][m];
    return 0;
}