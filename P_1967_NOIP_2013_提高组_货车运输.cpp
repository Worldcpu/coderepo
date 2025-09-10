#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{
    int u,v,w;
}e[MN];
int n,m,dtot,pre[MN],val[MN],q;
bool vis[MN];
vector<int> adj[MN];

namespace Tree{
    int siz[MN],hson[MN],htop[MN],dep[MN],fa[MN];

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }

    void dfs1(int u,int pre){
        siz[u]=1;
        fa[u]=pre;
        dep[u]=dep[pre]+1;
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
            dfs2(v,v);
        }
    }

    int lca(int x,int y){
        if(root(x)!=root(y)) return -1;
        while(htop[x]!=htop[y]){
            if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
            x=fa[htop[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}

int root(int x){
    if(pre[x]==x) return pre[x];
    else return pre[x]=root(pre[x]);
}

bool cmp(Edge x,Edge y){
    return x.w>y.w;
}

void buildkru(){
    dtot=n;
    for(int i=1;i<=m;i++){
        int ru=root(e[i].u),rv=root(e[i].v);
        if(ru!=rv){
            dtot++;
            pre[ru]=pre[rv]=dtot;
            adj[dtot].push_back(ru);
            adj[dtot].push_back(rv);
            val[dtot]=e[i].w;
        }
    }
    for(int i=1;i<=dtot;i++){
        int rx=root(i);
        if(!vis[rx]){
            Tree::dfs1(rx,0);
            Tree::dfs2(rx,rx);
            vis[rx]=1;
        }
    }
}

void initpre(){
    for(int i=0;i<MN;i++){
        pre[i]=i;
    }
}


int main(){
    initpre();
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>e[i].u>>e[i].v>>e[i].w;
    }
    sort(e+1,e+1+m,cmp);
    buildkru();
    cin>>q;
    while(q--){
        int x,y;
        cin>>x>>y;
        int lcaa=Tree::lca(x,y);
        if(lcaa==-1){
            cout<<-1<<'\n';
            continue;
        }
        cout<<val[lcaa]<<'\n';
    }   

    return 0;
}