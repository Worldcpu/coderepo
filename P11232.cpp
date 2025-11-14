#include<bits/stdc++.h>
#define int long long
#define pir pair<int,int>
using namespace std;
constexpr int MN=2e6+15;
int n,m,L,V,d[MN],v[MN],a[MN],p[MN],tot,ans1,ans2;
pir qj[MN];

namespace A0{

    void solvea0(int x){
        if(v[x]<=V) return;
        auto it=(*lower_bound(p+1,p+1+m,d[x]));
        qj[++tot]=pir(it,p[m]);
        ans1++;
    }
}

namespace A1{

    bool check(int x,int k){
        int dis=p[k]-d[x];
        int vt=v[x]*v[x]+2*a[x]*dis;
        return vt>V*V;
    }

    void solvea1(int x){
        auto st=lower_bound(p+1,p+1+m,d[x])-p;
        int dis=p[m]-d[x];
        int vt=v[x]*v[x]+2*a[x]*dis;
        if(vt>V*V){
            ans1++;
            int l=st,r=m,ret=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(x,mid)) r=mid-1,ret=mid;
                else l=mid+1;
            }
            qj[++tot]=pir(p[ret],p[m]);
        }

    }
}

namespace A2{

    bool check(int x,int k){
        int dis=p[k]-d[x];
        int vt=v[x]*v[x]+2*a[x]*dis;
        return vt>V*V;
    }

    void solvea2(int x){
        auto it=lower_bound(p+1,p+1+m,d[x])-p;
        int dis=p[it]-d[x];
        int vt=v[x]*v[x]+2*a[x]*dis;
        if(vt>V*V){
            ans1++;
            int l=it,r=m,ret=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(x,mid)) l=mid+1,ret=mid;
                else r=mid-1;
            }
            qj[++tot]=pir(p[it],p[ret]);
        }
    }
}

bool cmp(pir x,pir y){
    if(x.second==y.second ) return x.first<y.first;
    return x.second<y.second;
}

void init(){
    tot=ans1=ans2=0;
}

void solve(){
    cin>>n>>m>>L>>V;
    init();
    for(int i=1;i<=n;i++){
        cin>>d[i]>>v[i]>>a[i];
    }
    for(int i=1;i<=m;i++){
        cin>>p[i];
    }
    for(int i=1;i<=n;i++){
        if(d[i]>p[m]) continue;
        if(a[i]==0) A0::solvea0(i);
        if(a[i]>0) A1::solvea1(i);
        if(a[i]<0) A2::solvea2(i);
    }
    sort(qj+1,qj+1+tot,cmp);
    
    for(int i=1,lst=0;i<=tot;i++){
        if(qj[i].first<=lst&&lst<=qj[i].second) continue;
        lst=qj[i].second;
        ans2++;
    }
    cout<<ans1<<' '<<m-ans2<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}