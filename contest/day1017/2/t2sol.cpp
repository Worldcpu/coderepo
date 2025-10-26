#include<bits/stdc++.h>
#define int long long
const int N=7e5+5;
const int inf=1e17;
using namespace std;
int n,cnt;
int a[N],val[N],fa[N],siz[N],st[N],ed[N],rid[N];
int tans[N];
struct Edge{
    int to,w,nxt;
}e[N<<1];int head[N];
void add(int x,int y,int w)
{
    e[++head[0]]={y,w,head[x]};head[x]=head[0];
}
struct task{
    int u,v,w;
}q[N<<1];
void dfs(int x,int f)
{
    fa[x]=f;siz[x]=1;rid[st[x]=++cnt]=x;
    for(int i=head[x],y,w;i;i=e[i].nxt)
    {
        y=e[i].to,w=e[i].w;
        if(y==fa[x])continue;
        dfs(y,x);val[y]=w;
        siz[x]+=siz[y];
    }ed[x]=cnt;
}
struct Segment_Tree{
    struct Tree{
        int sum,tag;
    }t[N<<2];
    #define ls x<<1
    #define rs x<<1|1
    void add(int x,int k){t[x].sum+=k,t[x].tag+=k;}
    void pushdown(int x)
    {
        if(!t[x].tag)return ;
        add(ls,t[x].tag);add(rs,t[x].tag);
        t[x].tag=0;
    }
    void upd(int x,int l,int r,int L,int R,int k)
    {
        if(L>R)return;
        if(L<=l&&r<=R){add(x,k);return;}
        int mid=l+r>>1;pushdown(x);
        if(L<=mid)upd(ls,l,mid,L,R,k);
        if(mid<R)upd(rs,mid+1,r,L,R,k);
    }
    int query(int x,int l,int r,int pos)
    {
        if(l==r)return t[x].sum;
        int mid=l+r>>1;pushdown(x);
        if(pos<=mid)return query(ls,l,mid,pos);
        return query(rs,mid+1,r,pos);
    }
}T;
int ans[2];
void work()
{
    cin>>n;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=2,x,y,w;i<=n;i++)
    {
        scanf("%lld%lld%lld",&x,&y,&w);
        add(x,y,w);add(y,x,w);
    }
    dfs(1,0);
    for(int u=2,v;u<=n;u++)
    {
        v=fa[u];
        T.upd(1,1,n,st[u],ed[u],(val[u]-a[u])*(n-siz[u]));
        T.upd(1,1,n,1,st[u]-1,(val[u]-a[v])*siz[u]);
        T.upd(1,1,n,ed[u]+1,n,(val[u]-a[v])*siz[u]);
    }
    ans[0]=inf;
    for(int u=n;u;u--)
    {
        int tmp=T.query(1,1,n,u);
        if(ans[0]>tmp){ans[0]=tmp,ans[1]=u;}
    }
    printf("%lld\n%lld",rid[ans[1]],ans[0]);
}
#undef int
int main()
{
    work();
    return 0;
}