#include<bits/stdc++.h>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const ll MN=1e6+15,INF=1e18,M=1e6;
struct line{
    ll k,b;
}ln[MN];
struct node{
    int l,r,id;
}t[MN<<2];
ll f[MN],h[MN],s[MN];
int n;

ll clac(int id,int x){
    return ln[id].k*x+ln[id].b;
}


void build(int p,int l,int r){
    t[p].l=l;
    t[p].r=r;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
}

void update(int p,int i){
        if(t[p].l==t[p].r){
            if(clac(i,t[p].l)<clac(t[p].id,t[p].l)) t[p].id=i;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(clac(i,mid)<clac(t[p].id,mid)){
            swap(i,t[p].id);
        }
        if(clac(i,t[p].l)<clac(t[p].id,t[p].l)){
            update(ls,i);
        }
        if(clac(i,t[p].r)<clac(t[p].id,t[p].r)){
            update(rs,i);
        }
        return;
}

ll query(int p,ll k){
    ll ret=0;
    ret=clac(t[p].id,k);
    if(t[p].l==t[p].r) return ret;
    int mid=(t[p].l+t[p].r)>>1;
    if(mid>=k) ret=min(ret,query(ls,k));
    else ret=min(ret,query(rs,k));
    return ret;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=1;i<=n;i++){
        cin>>s[i];
        s[i]+=s[i-1];
    }
    ln[0].b=INF;
    build(1,0,M);
    ln[1].k=-2*h[1];
    ln[1].b=h[1]*h[1]-s[1];
    update(1,1);
    for(int i=2;i<=n;i++){
        f[i]=query(1,h[i])+s[i-1]+h[i]*h[i];
        ln[i].k=-2*h[i];
        ln[i].b=f[i]-s[i]+h[i]*h[i];
        update(1,i);
    }
    cout<<f[n];
    return 0;
}