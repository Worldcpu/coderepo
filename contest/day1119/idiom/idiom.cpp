#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,m,c[MN],p[MN],q;
vector<int> adj[MN];

namespace Tree{
    int dfn[MN],tot,fa[MN],dep[MN],f[MN],lst[MN];
    int vis[MN];
    vector<int> cyc;
    set<int> st[MN];

    void dfs(int u){
        for(;!vis[u];u=fa[u]) vis[u]=1;
        for(;vis[u]==1;u=fa[u]) vis[u]=2,cyc.push_back(u);
    }

    void dfs2(int u){
        f[u]=min(f[fa[u]]+1,dep[u]-lst[c[u]]+1);
        int tmp=lst[c[u]];
        lst[c[u]]=dep[u];
        for(auto v:adj[u]){
            if(vis[v]==2) continue;
            dep[v]=dep[u]+1;
            dfs2(v);
        }
        lst[c[u]]=tmp;
    }
}using namespace Tree;

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>fa[i];
        adj[fa[i]].push_back(i);
    }    
    dfs(1);
    for(int i=0,qwq=cyc.size();i<qwq;i++){
        cyc.push_back(cyc[i]);
    }
    reverse(cyc.begin(),cyc.end());
    for(auto p:cyc){
        dep[p]=dep[fa[p]]+1;
        dfs2(p);
        lst[c[p]]=dep[p];
    }
    cin>>q;
    while(q--){
        int x;
        cin>>x;
        cout<<f[x]<<'\n';
    }
    
    return 0;
}