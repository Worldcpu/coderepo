#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=6e6+16,MOD=998244353,G=3,INVG=332748118;
int n,pw[MN],inv[MN],invnum[MN],A[MN],B[MN],pw2[MN];

namespace Poly{
    
    int rev[MN];

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
            int Wn=ksm((op==1?G:INVG),(MOD-1)/(i<<1));
            for(int j=0;j<len;j+=(i<<1)){
                int w=1;
                for(int k=0;k<i;k++,w=(w*Wn)%MOD){
                    int x=f[j+k],y=w*f[j+k+i]%MOD;
                    f[j+k]=(x+y)%MOD;
                    f[j+k+i]=(x-y+MOD)%MOD;
                }
            }
        }
        if(op==-1){
            int invlen=ksm(len,MOD-2);
            for(int i=0;i<len;i++) f[i]=f[i]*invlen%MOD;
        }
    }

    // f is the output array
    void Mul(int f[],int g[],int n,int m){
        m+=n;
        n=1;
        while(n<=m) n<<=1;
        NTT(f,n,1);
        NTT(g,n,1);
        for(int i=0;i<=n;i++) f[i]=f[i]*g[i]%MOD;
        NTT(f,n,-1);
    }
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*(i)%MOD;
    inv[MN-1]=Poly::ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
    pw2[0]=1;
    for(int i=1;i<MN;i++) pw2[i]=(pw2[i-1]*2)%MOD;
    invnum[1]=1;
    for(int i=2;i<MN;i++) invnum[i]=(MOD-MOD/i)*invnum[MOD%i]%MOD;  
}


signed main(){
    init();
    cin>>n;
    A[0]=B[0]=1;
    A[1]=MOD-1,B[1]=n+1;
    for(int i=2;i<=n;i++){
        A[i]=(i&1?MOD-inv[i]:inv[i]);
        B[i]=(Poly::ksm(i,n+1)-1+MOD)%MOD*invnum[i-1]%MOD*inv[i]%MOD;
    }
    Poly::Mul(A,B,n,n);
    int ans=0;
    for(int i=0;i<=n;i++){
        (ans+=(Poly::ksm(2,i))*pw[i]%MOD*A[i]%MOD)%=MOD;
    }
    cout<<ans;
    return 0;
}
