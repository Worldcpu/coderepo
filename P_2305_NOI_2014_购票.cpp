#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=4e5+15,INF=2e18;
int n,t,f[MN],s[MN],p[MN],q[MN],L[MN];
vector<int> adj[MN];

struct Line{
    int k,b;
    
    Line(int kk=0,int bb=INF){
        k=kk,b=bb;
    }

    int get(int x){
        return k*x+b;
    }
};

struct LCSSegment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson;
        Line val;
    }t[MN*20];
    int tot;

    void update(int &p,int l,int r,Line k){
        if(!p){
            p=++tot;
            t[p].val=k;
            return;
        }
        int mid=(l+r)>>1;
        if(t[p].val.get(mid)>k.get(mid)) swap(t[p].val,k);
        if(l==r) return;
        if(t[p].val.get(l)>k.get(l)) update(ls,l,mid,k);
        if(t[p].val.get(r)>k.get(r)) update(rs,mid+1,r,k);
    }

    int query(int p,int l,int r,int x){
        int mid=(l+r)>>1,ret=t[p].val.get(x);
        if(!p||l==r) return ret;
        if(mid>=x) return min(ret,query(ls,l,mid,x));
        else return min(ret,query(rs,mid+1,r,x));
    }
    #undef ls
    #undef rs
}lcsg;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,rt;
    }t[MN<<2];

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
    }

    void modify(int p,int pos,Line k){
        lcsg.update(t[p].rt,0,1e6,k);
        if(t[p].l==t[p].r) return;
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
    }

    int query(int p,int fl,int fr,int x){
        if(fl>fr) return INF;
        if(t[p].l>=fl&&t[p].r<=fr){
            return lcsg.query(t[p].rt,0,1e6,x);
        }
        int mid=(t[p].l+t[p].r)>>1,ret=INF;
        if(mid>=fl) ret=min(ret,query(ls,fl,fr,x));
        if(mid<fr) ret=min(ret,query(rs,fl,fr,x));
        return ret;
    }
    #undef ls
    #undef rs
}sg;

namespace Tree{
    int out[MN],dtot,dep[MN],id[MN],top;

    void dfs1(int u,int pre){
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
        out[u]=++dtot;
    }

    void dfs2(int u,int pre){
        id[top]=u;
        sg.modify(1,out[u],Line(-dep[top],f[u]));
        for(auto v:adj[u]){
            if(v==pre) continue;
            top++;
            dep[top]=dep[top-1]+s[v];
            int x=out[id[lower_bound(dep,dep+top,dep[top]-L[v])-dep]];
            f[v]=sg.query(1,out[u],x,p[v])+dep[top]*p[v]+q[v];
            dfs2(v,u);
            top--;
        }
    }
}


signed main(){
    cin>>n>>t;
    for(int i=2;i<=n;i++){
        int fa;
        cin>>fa>>s[i]>>p[i]>>q[i]>>L[i];
        adj[fa].push_back(i);
        adj[i].push_back(fa);
    }
    sg.build(1,1,n);
    Tree::dfs1(1,0);
    Tree::dfs2(1,0);
    for(int i=2;i<=n;i++){
        cout<<f[i]<<'\n';
    }
    return 0;
}