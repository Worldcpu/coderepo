#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
template<typename type>
inline void read(type &x)
{
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

int n,m;

struct segtree{
    int l,r;
    ll sum;
    bool isok;
}t[MN<<2];
ll a[MN];

void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    if(t[ls].isok&&t[rs].isok) t[p].isok=1;
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    t[p].sum=0;
    t[p].isok=0;
    if(l==r){
        t[p].sum=a[l];
        if(t[p].sum<=1){
            t[p].isok=1;
        }
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void update(int p,int fl,int fr){
    if(t[p].isok) return;
    if(t[p].l==t[p].r){
        t[p].sum=sqrt(t[p].sum);
        if(t[p].sum<=1) t[p].isok=1;
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) update(ls,fl,fr);
    if(mid<fr) update(rs,fl,fr);
    pushup(p);
}

ll query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum;
    }
    ll ret=0;
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) ret+=query(ls,fl,fr);
    if(mid<fr) ret+=query(rs,fl,fr);
    return ret;
}

int main(){
    // ios::sync_with_stdio(0);
    int cnt=0;
    while (~scanf("%d",&n))
    {
        cnt++;
        printf("Case #%d:\n",cnt);
        for(int i=1;i<=n;i++){
            read(a[i]);
        }
        memset(t,0,sizeof(t));
        build(1,1,n);
        read(m);
        int op,x,y;
        while (m--)
        {
            read(op);
            read(x);
            read(y);
            if(x>y) swap(x,y);
            if(op==0) update(1,x,y);
            else printf("%lld\n",query(1,x,y));
        }
        cout<<'\n';
    }
    
    return 0;
}