#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5000005;

int n,q,dg[MN],pos[MN][2],rev[MN],rt[2];
vector<int> adj[MN],G[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson

    struct Node{
        int lson,rson;
    }t[MN<<2];
    int tot;

    void init(){
        for(int i=1;i<=tot;i++){
            G[i].clear();
            dg[i]=0;
        }
        tot=0;
    }

    void build(int &p,int l,int r,int type){
        p=++tot;
        if(l==r){
            pos[l][type]=p;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid,type);
        build(rs,mid+1,r,type);
        if(type){
            G[p].push_back(ls); dg[ls]++;
            G[p].push_back(rs); dg[rs]++;
        }else{
            G[ls].push_back(p); dg[p]++;
            G[rs].push_back(p); dg[p]++;
        }
    }

    void update(int p,int l,int r,int fl,int fr,int x,int type){
        if(l>fr || r<fl) return;
        if(l>=fl && r<=fr){
            if(type){
                G[x].push_back(p); dg[p]++;
            }else{
                G[p].push_back(x); dg[x]++;
            }
            return;
        }
        int mid=(l+r)>>1;
        update(ls,l,mid,fl,fr,x,type);
        update(rs,mid+1,r,fl,fr,x,type);
    }

    #undef ls
    #undef rs
}sg;

namespace Tree{
    int dfn[MN],hson[MN],htop[MN],siz[MN],dep[MN],fa[MN],dtot;

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
        dfn[u]=++dtot;
        rev[dfn[u]]=u;
        if(hson[u]) dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    void update(int x,int y,int z){
        if(dep[x]<dep[y]) swap(x,y);
        if(dfn[y]<=dfn[x] && dfn[x]<=dfn[y]+siz[y]-1){
            x=fa[x];
            while(htop[x]!=htop[y]){
                sg.update(rt[0],1,n,dfn[htop[x]],dfn[x],z,0);
                sg.update(rt[1],1,n,dfn[htop[x]],dfn[x],z,1);
                x=fa[htop[x]];
            }
            sg.update(rt[0],1,n,dfn[y]+1,dfn[x],z,0);
            sg.update(rt[1],1,n,dfn[y]+1,dfn[x],z,1);
        }else{
            x=fa[x], y=fa[y];
            while(htop[x]!=htop[y]){
                if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
                sg.update(rt[0],1,n,dfn[htop[x]],dfn[x],z,0);
                sg.update(rt[1],1,n,dfn[htop[x]],dfn[x],z,1);
                x=fa[htop[x]];
            }
            if(dfn[x]<dfn[y]) swap(x,y);
            sg.update(rt[0],1,n,dfn[y],dfn[x],z,0);
            sg.update(rt[1],1,n,dfn[y],dfn[x],z,1);
        }
    }

}using namespace Tree;

void init(){
    dtot=0;
    sg.init();
    for(int i=1;i<=n;i++){
        adj[i].clear();
        hson[i]=siz[i]=htop[i]=dfn[i]=dep[i]=fa[i]=pos[i][0]=pos[i][1]=0;
    }
    sg.build(rt[0],1,n,0);
    sg.build(rt[1],1,n,1);
}

bool toposort(){
    queue<int> q;
    for(int i=1;i<=sg.tot;i++){
        if(!dg[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto v:G[u]){
            dg[v]--;
            if(!dg[v]) q.push(v);
        }
    }
    for(int i=1;i<=sg.tot;i++) if(dg[i]) return false;
    return true;
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);

    cin>>q;
    while(q--){
        int x,y; cin>>x>>y;
        sg.tot++;
        int cur=sg.tot;
        // 注意顺序保持和正确代码一致
        G[pos[dfn[y]][0]].push_back(cur); dg[cur]++;
        G[pos[dfn[y]][1]].push_back(cur); dg[cur]++;
        G[cur].push_back(pos[dfn[x]][0]); dg[pos[dfn[x]][0]]++;
        G[cur].push_back(pos[dfn[x]][1]); dg[pos[dfn[x]][1]]++;
        update(x,y,cur);
    }
    cout<<(toposort()?"Yes\n":"No\n");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
