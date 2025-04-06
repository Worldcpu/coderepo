#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=1e5+15;
int n,m;
struct segtree
{
    int l,r,sum;
    double mk;
}t[MN<<2];
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
int query(int p,double maxx){
    if(maxx>=t[p].mk) return 0;
    if(t[p].l==t[p].r){
        return t[p].mk>maxx;
    }
    else if(t[ls].mk<=maxx){
        return query(rs,maxx);
    }else return query(ls,maxx)+t[p].sum-t[ls].sum;
}
void pushup(int p){
    t[p].mk=max(t[ls].mk,t[rs].mk);
    t[p].sum=t[ls].sum+query(rs,t[ls].mk);
}
void change(int p,int pos,double k){
    if(t[p].l==t[p].r){
        t[p].sum=1;
        t[p].mk=k;
        return;
    }
    int mid=t[p].l+t[p].r>>1;
    if(mid>=pos) change(ls,pos,k);
    else change(rs,pos,k);
    pushup(p);
}
int main(){
    cin>>n>>m;
    build(1,1,n);
    int fl,fr;
    while (m--)
    {
        cin>>fl>>fr;
        change(1,fl,(double)fr/fl);
        cout<<t[1].sum<<'\n';
    }
    
    return 0;
}