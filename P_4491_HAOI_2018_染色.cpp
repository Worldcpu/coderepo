#include<bits/stdc++.h>
#include <cmath>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MOD=1004535809,MODG=3,MODGinv=334845270;
int n,m,s,ans,f[MN],g[MN],awa[MN],pw[MN],rev[MN],inv[MN],w[MN];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
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

}

int getG(int x){
    return getC(m,x)*pw[n]%MOD*ksm(inv[s],x)%MOD*inv[n-s*x]%MOD*ksm(m-x,n-s*x)%MOD;
}

signed main(){
    init();
    cin>>n>>m>>s;
    int lim=min(m,n/s);
    for(int i=0;i<=lim;i++){
        f[i]=getG(i)*pw[i]%MOD;
        g[i]=(i&1)?MOD-inv[i]:inv[i];
    }
    reverse(f,f+1+lim);
    int len;
    for(len=1;len<lim*2+2;len<<=1);
    NTT(f,len,1);
    NTT(g,len,1);
    for(int i=0;i<len;i++){
        awa[i]=f[i]*g[i]%MOD;
    }
    NTT(awa,len,-1);
    reverse(awa,awa+lim+1);
    for(int i=0;i<=lim;i++){
        int w;
        cin>>w;
        ans=(ans+awa[i]*inv[i]%MOD*w)%MOD;
    }
    cout<<ans%MOD;
    return 0;
}
