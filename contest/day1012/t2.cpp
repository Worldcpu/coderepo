#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15,ML=20;
struct Edge{
    int u,v,w;
}e[MN];
int n,m,q,etot;
int pre[MN];
vector<int> adj[MN];

void initpre(){
    for(int i=0;i<MN;i++) pre[i]=i;
}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

namespace EXKru{
    int dtot,val[MN];

    void build(){
        dtot=n;
        for(int i=1;i<=etot;i++){
            int ru=root(e[i].u),rv=root(e[i].v);
            if(ru==rv) continue;
            dtot++;
            val[dtot]=e[i].w;
            pre[ru]=pre[rv]=dtot;
            adj[dtot].push_back(ru);
            adj[dtot].push_back(rv);
            if(dtot==2*n-1) break;
        }
    }
}

namespace Tree{
    int fa[MN],siz[MN],dep[MN],hson[MN],htop[MN],dfn[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}using namespace Tree;

int main(){
    cin>>n>>m>>q;
    initpre();
    for(int i=m;i>=1;i--){
        for(int j=i+i;j<=n;j+=i){
            e[++etot]={i,j,i};
        }
    }   
    EXKru::build();
    dfs1(EXKru::dtot,0);
    dfs2(EXKru::dtot,EXKru::dtot);
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<m-EXKru::val[lca(x,y)]+1<<'\n';
    }

    return 0;
}