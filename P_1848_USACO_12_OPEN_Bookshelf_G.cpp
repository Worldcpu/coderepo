#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define ll long long
using namespace std;
constexpr int MN=1e5+15;
template<typename type>
inline void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    flag?x=-x:0;
}
int n,L,w[MN],h[MN],s[MN],pre[MN],top;
ll f[MN];
struct segtree
{
    int l,r;
    ll f,sum,maxx;
}t[MN<<2];

void pushup(int p){
    t[p].sum=min(t[ls].sum,t[rs].sum);
    t[p].f=min(t[ls].f,t[rs].f);
}

void pushdown(int p){
    if(t[p].maxx){
        t[ls].maxx=t[rs].maxx=t[p].maxx;        
        t[ls].sum=t[ls].f+t[p].maxx;
        t[rs].sum=t[rs].f+t[p].maxx;
        t[p].maxx=0;
    }
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

ll querysum(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum;
    }
    pushdown(p);
    ll ret=1e10;
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) ret=min(querysum(ls,fl,fr),ret);
    if(mid<fr) ret=min(querysum(rs,fl,fr),ret);
    return ret;
}

void insertf(int p,int x,ll val){
    if(t[p].l==t[p].r){
        t[p].f=t[p].sum=val;
        // t[p].sum=t[p].f+t[p].maxx;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=x) insertf(ls,x,val);
    else insertf(rs,x,val);
    pushup(p);
}

void update(int p,int fl,int fr,ll k){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].maxx=k;
        t[p].sum=t[p].f+k;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) update(ls,fl,fr,k);
    if(mid<fr) update(rs,fl,fr,k);
    pushup(p);
}
int main(){
    read(n);
    read(L);
    for(int i=1;i<=n;i++){
        read(h[i]);
        read(w[i]);
    }
    for(int i=2;i<=n;i++){
        w[i]+=w[i-1];
    }
    for(int i=1;i<=n;i++){
        while (top&&h[i]>h[s[top]]){
            top--;
        }
        if(top){
            pre[i]=s[top];
        }else pre[i]=1;
        s[++top]=i;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<pre[i]<<" ";
    // }
    // cout<<'\n';
    build(1,1,n);
    int last=0,mn=0;
    for(int i=1;i<=n;i++){
        mn=max(mn,h[i]);
        while (w[i]-w[last]>L)
        {
            last++;
        }
        update(1,pre[i],i-1,h[i]);
        if(last==0){
            f[i]=querysum(1,last+1,i-1);
            f[i]=min(f[i],(ll)mn);
        }else f[i]=querysum(1,last,i-1);
        insertf(1,i,f[i]);
    }
    cout<<f[n];
    return 0;
}