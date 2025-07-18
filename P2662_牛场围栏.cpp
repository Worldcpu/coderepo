#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15;
constexpr int INF=1e18;
int f[MN],a[MN],b[MN],tot,n,m,ans,mod;



signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    mod=max(1ll,a[1]-m);
    if(mod==1){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;i++){
        int lst=max(a[i-1]+1,a[i]-m);
        for(int j=lst;j<=a[i];j++){
            if(j!=mod){
                b[++tot]=j;
            }
        }
    }
    sort(b+1,b+1+tot);
    tot=unique(b+1,b+1+tot)-b-1;
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=tot;i++){
        for(int j=0,lim=__gcd(b[i],mod);j<lim;j++){
            for(int cur=j,c=0;c<2;c+=cur==j){
                int nxt=(cur+b[i])%mod;
                f[nxt]=min(f[nxt],f[cur]+b[i]);
                cur=nxt;
            }
        }
    }
    for(int i=0;i<mod;i++){
        if(f[i]>=0x3f3f3f3f3f3f3f3f){
            cout<<-1;
            return 0;
        }
        ans=max(ans,f[i]-mod);
    }
    cout<<ans;
    return 0;
}
