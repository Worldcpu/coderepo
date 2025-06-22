#include<bits/stdc++.h>
using namespace std;
constexpr int MN=3e5+15;
int n,q;

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct Node{
        int k, l, r;

        int f(int x){
            return min(max(x+k, l), r);
        }

        Node operator + (Node b) const
        {
            if(l+b.k>b.r)return {0, b.r, b.r};
            if(b.l>r+b.k)return {0, b.l, b.l};
            return {k+b.k, max(l+b.k, b.l), min(r+b.k, b.r)};
        }
    }e;
    struct{
        int l,r;
        Node val;
    }t[MN<<2];

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r){
            t[p].val=e;
            cin>>t[p].val.k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    Node query(int p,int fl,int fr){
        if(t[p].l>fr||t[p].r<fl) return e;
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].val;
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

}sg;

int main(){
    cin>>n>>sg.e.l>>sg.e.r;
    sg.e.k = 0;
    sg.build(1,1,n);
    cin>>q;
    while(q--){
        int x,y,z;
        cin>>x>>y>>z;
        cout<<sg.query(1,x,y).f(z)<<'\n';
    }
    return 0;
}
