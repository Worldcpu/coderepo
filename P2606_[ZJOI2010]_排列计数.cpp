#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15;
int n,MOD,jc[MN],inv[MN],siz[MN],f[MN];

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

signed main(){
    cin>>n>>MOD;
    init();
    for(int i=1;i<=n;i++){
        siz[i]=1;
    }
    for(int i=n;i>=2;i--){
        siz[i>>1]+=siz[i];
    }
    for(int i=n+1;i<=2*n+1;i++){
        f[i]=1;
    }
    for(int i=n;i>=1;i--){
        f[i]=lucas(siz[i]-1,siz[i*2])*f[i*2]%MOD*f[i*2+1]%MOD;
    }
    cout<<f[1];
    return 0;
}
