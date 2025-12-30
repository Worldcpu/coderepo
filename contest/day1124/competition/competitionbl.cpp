#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
int n,m,L[MN],R[MN],ans,qjcnt;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val,cov;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void docov(int p,int k){
        if(k==0){
            t[p].val=t[p].cov=k;
        }else{
            t[p].val=(t[p].r-t[p].l+1);
            t[p].cov=k;
        }
    }

    void pushdown(int p){
        if(t[p].cov!=-1){
            docov(ls,t[p].cov);
            docov(rs,t[p].cov);
            t[p].cov=-1;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].cov=-1;
        if(l==r){
            t[p].val=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void cov(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            docov(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) cov(ls,fl,fr,k);
        if(mid<fr) cov(rs,fl,fr,k);
        pushup(p);
    }
}sg;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
    }   
    sg.build(1,1,m);
    for(int i=1;i<=n;i++){
        sg.cov(1,1,m,0);
        for(int j=i;j<=n;j++){
            sg.cov(1,L[j],R[j],1);
            ans=(ans+sg.t[1].val)%MOD;
            qjcnt++;
        }
    }
    ans=ans*ksm(qjcnt,MOD-2)%MOD;
    cout<<ans<<'\n';
    return 0;
}