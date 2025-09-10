#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
struct Edge{int u,v,w;}e[MN];
int n,m,q,rt[MN];
bool cmp1(const Edge &x,const Edge &y){return x.w<y.w;}
bool cmp2(const Edge &x,const Edge &y){return x.w>y.w;}
struct Segment{
    struct Node{int lson,rson,cnt;}t[MN*50];
    int tot;
    void build(int &p,int l,int r){p=++tot;if(l==r)return;int mid=(l+r)>>1;build(t[p].lson,l,mid);build(t[p].rson,mid+1,r);}
    void modify(int &p,int lst,int l,int r,int pos){
        p=++tot;t[p]=t[lst];t[p].cnt++;
        if(l==r)return;int mid=(l+r)>>1;
        if(pos<=mid)modify(t[p].lson,t[lst].lson,l,mid,pos);
        else modify(t[p].rson,t[lst].rson,mid+1,r,pos);
    }
    int query(int x,int y,int l,int r,int fl,int fr){
        if(fl<=l&&r<=fr)return t[y].cnt-t[x].cnt;
        int mid=(l+r)>>1,ret=0;
        if(fl<=mid)ret+=query(t[x].lson,t[y].lson,l,mid,fl,fr);
        if(fr>mid)ret+=query(t[x].rson,t[y].rson,mid+1,r,fl,fr);
        return ret;
    }
}sg;
struct Tree{
    int pre[MN],dfntot,val[MN],fa[31][MN],siz[MN],dfn[MN],id[MN],dtot;
    vector<int> adj[MN];
    int root(int x){return pre[x]==x?x:pre[x]=root(pre[x]);}
    void dfs1(int u,int pre0){
        dfn[u]=++dfntot;id[dfntot]=u;siz[u]=1;fa[0][u]=pre0;
        for(int i=1;i<31;i++){int mid=fa[i-1][u];fa[i][u]=mid?fa[i-1][mid]:0;}
        for(auto v:adj[u])if(v!=pre0){dfs1(v,u);siz[u]+=siz[v];}
    }
    void buildkru(int id0){
        dtot=n;for(int i=1;i<=2*n;i++)pre[i]=i;
        if(id0)sort(e+1,e+m+1,cmp2);else sort(e+1,e+m+1,cmp1);
        for(int i=1;i<=m;i++){int ru=root(e[i].u),rv=root(e[i].v);
            if(ru!=rv){dtot++;adj[dtot].push_back(ru);adj[dtot].push_back(rv);val[dtot]=e[i].w;pre[ru]=pre[rv]=dtot;if(dtot==2*n-1)break;}
        }
        dfs1(dtot,0);
    }
    int findu(int u,int k){for(int i=30;i>=0;i--)if(fa[i][u]&&val[fa[i][u]]>=k)u=fa[i][u];return u;}
    int findv(int u,int k){for(int i=30;i>=0;i--)if(fa[i][u]&&val[fa[i][u]]<=k)u=fa[i][u];return u;}
}t1,t2;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=m;i++){cin>>e[i].u>>e[i].v;e[i].u++;e[i].v++;e[i].w=min(e[i].u,e[i].v);}
    t1.buildkru(1);
    for(int i=1;i<=m;i++)e[i].w=max(e[i].u,e[i].v);
    t2.buildkru(0);
    sg.build(rt[0],1,(n<<1)-1);
    for(int i=1;i<(n<<1);i++){rt[i]=rt[i-1];if(t1.id[i]<=n)sg.modify(rt[i],rt[i-1],1,(n<<1)-1,t2.dfn[t1.id[i]]);}
    while(q--){
        int s,e0,l,r;cin>>s>>e0>>l>>r;s++,e0++,l++,r++;
        int u=t1.findu(s,l),v=t2.findv(e0,r);
        cout<<(bool)(sg.query(rt[t1.dfn[u]-1],rt[t1.dfn[u]+t1.siz[u]-1],1,(n<<1)-1,t2.dfn[v],t2.dfn[v]+t2.siz[v]-1))<<"\n";
    }
    return 0;
}
