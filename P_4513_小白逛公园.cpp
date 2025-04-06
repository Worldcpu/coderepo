#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=5e5+15;
int n,m;
struct segtree
{
    int l,r;
    ll sum,msum,ml,mr;
}t[MN<<2];
void pushup(int p){
    t[p].sum=t[ls].sum+t[rs].sum;
    t[p].ml=max(t[ls].ml,t[ls].sum+t[rs].ml);
    t[p].mr=max(t[rs].mr,t[rs].sum+t[ls].mr);
    t[p].msum=max({t[ls].msum,t[rs].msum,t[ls].mr+t[rs].ml});
}
ll a[MN];
void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].sum=t[p].msum=t[p].ml=t[p].mr=a[l];
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void update(int p,int pos,int k){
    if(t[p].l==t[p].r){
        t[p].msum=t[p].ml=t[p].mr=t[p].sum=k;
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=pos) update(ls,pos,k);
    else update(rs,pos,k);
    pushup(p);
}
segtree query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p];
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fr) return query(ls,fl,fr);
    else{
        if(mid<fl)return query(rs,fl,fr);
        else{
            segtree tls=query(ls,fl,fr),trs=query(rs,fl,fr),ans;
            ans.sum=tls.sum+trs.sum;
            ans.ml=max(tls.ml,tls.sum+trs.ml);
            ans.mr=max(trs.mr,trs.sum+tls.mr);
            ans.msum=max({tls.msum,trs.msum,tls.mr+trs.ml});
            return ans;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int op,x,y;
    build(1,1,n);
    while (m--)
    {
        cin>>op>>x>>y;
        if(op==1){
            if(x>y) swap(x,y);
            cout<<query(1,x,y).msum<<'\n';
        }else update(1,x,y);
    }
    
    return 0;
}