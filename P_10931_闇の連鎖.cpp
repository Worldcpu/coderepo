#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15;
int n,m,dep[MN],ans,top[MN],hson[MN],fa[MN],siz[MN],c[MN];
vector<int> adj[MN];

void dfs1(int u,int pre){
    siz[u]=1;
    fa[u]=pre;
    dep[u]=dep[pre]+1;
    int maxp=-1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(maxp<siz[v]){
            hson[u]=v;
            maxp=siz[v];
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

void getans(int u,int fa){
    for(auto v:adj[u]){
        if(v==fa) continue;
        getans(v,u);
        c[u]+=c[v];
    }
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
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        int u,v,lcuv;
        cin>>u>>v;
        lcuv=lca(u,v);
        //cout<<lcuv<<'\n';
        c[u]++;
        c[v]++;
        c[lcuv]-=2;
    }
    getans(1,0);
    for(int i=2;i<=n;i++){
        ans+=(c[i]==0?m:(c[i]==1));
    }
    cout<<ans;
    return 0;
}