#include<bits/stdc++.h>
using namespace std;
const int MN=2e6+15;
int n,m,q,tot,rt[MN],pre[MN],a[MN];
struct segtree
{
    int val,l,r,lc,rc;
}t[MN<<2];

int root(int x){
    if(pre[x]==x) return x;
    else return pre[x]=root(pre[x]);
}

int build(int l,int r,int k){
    int p=++tot;
    t[p].l=l,t[p].r=r,t[p].val=1;
    if(l==r){
        return p;
    }
    int mid=l+r>>1;
    if(k<=mid){
        t[p].lc=build(l,mid,k);
    }else t[p].rc=build(mid+1,r,k);
    return p;
}

int merge(int x,int y,int l,int r){

    if(!x&&!y){
        return 0;
    }
    if(!x) return y;
    if(!y) return x;
    int p=++tot;
    t[p].l=l,t[p].r=r,t[p].val=t[x].val+t[y].val;
    int mid=l+r>>1;
    t[p].lc=merge(t[x].lc,t[y].lc,l,mid);
    t[p].rc=merge(t[x].rc,t[y].rc,mid+1,r);
    return p;
}

int query(int p,int k){
    if(t[p].val<k) return -1;
    int lv=t[t[p].lc].val;
    if(t[p].l==t[p].r) return a[t[p].l];
    if(k<=lv){
        return query(t[p].lc,k);
    }else return query(t[p].rc,k-lv);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        pre[i]=i;
    }
    for(int i=1;i<=n;i++){
        int p;
        cin>>p;
        a[p]=i;
        rt[i]=build(1,n,p);
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        int ru=root(u),rv=root(v);
        if(ru!=rv){
            pre[ru]=rv;
            rt[rv]=merge(rt[ru],rt[rv],1,n);
        }
    }
    cin>>q;
    while (q--)
    {
        char op;
        int x,y;
        cin>>op>>x>>y;
        if(op=='B'){
            int rx=root(x),ry=root(y);
            if(rx!=ry){
                pre[rx]=ry;
                rt[ry]=merge(rt[rx],rt[ry],1,n);
            }
        }else{
            int rx=root(x);
            cout<<query(rt[rx],y)<<'\n';
        }
    }
    
    return 0;
}