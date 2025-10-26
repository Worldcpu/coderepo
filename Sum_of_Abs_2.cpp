#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,INF=1e18;
int n,L,a[MN],f[MN],maxx;

signed main(){
    cin>>n>>L;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    maxx=*max_element(a+1,a+1+n);
    for(int i=1;i<=maxx;i++){
        f[i]=INF;
        for(int j=1;j*(L-j)<=i&&j<=(L>>1);j++){
            f[i]=min(f[i],f[i-j*(L-j)]+1);
        }
    }
    for(int i=1;i<=n;i++){
        if(f[a[i]]<INF) cout<<f[a[i]]<<'\n';
        else cout<<-1<<'\n';
    }
    return 0;
}