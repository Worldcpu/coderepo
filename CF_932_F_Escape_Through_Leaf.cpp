#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MV=1e5,INF=1e18;
int n,a[MN],b[MN],ans[MN],rt[MN];
vector<int> adj[MN];

struct Line{
    int k,b;

    Line(int kk=0,int bb=0){
        k=kk,b=bb;
    }

    int get(int x){
        return k*x+b;
    }
};

struct LCSegment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson;
        Line val;
    }t[MN*10];
    int tot;

    void update(int &p,int l,int r,Line k){
        if(!p){
            p=++tot;
            t[p].val=k;
            return;
        }
        int mid=(l+r)>>1;
        if(k.get(mid)<t[p].val.get(mid)) swap(t[p].val,k);
        if(l==r) return;
        if(k.get(l)<t[p].val.get(l)) update(ls,l,mid,k);
        if(k.get(r)<t[p].val.get(r)) update(rs,mid+1,r,k);
    }

    int merge(int x,int y,int l,int r){
        if(!x||!y) return x|y;
        if(l==r){
            return t[x].val.get(l)>t[y].val.get(l)?y:x;
        }
        int mid=(l+r)>>1;
        t[x].lson=merge(t[x].lson,t[y].lson,l,mid);
        t[x].rson=merge(t[x].rson,t[y].rson,mid+1,r);
        update(x,l,r,t[y].val);
        return x;
    }

    int query(int p,int l,int r,int x){
        if(!p) return INF;
        int mid=(l+r)>>1,ret=t[p].val.get(x);
        if(l==r) return ret;
        if(mid>=x) return min(ret,query(ls,l,mid,x));
        else return min(ret,query(rs,mid+1,r,x));
    }
}sg;

void dfs1(int u,int pre){
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        rt[u]=sg.merge(rt[u],rt[v],-MV,MV);
    }
    if(rt[u]) ans[u]=sg.query(rt[u],-MV,MV,a[u]);
    sg.update(rt[u],-MV,MV,Line(b[u],ans[u]));
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<' ';
    }

    return 0;
}