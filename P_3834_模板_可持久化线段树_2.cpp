#include<bits/stdc++.h>
using namespace std;
const int MN=2e5+15;
struct segtree
{
    int val,l,r;
}t[MN<<5];
int n,m,root[MN],a[MN],b[MN],tot;
int newnode(int p){
    t[++tot]=t[p];
    return tot;
}
void build(int &p,int l,int r){
    p=++tot;
    if(l==r) return;
    int mid=l+r>>1;
    build(t[p].l,l,mid);
    build(t[p].r,mid+1,r);
}
int update(int p,int l,int r,int k){
    int cp=newnode(p);
    t[cp].val+=1;
    if(l==r){
        return cp;
    }
    int mid=l+r>>1;
    if(k<=mid){
        t[cp].l=update(t[p].l,l,mid,k);
    }else t[cp].r=update(t[p].r,mid+1,r,k);
    return cp;
}
int query(int u,int v,int l,int r,int k){
    if(l==r){
        return b[l];
    }
    int bj=t[t[v].l].val-t[t[u].l].val;
    int mid=l+r>>1;
    if(k<=bj){
        return query(t[u].l,t[v].l,l,mid,k);
    }else return query(t[u].r,t[v].r,mid+1,r,k-bj);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    int q=unique(b+1,b+1+n)-b-1;
    build(root[0],1,q);
    for(int i=1;i<=n;i++){
        int x=lower_bound(b+1,b+1+q,a[i])-b;
        root[i]=update(root[i-1],1,q,x);
    }
    while (m--)
    {
        int l,r,k;
        cin>>l>>r>>k;
        cout<<query(root[l-1],root[r],1,q,k)<<'\n';
    }
    
    return 0;
}