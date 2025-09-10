#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int n,m,rt[MN],ans;
vector<int> adj[MN];
vector<int> cf[MN];

namespace Tree{
    int dep[MN],hson[MN],htop[MN],siz[MN],dfn[MN],id[MN],fa[MN],dtot;

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        fa[u]=pre;
        siz[u]=1;
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
        id[dtot]=u;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==hson[u]||v==fa[u]) continue;
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

    struct Segment{
        #define ls t[p].lson
        #define rs t[p].rson
        struct Node{
            int lson,rson,sum,ldfn,rdfn,cnt;
        }t[MN<<8];
        int tot;

        void pushup(int p){
            t[p].sum=t[ls].sum+t[rs].sum-dep[lca(t[ls].rdfn,t[rs].ldfn)];
            t[p].ldfn=t[ls].ldfn?t[ls].ldfn:t[rs].ldfn;
            t[p].rdfn=t[rs].rdfn?t[rs].rdfn:t[ls].rdfn;
        }

        void modify(int &p,int l,int r,int pos,int k){
            if(!p) p=++tot;
            if(l==r){
                t[p].cnt+=k;
                t[p].ldfn=t[p].rdfn=(t[p].cnt?id[l]:0);
                t[p].sum=(t[p].cnt?dep[id[l]]:0);
                return;
            }
            int mid=(l+r)>>1;
            if(mid>=pos) modify(ls,l,mid,pos,k);
            else modify(rs,mid+1,r,pos,k);
            pushup(p);
        }

        int merge(int x,int y,int l,int r){
            if(!x||!y) return x+y;
            if(l==r){
                t[x].cnt+=t[y].cnt;
                t[x].ldfn=t[x].rdfn=(t[x].cnt?id[l]:0);
                t[x].sum=(t[x].cnt?dep[id[l]]:0);
                return x;
            }
            int mid=(l+r)>>1;
            t[x].lson=merge(t[x].lson,t[y].lson,l,mid);
            t[x].rson=merge(t[x].rson,t[y].rson,mid+1,r);
            pushup(x);           
            return x;
        }
        #undef ls
        #undef rs
    }sg;

    void dfs3(int u){
        for(auto v:adj[u]){
            if(v==fa[u]) continue;
            dfs3(v);
            rt[u]=sg.merge(rt[u],rt[v],1,n);
        }
        for(auto p:cf[u]){
            sg.modify(rt[u],1,n,dfn[p],-1);
        }
        auto rtt=sg.t[rt[u]];
        ans+=rtt.sum-dep[lca(rtt.ldfn,rtt.rdfn)];
    }

}using namespace Tree;

signed main(){
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
        int x,y;
        cin>>x>>y;
        sg.modify(rt[x],1,n,dfn[x],1);
        sg.modify(rt[y],1,n,dfn[y],1);
        sg.modify(rt[x],1,n,dfn[y],1);
        sg.modify(rt[y],1,n,dfn[x],1);
        int lcaa=lca(x,y);
        cf[lcaa].push_back(x);
        cf[lcaa].push_back(y);
        cf[fa[lcaa]].push_back(y);
        cf[fa[lcaa]].push_back(x);
    }
    dfs3(1);
    cout<<ans/2;
    return 0;
}