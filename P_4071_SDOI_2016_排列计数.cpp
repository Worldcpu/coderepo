#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int T,n,m,jc[MN],inv[MN],f[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void init(){
    jc[0]=1;
    for(int i=1;i<MN;i++){
        jc[i]=jc[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(jc[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
    f[1]=0,f[2]=1;
    for(int i=3;i<MN;i++) f[i]=(i-1)*(f[i-1]+f[i-2])%MOD;
}

int getc(int n,int m){
    if(n<m) return 0;
    return jc[n]*ksm(jc[m],MOD-2)%MOD*ksm(jc[n-m],MOD-2)%MOD;
}

int lucas(int n,int m){
    if(n<m) return 0;
    if(!n) return 1;
    return lucas(n/MOD,m/MOD)*getc(n%MOD,m%MOD)%MOD;
}

void solve(){
    int n,m;
    cin>>n>>m;
    if(n==m) cout<<1<<'\n';
    else if(n-m==1) cout<<0<<'\n';
    else if(m==0) cout<<f[n]<<'\n';
    else cout<<(f[n-m]%MOD*lucas(n,m)%MOD)%MOD<<'\n';
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
