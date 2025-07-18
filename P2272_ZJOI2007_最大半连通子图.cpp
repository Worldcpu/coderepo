#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+15;
int n,m,MOD,etot,f[MN],g[MN],in[MN];
pir e[MN];
vector<int> adj[MN],G[MN];

namespace Tarjan{
    int dfn[MN],low[MN],col[MN],cnt[MN],s[MN],top,ctot,dtot;
    bool vis[MN];

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        s[++top]=u;
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
            int p;
            ++ctot;
            do{
                p=s[top--];
                col[p]=ctot;
                cnt[ctot]++;
                vis[p]=0;
            }while(p!=u);
        }
    }

}using namespace Tarjan;

void toposort(){
    queue<int> q;
    for(int i=1;i<=ctot;i++){
        if(!in[i]){
            f[i]=cnt[i];
            g[i]=1;
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:G[u]){
            in[v]--;
            if(!in[v]) q.push(v);
            if(f[u]+cnt[v]==f[v]){
                (g[v]+=g[u])%=MOD;
            }else if(f[u]+cnt[v]>f[v]){
                f[v]=f[u]+cnt[v];
                g[v]=g[u];
            }
        }
    }
}

int main(){
    cin>>n>>m>>MOD;
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
                e[++etot]=pir(col[u],col[v]);
            }
        }
    }
    sort(e+1,e+1+etot);
    etot=unique(e+1,e+1+etot)-e-1;
    for(int i=1;i<=etot;i++){
        G[e[i].first].push_back(e[i].second);
        in[e[i].second]++;
    }
    toposort();
    int ans1=0,ans2=0;
    for(int i=1;i<=ctot;i++){
        if(f[i]>f[ans1]){
            ans1=i;
            ans2=g[i];
        }else if(f[i]==f[ans1]){
            (ans2+=g[i])%=MOD;
        }
    }
    cout<<f[ans1]<<'\n'<<ans2;
    return 0;
}
