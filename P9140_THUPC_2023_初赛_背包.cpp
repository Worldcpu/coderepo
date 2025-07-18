#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
int f[MN],n,q,mv[MN],md[MN],v[MN],d[MN],c[MN],w,m=1;


signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>v[i]>>c[i];
        if(w*v[i]<c[i]*m) w=c[i],m=v[i];
    }
    for(int i=1;i<=n;i++){
        mv[i]=v[i]%m;
        md[i]=v[i]/m;
    }
    for(int i=1;i<m;i++){
        f[i]=-1e18;
    }
    for(int i=1;i<=n;i++){
        for(int j=0,lim=__gcd(v[i],m);j<lim;j++){
            for(int k=j,cy=0;cy<2;cy+=k==j){
                int p=k+mv[i],d=md[i];
                if(p>=m) p-=m,d++;
                f[p]=max(f[p],f[k]+c[i]-d*w);
                k=p;
            }
        }
    }
    for(int i=1;i<=q;i++){
        int V;
        cin>>V;
        int p=V%m;
        if(f[p]<-1e17) cout<<-1<<'\n';
        else cout<<f[p]+V/m*w<<'\n';
    }
    
    return 0;
}
