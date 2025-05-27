#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int q,MOD;

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct{
        int l,r,val;  
    }t[MN<<2];

    void pushup(int p){
        t[p].val=(t[ls].val*t[rs].val)%MOD;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=1;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].val=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int getans(){
        return t[1].val%MOD;
    }

#undef ls
#undef rs
}sg;

signed main(){
    int T;
    cin>>T;
    while(T--){
        cin>>q>>MOD;
        sg.build(1,1,q);
        for(int i=1;i<=q;i++){
            int op,m;
            cin>>op>>m;
            if(op==1){
                sg.modify(1,i,m);
                cout<<sg.getans()<<'\n';
            }else{
                sg.modify(1,m,1);
                cout<<sg.getans()<<'\n';
            }
        }
    }
    return 0;
}
