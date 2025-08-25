#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3520;
int n,ans;
vector<int> adj[MN];

namespace Tree{
    int dep[MN],siz[MN],hson[MN],htop[MN],fa[MN];
    
    void dfs1(int u,int pre){
        siz[u]=1;
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(hson[u],ltop);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

    int dis(int x,int y){
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
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            for(int k=1;k<=n;k++){
                if(i==k||k==j) continue;
                ans+=(dis(i,j)==dis(j,k)&&dis(j,k)==dis(i,k));               
            }
        }
    }
    cerr<<dis(3,4)<<' '<<dis(4,2)<<' '<<dis(3,2)<<'\n';
    cerr<<lca(3,4);
    cout<<ans;

    return 0;
}