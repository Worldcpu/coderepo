#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15;
int n,tot,C,a[MN],b[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn,mx,cov,add1,add2;
    }t[MN<<2];

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void docov(int p,int k){
        t[p].cov=k;
        t[p].mn=t[p].mx=k;
        t[p].add1=t[p].add2=0;
    }

    void doadd1(int p,int k){
        t[p].add1+=k;
        t[p].mn+=1ll*k*b[t[p].l];
        t[p].mx+=1ll*k*b[t[p].r];
    }

    void doadd2(int p,int k){
        t[p].add2+=k;
        t[p].mn+=k;
        t[p].mx+=k;
    }

    void pushdown(int p){
        if(t[p].l==t[p].r) return;
        if(~t[p].cov){
            docov(ls,t[p].cov);
            docov(rs,t[p].cov);
            t[p].cov=-1;
        }
        if(t[p].add1){
            doadd1(ls,t[p].add1);
            doadd1(rs,t[p].add1);
            t[p].add1=0;
        }
        if(t[p].add2){
            doadd2(ls,t[p].add2);
            doadd2(rs,t[p].add2);
            t[p].add2=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].cov=-1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void cover(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            docov(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) cover(ls,fl,fr,k); 
        if(mid<fr) cover(rs,fl,fr,k);
        pushup(p);
    }

    void add1(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd1(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add1(ls,fl,fr,k);
        if(mid<fr) add1(rs,fl,fr,k);
        pushup(p);
    }

    void add2(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd2(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add2(ls,fl,fr,k);
        if(mid<fr) add2(rs,fl,fr,k);
        pushup(p);
    }

    int querymn(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mn;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        int ret=1e18;
        if(mid>=fl) ret=min(ret,querymn(ls,fl,fr));
        if(mid<fr) ret=min(ret,querymn(rs,fl,fr));
        return ret;
    }

    int binary(int p,int k){
        if(t[p].mx<k) return t[p].r+1;
        if(t[p].l==t[p].r) return t[p].l;
        pushdown(p);
        if(t[ls].mx>=k) return binary(ls,k);
        else return binary(rs,k);
    }
}sg;

signed main(){
    cin>>n>>C;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+1+n);
    tot=unique(b+1,b+1+n)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
    }
    sg.build(1,1,tot);
    for(int i=1;i<=n;i++){
        if(a[i]!=1){
            sg.add2(1,1,a[i]-1,C); 
        }
        sg.add2(1,a[i],tot,-b[a[i]]);
        sg.add1(1,a[i],tot,1); 
        int rm=sg.querymn(1,a[i],tot); 
        int pos=sg.binary(1,rm);
        if(pos<a[i]) sg.cover(1,pos,a[i]-1,rm);
    }
    cout<<sg.t[1].mn<<'\n';
    return 0;
}
