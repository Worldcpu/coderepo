#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15;
struct Edge{
    int v,w;
};
int n,m,K,tot,top,minv[MN],h[MN],dep[MN],fa[MN],s[MN],hson[MN],htop[MN],siz[MN],dfn[MN];
vector<Edge> adj[MN];
vector<int> g[MN];

void dfs1(int u,int pre){
    fa[u]=pre;
    siz[u]=1;
    dfn[u]=++tot;
    dep[u]=dep[pre]+1;
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        minv[e.v]=min(minv[u],e.w);
        dfs1(e.v,u);
        siz[u]+=siz[e.v];
        if(siz[hson[u]]<siz[e.v]) hson[u]=e.v;
    }
}

void dfs2(int u,int ltop){
    htop[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto e:adj[u]){
        if(e.v==fa[u]||e.v==hson[u]) continue;
        dfs2(e.v,e.v);
    }
}

int lca(int x,int y){
    while(htop[x]!=htop[y]){
        if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
        x=fa[htop[x]];
    }
    return dep[x]<dep[y]?x:y;
}

bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}

int getvtree(){
    sort(h+1,h+1+K,cmp);
    s[top=1]=1;
    if(h[1]!=1){
        s[++top]=h[1];
    }
    for(int i=2;i<=K;i++){
        int qlca=lca(s[top],h[i]);
        if(qlca==s[top]) continue;
        while(1){
            if(dep[qlca]>=dep[s[top-1]]){
                if(qlca!=s[top]){
                    g[qlca].push_back(s[top]);
                    if(qlca!=s[top-1]) s[top]=qlca;
                    else top--;
                }
                break;
            }
            else{
                g[s[top-1]].push_back(s[top]);
                top--;
            }
        }
        s[++top]=h[i];
    }
    while(top>1){
        g[s[top-1]].push_back(s[top]);
        top--;
    }
    return 1;
}

int dp(int u){
    //cerr<<"Node:"<<u<<" minv:"<<minv[u]<<'\n';
    if(g[u].empty()) {
        //cerr<<"EMPTY!\n";
        return minv[u];
    }
    int tmp=0;
    for(auto v:g[u]){
        tmp+=dp(v);
    }
    g[u].clear();
    return min(minv[u],tmp);
}

signed main(){
    minv[1]=0x3f3f3f3f;
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0);
    dfs2(1,1);
    cin>>m;
    while(m--){
        //cerr<<"BEGIN\n";
        top=0;
        cin>>K;
        for(int i=1;i<=K;i++){
            cin>>h[i];
        }
        cout<<dp(getvtree())<<'\n';    
        //cerr<<"END\n";
    }
    return 0;
}
