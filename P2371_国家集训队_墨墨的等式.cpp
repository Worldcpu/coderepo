#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,m,l,r,ans,a[MN],b[MN],f[MN];


signed main(){
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!a[i]) n--,i--;
    }
    if(!n) cout<<0<<'\n',exit(0);
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    sort(a+1,a+1+n);
    m=a[1];
    for(int i=1;i<=n;i++){
        b[i]=a[i]%m;
    }
    for(int i=2;i<=n;i++){
        for(int j=0,lim=__gcd(a[i],m);j<lim;j++){
            for(int k=j,c=0;c<2;c+=k==j){
                int p=k+b[i];
                if(p>=m) p-=m;
                f[p]=min(f[p],f[k]+a[i]);
                k=p;
            }
        }
    }
    for(int i=0;i<a[1];i++){
        if(r>=f[i]) ans+=max((r-f[i])/a[1]+1,0ll);
        if(l>f[i]) ans-=max((l-1-f[i])/a[1]+1,0ll);
    }
    cout<<ans;
    return 0;
}
