#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
struct Edge{
    int u,v,w;
}e[MN];
struct EDge{
    int v,w;
};
int n,a[MN],ans1=INF,ans2;
vector<EDge> adj[MN];



struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    struct SNode{
        int l,r,mn,add;
    }t[MN<<2];

    void doadd(int p,int k){
        t[p].mn+=k;
        t[p].add+=k;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].mn=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int pos){
        if(t[p].l==t[p].r){
            return t[p].mn;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) return query(ls,pos);
        else return query(rs,pos);
    }

}sg;

namespace Tree{
    int siz[MN],dfn[MN],id[MN],dtot,st[MN],ed[MN],fa[MN],val[MN];

    void dfs1(int u,int pre){
        siz[u]=1;
        dfn[u]=++dtot;
        id[dtot]=u;
        fa[u]=pre;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre) continue;
            val[v]=w;
            dfs1(v,u);
            siz[u]+=siz[v];
        }
    }

}using namespace Tree;


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        e[i]={u,v,w};
    }
    dfs1(1,0);
    sg.build(1,1,dtot);
    for(int i=2;i<=n;i++){
        int u=i,v=fa[i];
        sg.modify(1,dfn[u],dfn[u]+siz[u]-1,(n-siz[u])*(val[u]-a[u]));
        sg.modify(1,1,dfn[u]-1,(siz[u])*(val[u]-a[v]));
        sg.modify(1,dfn[u]+siz[u],n,(siz[u])*(val[u]-a[v]));
    }
    for(int i=n;i>=1;i--){
        auto ret=sg.query(1,i);
        if(ans1>ret){
            ans1=ret;
            ans2=i;
        }else if(ans1==ret){
            if(id[i]<id[ans2]){
                ans2=i;
            }
        }
    }
    cout<<id[ans2]<<'\n'<<ans1<<'\n';
    return 0;
}