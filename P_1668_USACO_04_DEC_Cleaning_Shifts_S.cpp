#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e6+15,INF=1e9+7;
struct node{
    int l,r;
}a[MN];
struct segtree{
    int l,r;
    int val;
}t[MN<<2];
int n,T,ans=INF;

bool cmp(node x,node y){
    if(x.r==y.r) return x.l<y.l;
    return x.r<y.r;
}

void pushup(int p){
    t[p].val=min(t[ls].val,t[rs].val);
}

void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r){
        t[p].val=INF;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}

void update(int p,int pos,int k){
    if(t[p].l==t[p].r){
        t[p].val=min(t[p].val,k);
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=pos){
        update(ls,pos,k);
    }else update(rs,pos,k);
    pushup(p);
}

int query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].val;
    }
    int mid=t[p].l+t[p].r>>1;
    int res=INF;
    if(mid>=fl) res=query(ls,fl,fr);
    if(mid<fr) res=min(res,query(rs,fl,fr));
    return res;
}

int main(){
    cin>>n>>T;
    build(1,1,T);
    for(int i=1;i<=n;i++){
        cin>>a[i].l>>a[i].r;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(a[i].l==1){
            update(1,a[i].r,1);
            if(a[i].r==T){
                cout<<1;
                return 0;
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(a[i].l>1){
            int tmp=query(1,max(1,a[i].l-1),max(1,a[i].r-1));
            update(1,a[i].r,tmp+1);
            if(a[i].r==T){
                ans=min(ans,tmp+1);
            }
        }
    }
    if(ans>=INF) cout<<-1;
    else cout<<ans;
    return 0;
}