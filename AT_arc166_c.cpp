#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MOD=998244353;
int h,w,f[MN],g[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    } 
    return ret;
}

void solve(){
    cin>>h>>w;
    if(h>w) swap(h,w);
    cout<<(g[2*h-1]*g[2*h-1]%MOD*ksm(f[2*h],w-h)%MOD)<<'\n';
}

void init(){
    f[1]=g[1]=2;
    f[2]=3,g[2]=6;
    for(int i=3;i<MN;i++){
        f[i]=(f[i-1]+f[i-2])%MOD;
        g[i]=g[i-2]*f[i]%MOD;
    }
}

signed main(){
    init();
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}