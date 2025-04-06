#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=4e4,MK=55;
struct segtree{
    int l,r,val,add;
}t[MN<<2];
int f[MK][MN],pre[MN],vis[MN],n,k;

void pushup(int p){
    t[p].val=max(t[ls].val,t[rs].val);
}

void build(int p,int l,int r,int i){
    t[p].l=l;
    t[p].r=r;
    t[p].add=0;
    if(l==r){
        t[p].val=f[i-1][l-1];
        t[p].add=0;
        return;
    }
    int mid=l+r>>1;
    build(ls,l,mid,i);
    build(rs,mid+1,r,i);
    pushup(p);
}

void pushdown(int p){
    if(t[p].add){
        t[ls].add+=t[p].add;
        t[rs].add+=t[p].add;
        t[ls].val+=t[p].add;
        t[rs].val+=t[p].add;
        t[p].add=0;
    }
}

void add(int p,int fl,int fr,int k){
    if(t[p].l>=fl&&t[p].r<=fr){
        t[p].val+=k;
        t[p].add+=k;
        return;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(mid>=fl) add(ls,fl,fr,k);
    if(mid<fr) add(rs,fl,fr,k);
    pushup(p);
}

int query(int p,int fl,int fr){
    if(t[p].l>=fl&&t[p].r<=fr){
        return t[p].val;
    }
    pushdown(p);
    int mid=t[p].l+t[p].r>>1,ret=0;
    if(mid>=fl) ret=max(ret,query(ls,fl,fr));
    if(mid<fr) ret=max(ret,query(rs,fl,fr));
    return ret;
}

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        pre[i]=vis[x]+1;
        vis[x]=i;
    }
    // for(int i=1;i<=n;i++){
    //     cout<<pre[i]<<" ";
    // }
    // cout<<'\n';
    for(int i=1;i<=k;i++){
        build(1,1,n,i);
        for(int j=1;j<=n;j++){
            add(1,pre[j],j,1);
            f[i][j]=query(1,1,j);
        }
    }
    cout<<f[k][n];
    return 0;
}