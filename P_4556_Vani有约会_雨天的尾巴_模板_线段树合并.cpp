#include<bits/stdc++.h>
#define ls t[p].lc
#define rs t[p].rc
using namespace std;
const int MN=3e6+15,ML=20,MF=1e6+15;
int n,m,fa[MN][35],dep[MN],tot,rt[MN],ans[MN];
struct segtree{
    int maxval,l,r,id,lc,rc;
}t[MN<<2];
// LCA's PART
vector<int> adj[MN];
void dfs(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[u][0]=pre;
    for(int i=1;i<=ML;i++){
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if(v!=pre){
            dfs(v,u);
        }
    }
}
int lca(int x,int y){
    if(dep[x]>dep[y]){
        swap(x,y);
    }
    for(int i=ML;i>=0;i--){
        if(dep[fa[y][i]]>=dep[x]){
            y=fa[y][i];
        }
    }
    if(x==y){
        return x;
    }
    for(int i=__lg(dep[x]);i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}

// SEGTREE's PART
// 维护权值线段树，编号p即种类

void pushup(int p){
    if(t[ls].maxval>=t[rs].maxval){
        t[p].maxval=t[ls].maxval;
        t[p].id=t[ls].id;
    }else{
        t[p].maxval=t[rs].maxval;
        t[p].id=t[rs].id;
    }
}

void update(int &p,int l,int r,int foodid,int k){
    if(!p) p=++tot;
    if(l==r){
        t[p].maxval+=k;
        t[p].id=foodid;
        return;
    }
    int mid=l+r>>1;
    if(foodid<=mid) update(ls,l,mid,foodid,k);
    else update(rs,mid+1,r,foodid,k);
    pushup(p);
}

int merge(int x,int y,int l,int r){
    if(!x&&!y) return 0;
    if(!x) return y;
    if(!y) return x;
    int p=++tot;
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].maxval=t[x].maxval+t[y].maxval;
        t[p].id=l;
        return p;
    }
    int mid=l+r>>1;
    ls=merge(t[x].lc,t[y].lc,l,mid);
    rs=merge(t[x].rc,t[y].rc,mid+1,r);
    pushup(p);
    return p;
}

// GET ANS FROM CHAFEN

void dfs2(int u,int pre){
    for(auto v:adj[u]){
        if(v!=pre){
            dfs2(v,u);
            rt[u]=merge(rt[u],rt[v],1,MF);
        }
    }
    ans[u]=(t[rt[u]].maxval)?t[rt[u]].id:0;
}
int main(){
    freopen("P4556_13.in","r",stdin);
    cin>>n>>m;

    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    while(m--)
    {
        int u,v,k;
        cin>>u>>v>>k;
        int lcauv=lca(u,v);
        update(rt[u],1,MF,k,1);
        update(rt[v],1,MF,k,1);
        update(rt[lcauv],1,MF,k,-1);
        update(rt[fa[lcauv][0]],1,MF,k,-1);
    }
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}