#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,m,mx[MN],rt[MN];
vector<int> adj[MN];

struct Segment{
    #define ls t[p].lson
    #define rs t[p].rson
    struct Node{
        int lson,rson,val,tag=1;
    }t[MN<<3];
    int tot,tmp;

    void pushup(int p){
        t[p].val=(t[ls].val+t[rs].val)%MOD;
    }
    
    void domul(int p,int k){
        t[p].val=t[p].val*k%MOD;
        t[p].tag=t[p].tag*k%MOD;
    }

    void pushdown(int p){
        if(t[p].tag!=1){
            domul(ls,t[p].tag);
            domul(rs,t[p].tag);
            t[p].tag=1;
        }
    }

    void update(int &p,int l,int r,int pos,int k){
        if(!p) p=++tot;
        if(l==r){
            t[p].val=k;
            return;
        }
        pushdown(p);
        int mid=(l+r)>>1;
        if(mid>=pos) update(ls,l,mid,pos,k);
        else update(rs,mid+1,r,pos,k);
        pushup(p);
    }

    int query(int p,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(l+r)>>1,ret=0;
        if(mid>=fl) (ret+=query(ls,l,mid,fl,fr))%=MOD;
        if(mid<fr) (ret+=query(rs,mid+1,r,fl,fr))%=MOD;
        return ret;
    }

    int merge(int x,int y,int l,int r,int s1,int s2){
        if(!x&&!y) return 0;
        if(!x){
            domul(y,s2);
            return y;
        }
        if(!y){
            domul(x,s1+tmp);
            return x;
        }
        if(l==r){
            t[x].val=(t[x].val*(s1+t[y].val+tmp)%MOD+t[y].val*s2)%MOD;
            return x;
        }
        int mid=(l+r)>>1;
        pushdown(x);
        pushdown(y);
        t[x].rson=merge(t[x].rson,t[y].rson,mid+1,r,(s1+t[t[y].lson].val)%MOD,(s2+t[t[x].lson].val)%MOD);
        t[x].lson=merge(t[x].lson,t[y].lson,l,mid,s1,s2);
        pushup(x);
        return x;
    }

}sg;

namespace Tree{
    int dep[MN];
    
    void dfs1(int u,int pre){
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
        }
    }

    void dfs2(int u,int pre){
        sg.update(rt[u],0,n,mx[u],1);
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs2(v,u);
            sg.tmp=sg.query(rt[v],0,n,0,dep[u]);
            rt[u]=sg.merge(rt[u],rt[v],0,n,0,0);
        }
    }

}using namespace Tree;

signed main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    cin>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        mx[v]=max(mx[v],dep[u]);
    }
    dfs2(1,0);
    cout<<sg.query(rt[1],0,n,0,0);

    return 0;
}