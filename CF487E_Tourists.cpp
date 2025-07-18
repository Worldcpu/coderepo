#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e6+15;
int n,m,q,ftot,w[MN],id[MN];
multiset<int> s[MN];
vector<int> adj[MN],G[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=min(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=w[id[l]];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].val;
        int mid=(t[p].l+t[p].r)>>1,ret=1e9;
        if(mid>=fl) ret=query(ls,fl,fr);
        if(mid<fr) ret=min(ret,query(rs,fl,fr));
        return ret;
    }

#undef ls
#undef rs
}sg;

namespace YFTarjan{
    int dfn[MN],low[MN],stk[MN],tp,dtot;

    void init(){
        ftot=n;
    }

    void tarjan(int u){
        low[u]=dfn[u]=++dtot;
        stk[++tp]=u;
        for(auto v:adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u]=min(low[u],low[v]);
                if(low[v]==dfn[u]){
                    ftot++;
                    int x;
                    do{
                        x=stk[tp--];
                        G[ftot].push_back(x);
                        G[x].push_back(ftot);
                    }while(x!=v);
                    G[ftot].push_back(u);
                    G[u].push_back(ftot);
                }
            }else low[u]=min(low[u],dfn[v]);
        }
    }
}

namespace Tree{
    int fa[MN],dep[MN],siz[MN],hson[MN],htop[MN],dfn[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
        siz[u]=1;
        for(auto v:G[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
        id[dtot]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:G[u]){
            if(v!=fa[u]&&v!=hson[u]){
                dfs2(v,v);
            }
        }
    }

}using namespace Tree;


int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        cin>>w[i];
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    YFTarjan::init();
    YFTarjan::tarjan(1);
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        if(fa[i]){
            s[fa[i]].insert(w[i]);
        }
    }
    for(int i=n+1;i<=ftot;i++){
        w[i]=*s[i].begin();
    }
    sg.build(1,1,ftot);
    while(q--){
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='C'){
            sg.modify(1,dfn[x],y);
            if(fa[x]){
                int u=fa[x];
                s[u].erase(s[u].lower_bound(w[x]));
                s[u].insert(y);
                if(w[u]!=*s[u].begin()){
                    w[u]=*s[u].begin();
                    sg.modify(1,dfn[u],w[u]);
                }
            }
            w[x]=y;
        }else{
            int ans=1e9;
            while(htop[x]!=htop[y]){
                if(dep[htop[x]]<dep[htop[y]]) swap(x,y);
                ans=min(ans,sg.query(1,dfn[htop[x]],dfn[x]));
                x=fa[htop[x]];
            }
            if(dfn[x]>dfn[y]) swap(x,y);
            ans=min(ans,sg.query(1,dfn[x],dfn[y]));
            if(x>n) ans=min(ans,w[fa[x]]);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
