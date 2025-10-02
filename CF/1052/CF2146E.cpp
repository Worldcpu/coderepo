#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN],ans;

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx,tag;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void doadd(int p,int k){
        t[p].mx+=k;
        t[p].tag+=k;
        return;
    }

    void pushdown(int p){
        if(t[p].tag){
            doadd(ls,t[p].tag);
            doadd(rs,t[p].tag);
            t[p].tag=0;
        }
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        t[p].tag=0;
        if(l==r){
            t[p].mx=t[p].tag=0;
            return;
        }
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void add(int p,int fl,int fr,int k){
        if(fl>fr) return;
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

    void modify(int p,int pos,int k){
        if(t[p].l==t[p].r){
            t[p].mx=k;
            return;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) modify(ls,pos,k);
        else modify(rs,pos,k);
        pushup(p);
    }

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mx;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=-1;
        if(mid>=fl) ret=max(ret,query(ls,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }
}sg;

void init(){
    
}

void solve(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sg.build(1,0,n);
    for(int i=1;i<=n;i++){
        sg.add(1,0,a[i]-1,1);
        sg.modify(1,a[i],0);
        cout<<sg.t[1].mx<<' ';
    }
    cout<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}