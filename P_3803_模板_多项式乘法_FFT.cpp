#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353,MODG=3,MODGinv=332748118;
int f[MN],g[MN],rev[MN],ans[MN],len,n,m;

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
}

signed main(){
    cin>>n>>m;
    for(int i=0;i<=n;i++){
        cin>>f[i];
        f[i]=(f[i]+MOD)%MOD;
    }
    for(int i=0;i<=m;i++){
        cin>>g[i];
        g[i]=(g[i]+MOD)%MOD;
    }
    len=1;
    while(len<=n+m){
        len<<=1;
    }
    NTT(f,len,1);
    NTT(g,len,1);
    for(int i=0;i<=len;i++) ans[i]=f[i]*g[i];
    NTT(ans,len,-1);
    int inv=ksm(len,MOD-2);
    for(int i=0;i<=n+m;i++){
        cout<<ans[i]*inv%MOD<<" ";
    }
    return 0;
}
