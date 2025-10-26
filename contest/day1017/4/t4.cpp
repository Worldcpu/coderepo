#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int n,m,a[MN],b[MN],qlca[MN],ans;
vector<int> adj[MN];

namespace DSU{
    int pre[MN];

    void initpre(){
        for(int i=1;i<MN;i++){
            pre[i]=i;
        }
    }

    int root(int x){
        if(pre[x]==x) return pre[x];
        else return pre[x]=root(pre[x]);
    }
}using namespace DSU;

namespace Tree{
    int htop[MN],hson[MN],dfn[MN],dep[MN],siz[MN],fa[MN],dtot;

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
        fa[u]=pre;
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

void work(int x,int y){
    while(dep[fa[x]]>dep[y]){
        pre[root(x)]=pre[root(fa[x])];
        pre[root(x+n)]=pre[root(fa[x]+n)];
        x=root(fa[x]);
    }
}

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>m;
    initpre();
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
        qlca[i]=lca(a[i],b[i]);
        work(a[i],qlca[i]);
        work(b[i],qlca[i]);
    }
    for(int i=1;i<=m;i++){
        if(qlca[i]!=a[i]&&qlca[i]!=b[i]){
            pre[root(a[i]+n)]=root(b[i]);
            pre[root(b[i]+n)]=root(a[i]);
        }
    }
    for(int i=2;i<=n;i++){
        if(root(i)==root(i+n)){
            cout<<0;
            return 0;
        }
        if(root(i)==i) ans++;
        if(root(i+n)==i+n) ans++;
    }
    if(ans){
        cout<<ksm(2,ans/2);
    }else cout<<0;
    return 0;
}