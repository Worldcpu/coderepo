#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e4+15,MOD=201314;
int n,m,z[MN],ans[MN];
vector<int> adj[MN];
vector<int> pl[MN],mi[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Node{
        int l,r,val,tag;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=(t[ls].val+t[rs].val)%MOD;
    }

    void dotag(int p,int k){
        t[p].tag+=k;
        (t[p].val+=(t[p].r-t[p].l+1)*k%MOD)%=MOD;
    }
    
    void pushdown(int p){
        if(t[p].tag){
            dotag(ls,t[p].tag);
            dotag(rs,t[p].tag);
            t[p].tag=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modfiy(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            dotag(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modfiy(ls,fl,fr,k);
        if(mid<fr) modfiy(rs,fl,fr,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        int ret=0;
        if(mid>=fl) (ret+=query(ls,fl,fr))%=MOD;
        if(mid<fr) (ret+=query(rs,fl,fr))%=MOD;
        return ret;
    }

#undef ls
#undef rs
}sg;

namespace Tree{
    int fa[MN],siz[MN],dep[MN],hson[MN],htop[MN],dfn[MN],dtot;

    void dfs1(int u,int pre){
        fa[u]=pre;
        siz[u]=1;
        dep[u]=dep[pre]+1;
        for(auto v:adj[u]){
            if(v==pre) continue;
            dfs1(v,u);
            siz[u]+=siz[v];
            if(!hson[u]||siz[hson[u]]<siz[v]) hson[u]=v;
        }
    }

    void dfs2(int u,int ltop){
        htop[u]=ltop;
        dfn[u]=++dtot;
        if(!hson[u]) return;
        dfs2(hson[u],ltop);
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
        }
    }

    void modfiy(int x){
        while(x){
            sg.modfiy(1,dfn[htop[x]],dfn[x],1);
            x=fa[htop[x]];
        }
    }

    int query(int x){
        int ans=0;
        while(x){
            ans=(ans+sg.query(1,dfn[htop[x]],dfn[x]))%MOD;
            x=fa[htop[x]];
        }
        return ans;
    }

}using namespace Tree;

signed main(){
    cin>>n>>m;
    for(int i=2;i<=n;i++){
        int pre;
        cin>>pre;
        adj[++pre].push_back(i);
    }
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r>>z[i];
        ++z[i];
        mi[l].push_back(i);
        pl[r+1].push_back(i);
    }
    dfs1(1,0);
    dfs2(1,1);
    sg.build(1,1,n);
    for(int i=1;i<=n;i++){
        modfiy(i);
        for(auto it:pl[i]){
            ans[it]+=query(z[it]);
        }
        for(auto it:mi[i]){
            ans[it]-=query(z[it]);
        }
    }
    for(int i=1;i<=m;i++){
        cout<<(ans[i]%MOD+MOD)%MOD<<'\n';
    }
    return 0;
}
