#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
#define gcd(a,b) __gcd(abs(a),abs(b))
#define pir pair<int,int>
using namespace std;
const int MN=5e5+15;

template<typename type>
void read(type &x){
    x=0;bool flag(0);char ch=getchar();
    while(!isdigit(ch)) flag=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    flag?x=-x:0;
}

struct segtree
{
    int l,r;
    ll sum,d;
}t[MN<<2];

int n,m;
ll a[MN];

void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    t[p].d=gcd(t[ls].d,t[rs].d);
}


void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].d=t[p].sum=a[l]-a[l-1];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void modify(int p,int x,ll k){
    if(t[p].l==t[p].r){
        t[p].sum+=k;
        t[p].d+=k;
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=x) modify(ls,x,k);
    else modify(rs,x,k);
    pushup(p);
}

ll querys(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].sum;
    }
    int mid=t[p].l+t[p].r>>1;
    ll ret=0;
    if(mid>=fl){
        ret+=querys(ls,fl,fr);
    }
    if(mid<fr){
        ret+=querys(rs,fl,fr);
    }
    return ret;
}

ll queryd(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].d;
    }
    ll ret=0;
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        ret=gcd(ret,queryd(ls,fl,fr));
    }
    if(mid<fr){
        ret=gcd(ret,queryd(rs,fl,fr));
    }
    return ret;
}
int main(){
    ios::sync_with_stdio(0);
    read(n);
    read(m);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    char op;
    int l,r;
    ll v;
    build(1,1,n);
    while (m--)
    {
        op=
        if(op=='C'){
            cin>>v;
            modify(1,l,v);
            if(r!=n) modify(1,r+1,-v);
        }else{
            cout<<gcd(queryd(1,l+1,r),querys(1,1,l))<<'\n';
        }
    }
    
    return 0;
}