#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=1e6+5,INF=1e9,MOD=1e9+7;
struct DPNode{
    int f,g;

    DPNode(int x=-INF,int y=0){
        f=x,g=y;
    }

    friend DPNode operator+(DPNode x,DPNode y){
        if(x.f!=y.f) return (x.f>y.f?x:y);
        return DPNode(x.f,(x.g+y.g)%MOD);
    }

}f[MN];
int n,L[MN],R[MN];
vector<pir> pos[MN];

struct Segment{
#define ls p<<1
#define rs p<<1|1
    struct Node{
        int l,r;
        DPNode v;
    }t[MN<<2];

    void pushup(int p){
        t[p].v=t[ls].v+t[rs].v;
    }

    void build(int p,int l,int r){
        t[p].l=l;
        t[p].r=r;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }

    void update(int p,int pos,DPNode k){
        if(t[p].l==t[p].r){
            t[p].v=k;
            return;
        }
        int mid=(t[p].l+t[p].r)>>1;
        if(mid>=pos) update(ls,pos,k);
        else update(rs,pos,k);
        pushup(p);
    }

    DPNode query(int p,int fl,int fr){
        if(t[p].l>fr||t[p].r<fl) return DPNode();
        if(t[p].l>=fl&&t[p].r<=fr) return t[p].v;
        return query(ls,fl,fr)+query(rs,fl,fr);
    }

#undef ls
#undef rs
}sg;

void solve(int l,int r){
    if(l==r) return;
    int mid=(l+r)>>1;
    solve(l,mid);
    for(int i=mid,mx=L[mid+1],mn=R[mid+1];i>=l&&mx<=mn;i--){
        if(i+mx<=r&&i+mn>=mid+1){
            pos[max(i+mx,mid+1)].push_back(pir(i,1));
            pos[min(i+mn,r)+1].push_back(pir(i,-1));
        }
        mn=min(mn,R[i]);
        mx=max(mx,L[i]);
    }
    for(int i=mid+1,mx=0,mn=INF;i<=r;i++){
        for(auto p:pos[i]){
            sg.update(1,p.first,(p.second==1?DPNode(f[p.first].f+1,f[p.first].g):DPNode()));
        }
        mx=max(mx,L[i]);
        mn=min(mn,R[i]);
        if(mx<=mn) f[i]=f[i]+sg.query(1,max(i-mn,l),min(i-mx,mid));
    }
    for(auto p:pos[r+1]) sg.update(1,p.first,DPNode());
    for(int i=l;i<=r+1;i++) pos[i].clear();
    solve(mid+1,r);
}

signed main(){
    cin>>n;
    for(int i=1,mx=0,mn=INF;i<=n;i++){
        cin>>L[i]>>R[i];
        mx=max(mx,L[i]);
        mn=min(mn,R[i]);
        if(mx<=i&&i<=mn) f[i]=DPNode(1,1);
    }
    sg.build(1,1,n);
    solve(1,n);
    if(f[n].f<=0){
        cout<<"NIE";
    }else cout<<f[n].f<<" "<<f[n].g;
    return 0;
}
