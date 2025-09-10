#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,a,b,L[MN],R[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,val,tag;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=(t[ls].val+t[rs].val)%MOD;
    }

    void domul(int p,int k){
        t[p].val=t[p].val*k%MOD;
        t[p].tag=t[p].tag*k%MOD;
    }

    void pushdown(int p){
        if(t[p].tag!=1){
            domul(ls,t[p].tag);
            domul(rs,t[p].tag);
            t[p].tag=1;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].tag=1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            domul(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    void change(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) change(ls,pos,k);
        else change(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) (ret+=query(ls,fl,fr))%=MOD;
        if(mid<fr) (ret+=query(rs,fl,fr))%=MOD;
        return ret;
    }
}sg;


signed main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>L[i]>>R[i];
    }
    sg.build(1,1,n+a);
    int ql=n+1,qr=n+a;
    sg.change(1,n+1,1);
    for(int i=1;i<=n;i++){
        int sum=sg.query(1,ql,qr);
        ql--,qr--;
        int val=max(0ll,R[i]-max(b,L[i]-1));
        if(ql+1<=qr){
            sg.modify(1,ql+1,qr,val);
        }
        val=max(0ll,min(b,R[i])-L[i]+1)*sum%MOD;
        sg.change(1,ql,val);
    }
    cout<<sg.query(1,ql,qr)<<'\n';
    return 0;
}