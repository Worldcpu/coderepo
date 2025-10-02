#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,K,L[MN],R[MN],mxv;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1

    struct Node{
        int mx,mxcnt;

        Node(int mxx=0,int cntt=0){
            mx=mxx,mxcnt=cntt;
        }

        friend Node operator+(const Node &x,const Node &y){
            Node ret;
            ret.mx=max(x.mx,y.mx);
            if(ret.mx==x.mx) ret.mxcnt+=x.mxcnt;
            if(ret.mx==y.mx) ret.mxcnt+=y.mxcnt;
            return ret;
        }

        friend Node operator+(const Node &x,const int &y){
            Node ret=x;
            ret.mx+=y;
            return ret;
        }

    };

    struct SNode{
        int l,r,add;
        Node val;
    }t[MN*30];
    int tot;

    void pushup(int p){
        t[p].val=t[ls].val+t[rs].val;
    }

    void doadd(int p,int k){
        t[p].val=t[p].val+k;
        t[p].add+=k;
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
            t[p].val=Node(0,1);
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

    Node querymx(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].val;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid<fl) return querymx(rs,fl,fr);
        if(mid>=fr) return querymx(ls,fl,fr);
        return querymx(ls,fl,fr)+querymx(rs,fl,fr);
    }
}sg;

namespace Sub0{

    void solve(){
        for(int i=1;i<=n;i++){

        }
    }
}

namespace Sub1{

    void solve(){

    }

}

namespace Sub2{

    void solve(){
        int ans=1e18;
        for(int i=1;i<=n;i++){
            int l,r;
            cin>>l>>r;
            ans=min(ans,r-l+1);
        }
        cout<<ans;
    }

}

signed main(){
    freopen("vacation.in","r",stdin);
    freopen("vacation.out","w",stdout);
    cin>>n>>K;
    if(K==0){
        Sub0::solve();
    }else if(K==1) Sub1::solve();
    else if(K==1e18) Sub2::solve();
    else{
        // QWQ
    }
    return 0;
}