#include<bits/stdc++.h>
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
struct segtree
{
    int l,r;
    bool docover;
    int ans,hans;
    int sum,mxsum,cov,mxcov;
}t[4*MN];
int n,q,a[MN];

void pushup(int p){
    t[p].ans=max(t[ls].ans,t[rs].ans);
    t[p].hans=max(t[ls].hans,t[rs].hans);
}

void dosum(int p,int k,int maxk){
    if(t[p].docover){
        t[p].mxcov=max(t[p].mxcov,t[p].cov+maxk);
        t[p].hans=max(t[p].hans,t[p].ans+maxk);
        t[p].ans+=k;
        t[p].cov+=k;
    }else{
        t[p].mxsum=max(t[p].mxsum,t[p].sum+maxk);
        t[p].hans=max(t[p].hans,t[p].ans+maxk);
        t[p].ans+=k;
        t[p].sum+=k;
    }
}

void docov(int p,int k,int maxk){
    if(t[p].docover){
        t[p].mxcov=max(t[p].mxcov,maxk);
        t[p].hans=max(t[p].hans,maxk);
    }else{
        t[p].docover=1;
        t[p].mxcov=maxk;
        t[p].hans=max(t[p].hans,maxk);
    }
    t[p].ans=t[p].cov=k;
}

void pushdown(int p){
    dosum(ls,t[p].sum,t[p].mxsum);
    dosum(rs,t[p].sum,t[p].mxsum);
    t[p].sum=t[p].mxsum=0;

    if(t[p].docover){
        docov(ls,t[p].cov,t[p].mxcov);
        docov(rs,t[p].cov,t[p].mxcov);
        t[p].cov=t[p].mxcov=t[p].docover=0;
    }
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].hans=t[p].ans=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

int query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].ans;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1,res=-1e9;
    if(mid>=fl){
        res=query(ls,fl,fr);
    }
    if(mid<fr){
        res=max(res,query(rs,fl,fr));
    }
    return res;
}

int queryhis(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].hans;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    int res=-1e9;
    if(mid>=fl){
        res=queryhis(ls,fl,fr);
    }
    if(mid<fr){
        res=max(res,queryhis(rs,fl,fr));
    }
    return res;
}

void add(int p,int fl,int fr,int k){
    if(t[p].l>=fl&&t[p].r<=fr){
        dosum(p,k,k);
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        add(ls,fl,fr,k);
    }
    if(mid<fr){
        add(rs,fl,fr,k);
    }
    pushup(p);
}

void cover(int p,int fl,int fr,int k){
    if(t[p].l>=fl&&t[p].r<=fr){
        docov(p,k,k);
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        cover(ls,fl,fr,k);
    }
    if(mid<fr){
        cover(rs,fl,fr,k);
    }
    pushup(p);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    cin>>q;
    char op;
    int x,y,z;
    while (q--)
    {
        cin>>op>>x>>y;
        if(op=='Q'){
            cout<<query(1,x,y)<<'\n';
        }
        if(op=='A'){
            cout<<queryhis(1,x,y)<<'\n';
        }
        if(op=='P'){
            cin>>z;
            add(1,x,y,z);
        }
        if(op=='C'){
            cin>>z;
            cover(1,x,y,z);
        }
    }
    
    return 0;
}