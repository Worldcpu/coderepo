#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e6+15;
int n,q,rt[MN];
vector<int> adj[MN];

struct Segment{
#define ls t[p].lson
#define rs t[p].rson

    struct Node{
        int lson,rson,val;
    }t[MN];
    int tot;

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void modify(int &p,int l,int r,int pos,int k){
        if(!p) p=++tot;
        if(l==r){
            t[p].val=k;
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=pos) modify(ls,l,mid,pos,k);
        else modify(rs,mid+1,r,pos,k);
        pushup(p);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(!p) return 0;
        if(l>=fl&&r<=fr){
            return t[p].val;
        }
        int mid=(l+r)>>1;
        int ret=0;
        if(mid>=fl) ret+=query(ls,l,mid,fl,fr);
        if(mid<fr) ret+=query(rs,mid+1,r,fl,fr);
        return ret;
    }

    int merge(int x,int y){
        if(!x||!y) return x|y;
        int p=++tot;
        t[p].val=t[x].val+t[y].val;
        t[p].lson=merge(t[x].lson,t[y].lson);
        t[p].rson=merge(t[x].rson,t[y].rson);
        return p;
    }

#undef ls
#undef rs
}sg;

namespace Tree{
    int dep[MN],siz[MN];

    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        siz[u]=1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
        }
        sg.modify(rt[u],1,n,dep[u],siz[u]-1);
        for(auto v:adj[u]){
            if(v==pre) continue;
            rt[u]=sg.merge(rt[u],rt[v]);
        }
    }

}using namespace Tree;

signed main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    Tree::dfs1(1,0);
    while(q--){
        int p,k;
        cin>>p>>k;
        int ans=min(dep[p]-1,k)*(siz[p]-1);
        ans+=sg.query(rt[p],1,n,dep[p]+1,dep[p]+k);
        cout<<ans<<'\n';
    }

    return 0;
}
