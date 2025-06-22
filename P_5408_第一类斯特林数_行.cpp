#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e5+15,MOD=167772161,MODG=3,MODGinv=55924054;
int n,rev[MN],inv[MN],pw[MN],f[MN],g[MN],a[MN],b[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void dorev(int f[],int len){
    for(int i=0;i<len;i++){
        rev[i]=rev[i>>1]>>1;
        if(i&1){
            rev[i]|=len>>1;
        }
    }
    for(int i=0;i<len;i++){
        if(i<rev[i]) swap(f[i],f[rev[i]]);
    }
}

void NTT(int f[],int len,int op){
    dorev(f,len);
    for(int i=1;i<len;i<<=1){
        int Wn=ksm((op==1?MODG:MODGinv),(MOD-1)/(i<<1));
        for(int j=0;j<len;j+=(i<<1)){
            int w=1;
            for(int k=0;k<i;k++,w=(w*Wn)%MOD){
                int x=f[j+k],y=w*f[j+k+i]%MOD;
                f[j+k]=(x+y)%MOD;
                f[j+k+i]=(x-y+MOD)%MOD;
            }
        }
    }
if (op == -1) {
    int inv_len = ksm(len, MOD-2);
    for (int i = 0; i < len; i++) 
        f[i] = f[i] * inv_len % MOD;
}
}

void Mul(int f[],int g[],int n,int m){
    m+=n,n=1;
    while(n<m) n<<=1;
    NTT(f,n,1);
    NTT(g,n,1);
    for(int i=0;i<n;i++) f[i]=f[i]*g[i]%MOD;
    NTT(f,n,-1);
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

void solve(int f[],int n){
    if(n==1){
        f[1]=1;
        return;
    }
    if(n&1){
        solve(f,n-1);
        for(int i=n;i>=1;i--){
            f[i]=(f[i-1]+f[i]*(n-1)%MOD)%MOD;
        }
        f[0]=f[0]*(n-1)%MOD;
    }else{
        int m=n/2,ret=1;
        solve(f,m);
        for(int i=0;i<=m;i++){
            a[i]=f[i]*pw[i]%MOD;
            b[i]=ret*inv[i]%MOD;
            ret=ret*m%MOD;
        }
        reverse(a,a+1+m);
        Mul(a,b,m+1,m+1);
        for(int i=0;i<=m;i++){
            g[i]=inv[i]*a[m-i]%MOD;
        }
        Mul(f,g,m+1,m+1);
        int lim=1;
        while(lim<(m+1)<<1) lim<<=1;
        for(int i=m+1;i<lim;i++) a[i]=b[i]=g[i]=0;
        for(int i=n+1;i<lim;i++) f[i]=0;
    }
}

signed main(){
    init();
    cin>>n;
    solve(f,n);
    for(int i=0;i<=n;i++) cout<<f[i]<<" ";
    return 0;
}
