#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int n,m;

struct Segment{
#define ls p<<1
#define rs p<<1|1

    struct Data{
        int sum1,sum2,sum3,sum4,sum5;
        
        Data(int s1=0,int s2=0,int s3=0,int s4=0,int s5=0){
            sum1=s1,sum2=s2,sum3=s3,sum4=s4,sum5=s5;
        }

        friend Data operator+(Data x,Data y){
            Data ret;
            ret.sum1=x.sum1+y.sum1;
            ret.sum2=x.sum2+y.sum2;
            ret.sum3=x.sum3+y.sum3;
            ret.sum4=x.sum4+y.sum4;
            ret.sum5=x.sum5+y.sum5;
            return ret;
        }

    };

    struct Node{
        int l,r,sum1,sum2,sum3,sum4,sum5,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].sum1=t[ls].sum1+t[rs].sum1;
        t[p].sum2=t[ls].sum2+t[rs].sum2;
        t[p].sum3=t[ls].sum3+t[rs].sum3;
        t[p].sum4=t[ls].sum4+t[rs].sum4;
        t[p].sum5=t[ls].sum5+t[rs].sum5;
    }

    void doadd(int p,int k){
        t[p].add+=k;
        t[p].sum1+=(t[p].r-t[p].l+1)*k;
        t[p].sum2+=k*t[p].sum4;
        t[p].sum3+=k*t[p].sum5;
    }

    void pushdown(int p){
        if(t[p].add){
            doadd(ls,t[p].add);
            doadd(rs,t[p].add);
            t[p].add=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].sum4=l;
            t[p].sum5=l*l;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) modify(ls,fl,fr,k);
        if(mid<fr) modify(rs,fl,fr,k);
        pushup(p);
    }

    Data query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return Data(t[p].sum1,t[p].sum2,t[p].sum3,t[p].sum4,t[p].sum5);
        }
        pushdown(p);
        Data ret;
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) ret=ret+query(ls,fl,fr);
        if(mid<fr) ret=ret+query(rs,fl,fr);
        return ret;
    }


#undef ls
#undef rs
}sg;

signed main(){
    cin>>n>>m;
    sg.build(1,1,n);
    while(m--){
        char op;
        int l,r,v;
        cin>>op>>l>>r;
        if(op=='C'){
            cin>>v;
            if(l==r) continue;
            sg.modify(1,l+1,r,v);
        }else{
            auto p=sg.query(1,l+1,r);
            int a=-p.sum3+(l+r+1)*p.sum2+(r-(l+1)-(l+1)*r+1)*p.sum1,b=(r-l+1)*(r-l)/2;
            int gcdd=__gcd(a,b);
            cout<<a/gcdd<<"/"<<b/gcdd<<'\n';
        }
    }
    return 0;
}
