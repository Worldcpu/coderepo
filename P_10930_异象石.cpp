#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e5+15;
struct Edge{
    int v,w;
};
int n,m,ans,top[MN],fa[MN],hson[MN],depp[MN],dep[MN],siz[MN],dfn[MN],tot;
vector<Edge> adj[MN];
set<pir> s;

void dfs1(int u,int pre){
    fa[u]=pre;
    siz[u]=1;
    depp[u]=depp[pre]+1;
    dfn[u]=++tot;
    int mxp=-1;
    for(auto e:adj[u]){
        if(e.v==pre) continue;
        dep[e.v]=dep[u]+e.w;
        dfs1(e.v,u);
        
        siz[u]+=siz[e.v];
        if(mxp<siz[e.v]){
            mxp=siz[e.v];
            hson[u]=e.v;
        }
    }
}

void dfs2(int u,int ltop){
    top[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto e:adj[u]){
        if(e.v==fa[u]||e.v==hson[u]) continue;
        dfs2(e.v,e.v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(depp[top[x]]<depp[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return depp[x]<depp[y]?x:y;
}

int path(int x,int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0);
    dfs2(1,0);
    cin>>m;
    while(m--){
        char op;
        int x,l,r;
        cin>>op;
        if(op=='?') cout<<ans/2<<'\n';
        else if(op=='+'){
            cin>>x;
            s.insert(pir(dfn[x],x));
            auto it1=s.lower_bound(pir(dfn[x],x)),it2=s.upper_bound(pir(dfn[x],x));
            if(it1==s.begin()){
                l=(*--s.end()).second;
            }else l=(*--it1).second;
            if(it2==s.end()) r=(*s.begin()).second;
            else r=(*it2).second;
            ans-=path(l,r);
            ans+=path(l,x)+path(x,r);
        }
        else if(op=='-'){
            cin>>x;
            auto it1=s.lower_bound(pir(dfn[x],x)),it2=s.upper_bound(pir(dfn[x],x));
            if(it1==s.begin()){
                l=(*--s.end()).second;
            }else l=(*--it1).second;
            if(it2==s.end()) r=(*s.begin()).second;
            else r=(*it2).second;
            s.erase(pir(dfn[x],x));
            ans+=path(l,r);
            ans-=path(l,x)+path(x,r);
        }
    }
    return 0;
}