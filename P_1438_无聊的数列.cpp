#include<iostream>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
struct segtree{
    ll val,k,d;
    int l,r,op;
}t[4*MN];
int n,m;
ll a[MN];
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    // t[p].val=t[ls].val+t[rs].val;
}
void pushdown(int p){
    if(t[p].op){
        t[ls].k+=t[p].k;
        t[ls].d+=t[p].d;
        t[ls].op=t[rs].op=1;
        t[rs].k+=t[p].k+(t[rs].l-t[ls].l)*t[p].d;
        t[rs].d+=t[p].d;
        
    }
    t[p].op=t[p].k=t[p].d=0;
}
void add(int p,int fl,int fr,ll k,ll d){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].op=1;
        t[p].k+=k+(t[p].l-fl)*d;
        t[p].d+=d;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl){
        add(ls,fl,fr,k,d);
    }
    if(mid<fr){
        add(rs,fl,fr,k,d);
    }
    // t[p].val=t[ls].val+t[rs].val;
}
ll query(int p,int k){
    if(t[p].l==t[p].r){
        t[p].val+=t[p].k;
        t[p].k=t[p].d=0;
        return t[p].val;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(k<=mid){
        return query(ls,k);
    }else return query(rs,k);
}    // t[p].val=t[ls].val+t[rs].val;val
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int l,r,op,p;
        ll k,d;
        cin>>op;
        if(op==1){
            cin>>l>>r>>k>>d;
            add(1,l,r,k,d);
        }else{
            cin>>p;
            cout<<query(1,p)<<endl;
        }
    }
    return 0;
}