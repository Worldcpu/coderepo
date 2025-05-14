#include <algorithm>
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;
constexpr int MN=4e5+15;
struct Node{
    int x,y;
}a[MN];
int n,nowd;
ll ans;

ll getdis(int x,int y){
    return sqrt( (double)(a[x].x-a[y].x) * (a[x].x-a[y].x) + (a[x].y-a[y].y)* (a[x].y-a[y].y) );
}

bool cmpx(int x,int y){
        return a[x].x<a[y].x;
    }

    bool cmpy(int x,int y){
        return a[x].y<a[y].y;
    }

struct KDTree{
#define ls t[p].lson
#define rs t[p].rson
#define pf(x) (1ll*x*x)

    struct{
        int lson,rson,lx,ly,rx,ry;
    }t[MN];
    int id[MN],rt;

    KDTree(){
        for(int i=1;i<MN;i++) id[i]=i;
    }

    void pushup(int p){
        t[p].lx=t[p].rx=a[p].x,t[p].ly=t[p].ry=a[p].y;
        if(t[p].lson){
            t[p].lx=min(t[p].lx,t[ls].lx);
            t[p].rx=max(t[p].rx,t[ls].rx);
            t[p].ly=min(t[p].ly,t[ls].ly);
            t[p].ry=max(t[p].ry,t[ls].ry);
        }
         if(t[p].rson){
            t[p].lx=min(t[p].lx,t[rs].lx);
            t[p].rx=max(t[p].rx,t[rs].rx);
            t[p].ly=min(t[p].ly,t[rs].ly);
            t[p].ry=max(t[p].ry,t[rs].ry);
        }
    }

    int build(int l,int r,bool tp){
        if(r<l) return 0;
        int mid=(l+r)>>1,p;
        if(tp) nth_element(id+l,id+mid,id+r+1,cmpx);
        else nth_element(id+l,id+mid,id+r+1,cmpy);
        p=id[mid];
        t[p].lson=build(l,mid-1,tp^1);
        t[p].rson=build(mid+1,r,tp^1);
        pushup(p);
        return p;
    }

    ll fac(int p){
        if(!p) return INF;
        ll ret=0;
        if(t[p].lx>a[nowd].x) ret+=pf(t[p].lx-a[nowd].x);
        if(t[p].rx<a[nowd].x) ret+=pf(t[p].rx-a[nowd].x);
        if(t[p].ly>a[nowd].y) ret+=pf(t[p].ly-a[nowd].y);
        if(t[p].ry<a[nowd].y) ret+=pf(a[nowd].y-t[p].ry);
        return ret;
    }

    void query(int p){
        if(p!=nowd) ans=min(ans,getdis(nowd,p));
        ll fl=fac(ls);
        ll fr=fac(rs);
        if(fl<fr){
            if(fl<ans){
                query(ls);
            }
            if(fr<ans) query(rs);
        }else{
            if(fr<ans) query(rs);
            if(fl<ans) query(ls);
        }
        
    }

#undef ls
#undef rs
}kdt;

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
    }
    kdt.rt=kdt.build(1, n, 0);
    for(int i=1;i<=n;i++){
        nowd=kdt.id[i];
        kdt.query(kdt.rt);
    }
    cout<<ans;
    return 0;
}
