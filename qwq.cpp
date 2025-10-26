#include<bits/stdc++.h>
#define ll long long
#define int long long
const int N=1e5+5;
const ll inf=1e17;
using namespace std;
struct Segment_Tree{
    struct Tree{
        int cnt;ll sum;
    }t[N<<2];
    #define ls x<<1
    #define rs x<<1|1
    void insert(int x,int l,int r,int pos)
    {
        t[x].cnt++,t[x].sum+=pos;
        if(l==r)return;int mid=l+r>>1;
        if(pos<=mid)insert(ls,l,mid,pos);
        else insert(rs,mid+1,r,pos);
    }
    int query_cnt(int x,int l,int r,int L,int R)
    {
        if(R<L)return 0;
        if(L<=l&&r<=R)return t[x].cnt;
        int mid=l+r>>1,res=0;
        if(L<=mid)res+=query_cnt(ls,l,mid,L,R);
        if(mid<R)res+=query_cnt(rs,mid+1,r,L,R);
        return res;
    }
    ll query_sum(int x,int l,int r,int L,int R)
    {
        if(R<L)return 0;
        if(L<=l&&r<=R)return t[x].sum;
        int mid=l+r>>1;ll res=0;
        if(L<=mid)res+=query_sum(ls,l,mid,L,R);
        if(mid<R)res+=query_sum(rs,mid+1,r,L,R);
        return res;
    }
}Tx,Ty;
struct task{
    int x,y;
    bool operator <(const task &t)const{
        return x==t.x ? y<t.y : x<t.x;
    }
}q[N];
int n,m,z;
ll ans[3],val;
ll calc(int x,int y)
{
    int sum=0,cnt=0,tmp=0;
    // x:
    cnt=Tx.query_cnt(1,1,n,1,x);tmp=Tx.query_sum(1,1,n,1,x);//[1,x]
    sum+=-tmp+1ll*x*cnt;
    cnt=Tx.query_cnt(1,1,n,x+1,n);tmp=Tx.query_sum(1,1,n,x+1,n);//(x,n]
    sum+=-1ll*x*cnt+tmp;
    //y:
    cnt=Ty.query_cnt(1,1,n,1,y);tmp=Ty.query_sum(1,1,n,1,y);
    sum+=-tmp+1ll*y*cnt;
    cnt=Ty.query_cnt(1,1,n,y+1,n);tmp=Ty.query_sum(1,1,n,y+1,n);
    sum+=-1ll*y*cnt+tmp;
    return sum;
}
int a[N],b[N];
void work()
{
    cin>>n>>m>>z;
    ans[0]=inf;
    ll xx=0,yy=0;
    for(int i=1,w;i<=m;i++)
    {
        scanf("%lld%lld%lld",&q[i].x,&q[i].y,&w);val+=w;
        Tx.insert(1,1,n,q[i].x);
        Ty.insert(1,1,n,q[i].y);
        a[i]=q[i].x,b[i]=q[i].y;
    }
    sort(a+1,a+1+m);sort(b+1,b+1+m);
    xx=a[m>>1],yy=b[m>>1];
    for(int i=-500;i<=500;i++)for(int j=-500;j<=500;j++)
    if(1<=xx+i&&xx+i<=n&&1<=yy+j&&yy+j<=n)
    {
        ll tmp=calc(xx+i,yy+j);
        if(ans[0]>tmp)
        {
            ans[0]=tmp;ans[1]=xx+i,ans[2]=yy+j;
        }
    }
    ans[0]=1ll*ans[0];
    printf("%lld\n%lld %lld",ans[0]+val,ans[1],ans[2]);
}
#undef int
int main()
{
    freopen("shuru.in","r",stdin);freopen("shuru.out","w",stdout);
    work();
    return 0;
}
