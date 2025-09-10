#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,q;
vector<int> adj[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int sum,mx;

        Node(int s=0,int m=0){
            sum=s;
            mx=m;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.sum=x.sum+y.sum;
            ret.mx=max({y.mx,y.sum+x.mx});
            return ret;
        }

    }ndinit;

    struct SNode{
        int l,r,tag;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void doclear(int p){
        t[p].val={-(t[p].r-t[p].l+1),-1};
        t[p].tag=1;
    }

    void pushdown(int p){
        if(t[p].tag){
            doclear(ls);
            doclear(rs);
            t[p].tag=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val={0,0};
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val.sum+=k;
            t[p].val.mx=t[p].val.sum;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }
    
    void clear(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            doclear(p);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) clear(ls,fl,fr);
        if(mid<fr) clear(rs,fl,fr);
        pushup(p);
    }

    auto query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

}sg;

namespace Tree{
    int dep[MN],fa[MN],hson[MN],htop[MN],siz[MN],dfn[MN],id[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        dep[u]=dep[pre]+1;
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
            if(v==fa[u]||v==hson[u]) continue;
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

    int query(int x){
        auto ret=sg.ndinit;
        while(x){
            ret=sg.query(1,dfn[htop[x]],dfn[x])+ret;
            x=fa[htop[x]];
        }
        return ret.mx;
    }

}using namespace Tree;

void init(){
    sg.ndinit.sum=0,sg.ndinit.mx=-1;
}

int main(){
    init();
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        int pre;
        cin>>pre;
        adj[pre].push_back(i);
        adj[i].push_back(pre);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++){
        cerr<<hson[i]<<' ';
    }
    cerr<<'\n';
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        sg.modify(1,i,-1);
    }
    while(q--){
        int op,x;
        cin>>op>>x;
        if(op==1){
            sg.modify(1,dfn[x],1);
        }
        if(op==2){
            sg.clear(1,dfn[x],dfn[x]+siz[x]-1);
            sg.modify(1,dfn[x],-1-query(x));
        }
        if(op==3){
            cerr<<query(x)<<'\n';
            if(x==7){
                cerr<<query(4)<<' '<<query(1)<<'\n';
            }
            cout<<(query(x)>=0?"black":"white")<<'\n';
        }
    }

    return 0;
}