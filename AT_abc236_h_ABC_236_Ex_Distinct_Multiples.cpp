#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MK=25,MOD=998244353;
int n,m,a[MK],pw[MK],f[1<<16],g[1<<16],c[1<<16];

void init(){
    pw[0]=1;
    for(int i=1;i<MK;i++) pw[i]=pw[i-1]*i%MOD;
}

int lcm(int x,int y){
    return x/__gcd(x,y)*y;
}

signed main(){
    init();
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>a[i];
    f[0]=g[0]=1;
    for(int s=1;s<(1<<n);s++){
        int x=__lg(s&-s),y=s^(s&-s);
        c[s]=c[y]+1;
        (f[s]+=f[y]*(m/a[x]%MOD)%MOD)%=MOD;
        g[s]=!g[y]||a[x]/__gcd(a[x],g[y])>m/g[y]?0:lcm(a[x],g[y]);
        for(int t=y;t;t=(t-1)&y){
            if(!g[t|1<<x]) continue;
            if(c[t]&1) f[s]=(f[s]-f[y^t]*(m/g[t|1<<x]%MOD)%MOD*pw[c[t]]%MOD+MOD)%MOD;
            else f[s]=(f[s]+f[y^t]*(m/g[t|1<<x]%MOD)%MOD*pw[c[t]]%MOD)%MOD;
        }
    }
    cout<<f[(1<<n)-1];
    return 0;
}
