#include<bits/stdc++.h>
#define pir pair<int,int>
using namespace std;
constexpr int MN=5e5+15,INF=1e9;
int n,m,ans,L=-INF,R=INF;
pir a[MN];
vector<int> qry[MN];

struct Segment{
    #define ls p<<1
    #define rs p<<1|1
    struct Node{
        int l,r,mx,add;
    }t[MN<<2];

    void pushup(int p){
        t[p].mx=max(t[ls].mx,t[rs].mx);
    }

    void doadd(int p,int k){
        t[p].add+=k;
        t[p].mx+=k;
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
        t[p].add=0;
        if(l==r){
            t[p].mx=l;
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

    int query(int p,int fl,int fr){
        if(t[p].l>=fl&&t[p].r<=fr){
            return t[p].mx;
        }
        pushdown(p);
        int mid=(t[p].l+t[p].r)>>1,ret=0;
        if(mid>=fl) ret=max(ret,query(ls,fl,fr));
        if(mid<fr) ret=max(ret,query(rs,fl,fr));
        return ret;
    }
}sg;

bool cmp(pir x,pir y){
    if(x.first==y.first) return x.second>y.second;
    return x.first<y.first;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].first>>a[i].second;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        L=max(L,a[i].first);
        R=min(R,a[i].second);
    }
    ans=n-(L<R?R-L+1:0);
    sg.build(1,0,m+1);
    for(int i=1;i<=n;i++){
        int now=sg.query(1,a[i].first+1,a[i].second);
        ans=max(ans,now-a[i].first);
        sg.add(1,0,a[i].second,1);
    }
    cout<<(ans>m?ans-m:0);
    return 0;
}