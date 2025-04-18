#include<bits/stdc++.h>
#define pir pair<int,int>
#define py(x) (x+MN)
using namespace std;
constexpr int MN=3e5+15,MK=1e6+15;
struct Node{
    int id,to,cnt;
};
int n,m,w[MN],hson[MN],fa[MN],top[MN],dep[MN],siz[MN],c[2][MK],ans[MN];
vector<int> adj[MN];
vector<Node> id[MN];

void dfs1(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[u]=pre;
    siz[u]=1;
    int mxp=-1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>mxp){
            hson[u]=v;
            mxp=siz[v];
        }
    }
}

void dfs2(int u,int ltop){
    top[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto v:adj[u]){
        if(v==fa[u]||v==hson[u]) continue;
        dfs2(v,v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

void getans(int u,int pre){
    int c1=c[0][w[u]+dep[u]],c2=c[1][py(w[u]-dep[u])];
    for(auto p:id[u]){
        c[p.id][p.to]+=p.cnt;
    }
    for(auto v:adj[u]){
        if(v==pre) continue;
        getans(v,u);
    }
    ans[u]=c[0][w[u]+dep[u]]-c1+c[1][py(w[u]-dep[u])]-c2;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int lcuv=lca(u,v);
        id[u].push_back({0,dep[u],1});
        id[v].push_back({1,py(dep[u]-2*dep[lcuv]),1});
        id[lcuv].push_back({1,py(dep[u]-2*dep[lcuv]),-1});
        id[fa[lcuv]].push_back({0,dep[u],-1});
    }
    
    getans(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}