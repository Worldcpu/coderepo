#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+5;
int a[MN],n,q;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mn,mx,sum,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mn=min(t[ls].mn,t[rs].mn);
        t[p].mx=max(t[ls].mx,t[rs].mx);
        t[p].sum=t[ls].sum+t[rs].sum;
    }

    void doadd(int p,int k){
        t[p].mn+=k;
        t[p].mx+=k;
        t[p].sum+=(t[p].r-t[p].l+1)*k;
        t[p].add+=k;
        return;
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
            t[p].mn=t[p].mx=a[l];
            t[p].sum=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(t[p].l>=fl&&t[p].r<=fr){
            doadd(p,k);
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) add(ls,fl,fr,k);
        if(mid<fr) add(rs,fl,fr,k);
        pushup(p);
    }

    void dosqrt(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            int c1=sqrt(t[p].mn),c2=sqrt(t[p].mx);
            if(t[p].mn==t[p].mx){
                doadd(p,-(t[p].mn-c1));
                return;
            }
            else if(t[p].mn+1==t[p].mx&&c1+1==c2){
                doadd(p,-(t[p].mn-c1));
                return;
            }
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=fl) dosqrt(ls,fl,fr);
        if(mid<fr) dosqrt(rs,fl,fr);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].sum;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;;
        if(mid>=fl) ret+=query(ls,fl,fr);
        if(mid<fr) ret+=query(rs,fl,fr);
        return ret;
    }
}sg;


signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sg.build(1,1,1e6);
    while(q--){
        int op,x,y,z;
        cin>>op>>x>>y;
        if(op==1){
            cin>>z;
            sg.add(1,x,y,z);
        }
        if(op==2){
            sg.dosqrt(1,x,y);
        }
        if(op==3){
            cout<<sg.query(1,x,y)<<'\n';
        }
    }

    return 0;
}