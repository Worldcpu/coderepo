#include<bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
constexpr int MN=1e5+15;
constexpr double eps=1e-6;
struct Edge{
    int v,w;
};
int n,L,R;
double tmp[MN],V;
vector<Edge> adj[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r;
        double val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=max(t[ls].val,t[rs].val);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].val=-1e18;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int pos,double k){
        if(t[p].l==t[p].r){
            t[p].val=max(t[p].val,k);
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    double query(int p,int fl,int fr){
        if(fl>fr) return -1e18;
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        int mid=(t[p].l+t[p].r)>>1;
        double ret=-1e18;
        if(mid>=fl) ret=query(ls,fl,fr);
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }
#undef ls
#undef rs
}sg;

namespace Tree{
    int htop[MN],hson[MN],dep[MN],mxdep[MN],val[MN],len[MN],fa[MN],dfn[MN],dtot;
    double dis[MN],ret;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=mxdep[u]=dep[pre]+1;
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==pre) continue;
            dfs1(v,u);
            if(mxdep[u]<mxdep[v]){
                mxdep[u]=mxdep[v];
                hson[u]=v;
                val[v]=w;
            }
        }
        len[u]=mxdep[u]-dep[u];
    }

    void dfs2(int u,int ltop){
        dfn[u]=++dtot;
        if(hson[u]) dfs2(hson[u],ltop);
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    void dfs3(int u,int pre){
        sg.modify(1,dfn[u],dis[u]);
        if(hson[u]){
            dis[hson[u]]=dis[u]+val[hson[u]]-V;
            dfs3(hson[u],u);
        }
        for(auto e:adj[u]){
            int v=e.v,w=e.w;
            if(v==fa[u]||v==hson[u]) continue;
            dis[v]=dis[u]+e.w-V;
            dfs3(v,u);
            for(int i=1;i<=len[v]+1;i++){
                tmp[i]=sg.query(1,dfn[v]+i-1,dfn[v]+i-1);
            }
            for(int i=1;i<=min(len[v]+1,R);i++){
                ret=max(ret,tmp[i]+sg.query(1,dfn[u]+L-i,min(dfn[u]+R-i,dfn[u]+len[u]))-2*dis[u]);
            }
            for(int i=1;i<=len[v]+1;i++){
                sg.modify(1,dfn[u]+i,tmp[i]);
            }
        }
        ret=max(ret,sg.query(1,dfn[u]+L,min(dfn[u]+R,dfn[u]+len[u]))-dis[u]);
    }
}using namespace Tree;

bool check(double x){
    sg.build(1,1,n);
    V=x,ret=-1e18;
    dfs3(1,0);
    return ret>=0;
}

signed main(){
    cin>>n>>L>>R;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs1(1,0);
    dfs2(1,1);
    double l=0,r=1e7;
    while(r-l>eps){
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    cout<<fixed<<setprecision(3)<<l;

    return 0;
}
