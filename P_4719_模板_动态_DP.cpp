#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1e5+15,INF=0x3f3f3f3f;
int n,m,dtot,a[MN],id[MN],dfn[MN],f[MN][2],g[MN][2],fa[MN],hson[MN],siz[MN],dep[MN],htop[MN],ltail[MN];
vector<int> adj[MN];

struct Matrix{
    int mat[2][2];
    
    Matrix(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                mat[i][j]=-INF;
            }
        }
    }

    Matrix operator*(const Matrix &x)const{
        Matrix ret;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    ret.mat[i][j]=max(ret.mat[i][j],mat[i][k]+x.mat[k][j]);
                }
            }
        }
        return ret;
    }

}mt[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r;
        Matrix val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val*t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=mt[id[l]];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modfiy(int p,int pos){
        if(t[p].l==t[p].r){
            t[p].val=mt[id[pos]];
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modfiy(ls,pos);
        else modfiy(rs,pos);
        pushup(p);
    }

    Matrix query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].val;
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return query(rs,fl,fr);
        if(mid>=fr) return query(ls,fl,fr);
        return query(ls,fl,fr)*query(rs,fl,fr);
    }
}sg;

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
    ltail[u]=u;
    dfn[u]=++dtot;
    id[dtot]=u;
    f[u][1]=a[u];
    f[u][0]=0;
    g[u][1]=a[u];
    g[u][0]=0;
    if(hson[u]){
        dfs2(hson[u],ltop);
        f[u][0]+=max(f[hson[u]][0],f[hson[u]][1]);
        f[u][1]+=f[hson[u]][0];
        ltail[u]=ltail[hson[u]];
        for(auto v:adj[u]){
            if(v==fa[u]||v==hson[u]) continue;
            dfs2(v,v);
            f[u][0]+=max(f[v][0],f[v][1]);
            f[u][1]+=f[v][0];
            g[u][0]+=max(f[v][0],f[v][1]);
            g[u][1]+=f[v][0];
        }
    }
    mt[u].mat[0][0]=g[u][0];
    mt[u].mat[0][1]=g[u][0];
    mt[u].mat[1][0]=g[u][1];
    mt[u].mat[1][1]=-INF;
}

void modfiychain(int u, int k){
    g[u][1] += k - a[u];
    a[u] = k;
    mt[u].mat[1][0] = g[u][1];
    while(u){
        Matrix bef = sg.query(1, dfn[htop[u]], dfn[ltail[u]]);
        sg.modfiy(1, dfn[u]);
        Matrix aft = sg.query(1, dfn[htop[u]], dfn[ltail[u]]);
        u = fa[htop[u]];
        int delta0 = max(aft.mat[0][0], aft.mat[1][0]) - max(bef.mat[0][0], bef.mat[1][0]);
        int delta1 = aft.mat[0][0] - bef.mat[0][0];
        g[u][0] += delta0;
        g[u][1] += delta1;
        mt[u].mat[0][0] = g[u][0];
        mt[u].mat[0][1] = g[u][0];
        mt[u].mat[1][0] = g[u][1];
        mt[u].mat[1][1] = -INF;
    }
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    sg.build(1,1,n);
    while(m--){
        int x,y;
        cin>>x>>y;
        modfiychain(x,y);
        Matrix ret=sg.query(1,dfn[1],dfn[ltail[1]]);
        cout<<max(ret.mat[0][0],ret.mat[1][0])<<'\n';
    }
    return 0;
}
