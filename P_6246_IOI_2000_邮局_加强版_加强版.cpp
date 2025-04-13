#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=5e5+15;
struct queueueue{
    int l,r,j;
}q[MN];
int n,m,ql,qr;
ll pos[MN],sump[MN],ans[MN];
ll f[MN];

ll w(int l,int r){
    int p=(l+r+1)>>1;
    return (sump[r]-sump[p])-(ll)pos[p]*(r-p)+(ll)pos[p]*(p-l)-(sump[p]-sump[l]);
}

void insert(int x){
    int pos=n+1;
    while(ql<=qr&&f[x]+w(x,q[qr].l)<=f[q[qr].j]+w(q[qr].j,q[qr].l)) pos=q[qr--].l;
    if(ql<=qr&&f[x]+w(x,q[qr].r)<=f[q[qr].j]+w(q[qr].j,q[qr].r)){
        int l=q[qr].l,r=q[qr].r;
        while(l+1<r){
            int mid=(l+r)>>1;
            if(f[x]+w(x,mid)<=f[q[qr].j]+w(q[qr].j,mid)) r=mid;
            else l=mid;
        }
        q[qr].r=r-1;
        pos=r;
    }
    if(pos!=n+1){
        q[++qr]={pos,n,x};
    }
}

bool check(ll k){
    ql=1,qr=0;
    q[++qr]={1,n,0};
    for(int i=1;i<=n;i++){
        while(ql<=qr&&q[ql].r<i) ql++;
        f[i]=f[q[ql].j]+w(q[ql].j,i)+k;
        ans[i]=ans[q[ql].j]+1;
        insert(i);
    }
    // cout<<ans[n]<<" ";
    return ans[n]>=m;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>pos[i];
    }
    sort(pos+1,pos+1+n);
    for(int i=1;i<=n;i++){
        sump[i]=sump[i-1]+pos[i];
    }
    ll l=0,r=1e18;
    while(l+1<r){
        ll mid=(l+r)>>1;
        if(check(mid)) l=mid;
        else r=mid;
    }
    check(l);
    cout<<f[n]-m*l;
    return 0;
}