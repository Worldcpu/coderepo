#include<bits/stdc++.h>
using namespace std;
constexpr int MN=4e5+15;
struct Query{
    int l,r,lca,id;
}q[MN];
int n,m,tot,ret,len,dtot,ans[MN],pos[MN],st[MN],ed[MN],fa[MN],a[MN],b[MN],top[MN],hson[MN],siz[MN],dep[MN],cnt[MN];
bool vis[MN];
vector<int> adj[MN];

bool cmp(Query x,Query y){
    if(x.l/len!=y.l/len) return x.l<y.l;
    else return x.r<y.r;
}

void dfs1(int u,int pre){
    dep[u]=dep[pre]+1;
    fa[u]=pre;
    siz[u]=1;
    st[u]=++dtot,pos[dtot]=u;
    int maxp=-1;
    for(auto v:adj[u]){
        if(v==pre) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(maxp<siz[v]){
            maxp=siz[v];
            hson[u]=v;
        }
    }
    ed[u]=++dtot,pos[dtot]=u;
}

void dfs2(int u,int ltop){
    top[u]=ltop;
    if(!hson[u]) return;
    dfs2(hson[u],ltop);
    for(auto v:adj[u]){
        if(v==fa[u]||v==hson[u]) continue;
        dfs2(v,v);
    }
}

int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

void add(int p){
    if(++cnt[p]==1) ret++;
}

void del(int p){
    if(--cnt[p]==0) ret--;
}

void Add(int p){
    vis[p]?del(a[p]):add(a[p]);
    vis[p]^=1;
}

int main(){
    cin>>n>>m;
    len=sqrt(n);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+tot,a[i])-b;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        if(st[x]>st[y]) swap(x,y);
        int qlca=lca(x,y);
        q[i].id=i;
        if(qlca==x) q[i].l=st[x],q[i].r=st[y];
        else q[i].l=ed[x],q[i].r=st[y],q[i].lca=qlca;
    }
    sort(q+1,q+1+m,cmp);
    int l=1,r=0;
    for(int i=1;i<=m;i++){
        while(l<q[i].l) Add(pos[l]),l++;
        while(l>q[i].l) l--,Add(pos[l]);
        while(r<q[i].r) r++,Add(pos[r]);
        while(r>q[i].r) Add(pos[r]),r--;
        if(q[i].lca) Add(q[i].lca);
        ans[q[i].id]=ret;
        if(q[i].lca) Add(q[i].lca);
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
    return 0;
}