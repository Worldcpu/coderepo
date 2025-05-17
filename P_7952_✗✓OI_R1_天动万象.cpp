#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,q,a[MN];
vector<int> adj[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct {
        int l,r,mx;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].mx=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(pos<=mid) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(fl>fr) return 0;
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].mx;
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(fl<=mid) ret=max(ret,query(ls,fl,fr));
        if(fr>mid) ret=max(ret,query(rs,fl,fr));
        return ret;
    }
#undef ls
#undef rs
}seg;

struct FHQTreap{
#define ls t[p].lson
#define rs t[p].rson
    struct Node{
        int lson,rson,dat,val,maxx,siz;
    }t[MN];
    int tot,rt[MN];

    int newnode(int k){
        t[++tot] = {0,0,rand(),k,k,1};
        return tot;
    }

    void pushup(int p){
        t[p].maxx = max({t[ls].maxx, t[rs].maxx, t[p].val});
        t[p].siz = t[ls].siz + t[rs].siz + 1;
    }

    void split(int p,int k,int &x,int &y){
        if(!p){x=y=0;return;}
        if(t[ls].siz < k){
            x = p;
            split(rs, k-t[ls].siz-1, rs, y);
        }else{
            y = p;
            split(ls, k, x, ls);
        }
        pushup(p);
    }

    int merge(int x,int y){
        if(!x||!y) return x+y;
        if(t[x].dat < t[y].dat){
            t[x].rson = merge(t[x].rson, y);
            pushup(x);
            return x;
        }else{
            t[y].lson = merge(x, t[y].lson);
            pushup(y);
            return y;
        }
    }

#undef ls
#undef rs
}fhq;

struct Tree{
    int htop[MN],dep[MN],fa[MN],dfn[MN],out[MN],idx;
    vector<int> g[MN],upd;

    void update(int p){
        seg.modify(1, dfn[p], fhq.t[fhq.rt[p]].maxx);
    }

    int top(int x){
        while(x != htop[x])
            x = htop[x] = htop[htop[x]];
        return x;
    }

    void dfs(int u,int tp){
        htop[u] = tp;
        dep[u] = dep[fa[u]] + 1;
        dfn[u] = ++idx;
        fhq.rt[tp] = fhq.merge(fhq.rt[tp], fhq.newnode(a[u]));
        
        if(adj[u].size() >= 2){
            for(int v:adj[u]){
                if(v == fa[u]) continue;
                g[tp].push_back(v);
                dfs(v, v);
            }
        }else if(adj[u].size() == 1){
            dfs(adj[u][0], tp);
        }
        
        if(u == tp) update(u);
        out[u] = idx;
    }

    int query(int u){
        int t = top(u);
        int sz = dep[u] - dep[t];
        int x,y;
        fhq.split(fhq.rt[t], sz, x, y);
        int res = max(fhq.t[y].maxx, seg.query(1, dfn[u]+1, out[u]));
        fhq.rt[t] = fhq.merge(x, y);
        return res;
    }

    void merge_chain(int u){
        int v = g[u][0];
        htop[v] = top(u);
        fhq.rt[u] = fhq.merge(fhq.rt[u], fhq.rt[v]);
        fhq.rt[v] = 0;
        swap(g[u], g[v]);
        g[v].clear();
        update(v);
        update(u);
    }

    int extract(int u){
        int x,y;
        fhq.split(fhq.rt[u], 1, x, y);
        int ret = fhq.t[x].val;
        fhq.t[x].val = 0;
        if(g[u].empty()){
            fhq.rt[u] = y;
            update(u);
            return ret;
        }
        
        vector<int> tmp;
        for(int v:g[u]){
            int w = extract(v);
            if(fhq.t[fhq.rt[v]].maxx) tmp.push_back(v);
            fhq.t[x].val += w;
        }
        fhq.t[x].maxx = fhq.t[x].val;
        g[u] = tmp;
        fhq.rt[u] = fhq.merge(y, x);
        if(g[u].size() == 1) upd.push_back(u);
        update(u);
        return ret;
    }

    void shift(int u){
        upd.clear();
        int t = top(u);
        int sz = dep[u] - dep[t];
        int x,y,z;
        fhq.split(fhq.rt[t], sz, x, y);
        fhq.split(y, 1, y, z);
        
        fhq.t[y].val = 0;
        vector<int> tmp;
        for(int v:g[t]){
            int w = extract(v);
            if(fhq.t[fhq.rt[v]].maxx) tmp.push_back(v);
            fhq.t[y].val += w;
        }
        fhq.t[y].maxx = fhq.t[y].val;
        g[t] = tmp;
        fhq.rt[t] = fhq.merge(fhq.merge(x, z), y);
        update(t);
        
        if(g[t].size() == 1) upd.push_back(t);
        for(int x:upd) merge_chain(x);
    }
}t;

signed main(){
    srand(time(0));
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=2;i<=n;i++){
        cin>>t.fa[i];
        adj[t.fa[i]].push_back(i);
    }
    seg.build(1,1,n);
    t.dfs(1,1);
    
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1) cout<<t.query(x)<<'\n';
        else t.shift(x);
    }
    return 0;
}
