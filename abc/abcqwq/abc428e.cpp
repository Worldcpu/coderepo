#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,rt1,rt2,mxdep;
vector<int> adj[MN];

namespace Tree{
    int dep[MN];
    
    void dfs(int u,int pre){
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs(v,u);
        }
    }


}using namespace Tree;

namespace TreeLCA{
    constexpr int ML=30;
int hson[MN],dep[MN],top[MN],fa[MN],siz[MN];
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
        if(v==fa[u]||v==hson[u]){
            continue;
        }
        dfs2(v,v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            swap(x,y);
        }
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

    int getdis(int x,int y){
        return dep[x]+dep[y]-2*dep[lca(x,y)];
    }

}using namespace Tree;


int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>mxdep){
            mxdep=dep[i];
            rt1=i;
        }
    }   
    dfs(rt1,0);
    mxdep=0;
    for(int i=1;i<=n;i++){
        if(dep[i]>=mxdep){
            mxdep=dep[i];
            rt2=i;
        }
    }   

    dfs(rt2,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>=mxdep){
            mxdep=dep[i];
            rt1=i;
        }
    }   
    dfs(rt1,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>=mxdep){
            mxdep=dep[i];
            rt2=i;
        }
    }   
    if(rt1<rt2) swap(rt1,rt2);
    TreeLCA::dfs1(rt1,0);
    TreeLCA::dfs2(rt1,rt1);
    for(int i=1;i<=n;i++){
        int dis1=TreeLCA::getdis(i,rt1);
        int dis2=TreeLCA::getdis(i,rt2);
        if(dis1>=dis2){
            cout<<rt1<<'\n';
        }else cout<<rt2<<'\n';
    }

    return 0;
}