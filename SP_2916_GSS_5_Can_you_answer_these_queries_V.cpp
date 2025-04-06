#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
struct segtree
{
    int l,r;
    ll sum,msum,ml,mr;
}t[MN<<2];

ll a[MN];
int T,n,m;

segtree merge(segtree x,segtree y){
    segtree ret;
    ret.sum=x.sum+y.sum;
    ret.ml=max(x.ml,x.sum+y.ml);
    ret.mr=max(y.mr,y.sum+x.mr);
    ret.msum=max({x.msum,y.msum,x.mr+y.ml});
    return ret;
}

void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    t[p].ml=max(t[ls].ml,t[ls].sum+t[rs].ml);
    t[p].mr=max(t[rs].mr,t[rs].sum+t[ls].mr);
    t[p].msum=max({t[ls].msum,t[rs].msum,t[ls].mr+t[rs].ml});
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].ml=t[p].mr=t[p].msum=t[p].sum=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

segtree querymax(int p,int fl,int fr){
    if(fl>fr) return (segtree){0,0,0,0,0,0};
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p];
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fr) return querymax(ls,fl,fr);
    else if(mid<fl) return querymax(rs,fl,fr);
    else{
        return merge(querymax(ls,fl,mid),querymax(rs,mid+1,fr));
    }
}

ll query(int l1,int r1,int l2,int r2){
    if(r1<l2){
        return querymax(1,l1,r1).mr+querymax(1,r1+1,l2-1).sum+querymax(1,l2,r2).ml;
    }
    ll ans=querymax(1,l2,r1).msum;
    if(l1<l2) ans=max(ans,querymax(1,l1,l2).mr+querymax(1,l2,r2).ml-a[l2]);
    if(r1<r2) ans=max(ans,querymax(1,l1,r1).mr+querymax(1,r1,r2).ml-a[r1]);
    return ans;
}

int main(){
    cin>>T;
    while (T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        build(1,1,n);
        cin>>m;
        int l1,r1,l2,r2;
        while (m--)
        {
            cin>>l1>>r1>>l2>>r2;
            cout<<query(l1,r1,l2,r2)<<'\n';
        }
        
    }
    
    return 0;
}