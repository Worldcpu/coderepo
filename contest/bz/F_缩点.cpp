#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,m,a[MN],ans;
vector<int> adj[MN],G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],dtot,st[MN],top,col[MN],vtot;
    int val[MN];
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        st[++top]=u;
        vis[u]=1;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            }else if(vis[v]){
                low[u]=min(low[u],dfn[v]);
            }
        }
        if(low[u]==dfn[u]){
            vtot++;
            int p;
            do{
                p=st[top--];
                vis[p]=0;
                col[p]=vtot;
                val[vtot]+=a[p];
            }while(p!=u);
        }
    }
}using namespace Tarjan;

namespace Toposort{
    int in[MN],f[MN];

    void toposort(){
        queue<int> q;
        fill(f+1,f+1+vtot,0);
        for(int i=1;i<=vtot;i++){
            if(!in[i]){
                q.push(i);
                f[i]=val[i];
            }
        }
        while(!q.empty()){
            auto u=q.front();
            q.pop();
            for(auto v:adj[u]){
                f[v]=max(f[v],f[u]+val[v]);
                if(!--in[v]) q.push(v);
            }
        }
    }

}using namespace Toposort;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }

    for(int u=1;u<=n;u++){
        for(auto v:adj[u]){
            if(col[u]!=col[v]){
                G[col[u]].push_back(col[v]);
                in[col[v]]++;
            }
        }
    }
    toposort();
    for(int i=1;i<=vtot;i++){
        ans=max(ans,f[i]);
    }
    cout<<ans<<'\n';

    return 0;
}