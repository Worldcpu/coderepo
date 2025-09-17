#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=150,MOD=998244353,MV=(1ll<<60)-1;
struct Line{
    int l,r;

    friend bool operator<(const Line &x,const Line&y){
        return x.l<y.l;
    }
}a[MN],b[MN],ans[MN*MN*550];
int na,nb,atot,anss;
vector<Line> va[MN],vb[MN];

namespace Segment{
    void updatea(int p,int l,int r,int fl,int fr){
        va[p].push_back({l,r});
        if(l>=fl&&r<=fr) return;
        int mid=(l+r)>>1;
        if(mid>=fl) updatea(p+1,l,mid,fl,fr);
        if(mid<fr) updatea(p+1,mid+1,r,fl,fr);
    }


    void updateb(int p,int l,int r,int fl,int fr){
        if(l>=fl&&r<=fr){
            vb[p].push_back({l,r});
            return;
        }
        int mid=(l+r)>>1;
        if(mid>=fl) updateb(p+1,l,mid,fl,fr);
        if(mid<fr) updateb(p+1,mid+1,r,fl,fr);
    }
}using namespace Segment;

int sum(int x,int y){
    x%=MOD,y%=MOD;
    return ((y-x+1)*(x+y)>>1)%MOD;
}

void solve(){
    for(int i=1;i<=na;i++){
        updatea(0,0,MV,a[i].l,a[i].r);
    }
    for(int i=1;i<=nb;i++){
        updateb(0,0,MV,b[i].l,b[i].r);
    }
    for(int i=1;i<=60;i++){
        for(auto p:va[i]){
            for(auto q:vb[i]){
                int low=p.l^p.r;
                ans[++atot]={(p.l^q.l)&(~low),(p.l^q.l)|low};
            }
        }
    }
}

signed main(){
    cin>>na;
    for(int i=1;i<=na;i++){
        cin>>a[i].l>>a[i].r;
    }
    cin>>nb;
    for(int i=1;i<=nb;i++){
        cin>>b[i].l>>b[i].r;
    }
    solve();
    for(int i=1;i<=60;i++){
        va[i].clear();
        vb[i].clear();
    }
    swap(na,nb);
    swap(a,b);
    solve();
    sort(ans+1,ans+1+atot);
    int L=ans[1].l,R=ans[1].r;
    for(int i=2;i<=atot;i++){
        if(ans[i].l<=R){
            R=max(R,ans[i].r);
        }
        else{
            anss=(anss+sum(L,R)+MOD)%MOD;
            L=ans[i].l,R=ans[i].r;
        }
    }
    anss=(anss+sum(L,R)+MOD)%MOD;
    cout<<anss;

    return 0;
}