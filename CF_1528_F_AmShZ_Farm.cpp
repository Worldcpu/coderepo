#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353,MODG=3,MODGinv=332748118;
int n,K,ans,pw[MN],inv[MN],st[MN],Btmp[MN];

namespace Poly{
    int rev[MN];

    int ksm(int a,int b){
        int ret=1;
        while(b>0){
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

}using namespace Poly;

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}


signed main(){
    init();
    cin>>n>>K;
    for(int i=0;i<=K;i++){
        st[i]=(i&1?MOD-inv[i]:inv[i]);
        Btmp[i]=Poly::ksm(i,K)*inv[i]%MOD;
    }
    Poly::Mul(st,Btmp,K,K);
    for(int i=1,C=1;i<=K;i++){
        C=C*(n-i+1)%MOD*ksm(i,MOD-2)%MOD;
        ans=(ans+C*st[i]%MOD*pw[i]%MOD*Poly::ksm(n+1,n-i)%MOD)%MOD;
    }
    cout<<ans;
    return 0;
}
