#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,V=36501;
int bel[MN],siz[MN],vtot,n,m,in[MN],f[MN],ed;
bool vis[MN],ban[MN];
vector<int> adj[MN],G[MN],ans;

namespace Tarjan{
    int dfn[MN],low[MN],dtot,st[MN],top;
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
            }while(p!=u);
        }
    }

    void solve(){
        for(int i=1;i<=n+1;i++){
            if(!dfn[i]) tarjan(i);
        }
    }
}

void tp1(){
    queue<int> q;
    for(int i=1;i<=vtot;i++){
        if(i==ed) continue;
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=1;
        for(auto v:G[u]){
            if(!--in[v]&&v!=ed) q.push(v);
        }
    }
}

void tp2(){
    queue<int> q;
    q.push(ed);
    f[ed]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=1;
        for(auto v:G[u]){
            if(ban[v]) continue;
            f[v]=min(V,f[v]+f[u]);
            if(!--in[v]) q.push(v);
        }
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
    }
    Tarjan::solve();
    for(int u=1;u<=n+1;u++){
        for(auto v:adj[u]){
            if(bel[u]!=bel[v]){
                G[bel[v]].push_back(bel[u]);
                in[bel[u]]++;
            }else if(u==v){
                ban[bel[u]]=1;
            }
        }
    }
    ed=bel[n+1];
    tp1();
    if(!ban[ed]){
        tp2();
    }
    for(int i=1;i<=n;i++){
        if(!vis[bel[i]]||f[bel[i]]==V){
            ans.push_back(i);
        }
    }
    if(!ans.empty()){
        cout<<"zawsze\n";
    }else{
        int ret=0;
        for(int i=1;i<=n;i++){
            if(f[bel[i]]>ret){
                ret=f[bel[i]];
                ans.clear();
            }
            if(f[bel[i]]==ret) ans.push_back(i);
        }
        cout<<ret<<'\n';
    }
    cout<<ans.size()<<'\n';
    for(auto p:ans) cout<<p<<'\n';
    return 0;
}