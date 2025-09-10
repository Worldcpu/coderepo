#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,K,d,a[MN],pw[MN],inv[MN],f[MN],b[MN],ans;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int g(int n,int k){
    if(n<0||k<0) return 0;
    return getC(n-k+1,k);
}

void solve(int n,int m,int k){
    if(m<=0) return;
    if(n<=3){
        if(n==1&&m==1){
            f[k]=1;
        }
        if(n==2&&m==1) f[k]=f[k+1]=1;
        if(n==3&&m==1) f[k]=f[k+1]=f[k+2]=1;
        if(n==3&&m==2) f[k]=f[k+2]=1;
        return;
    }
    b[k-1]=(g(n-3,m-1)+g(n-1,m))*m%MOD*ksm(n,MOD-2)%MOD;
    f[k]=f[n+k-1]=g(n-4,m-2);
    solve(n-4,m-2,k+2);
}

signed main(){
    initpw();
    cin>>n>>K>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    solve(n,K,1);
    for(int i=1;i<=n;i++){
        (b[i]+=b[i-1])%=MOD;
    }
    for(int i=1;i<=n;i++){
        ans=(ans+a[i]*(f[i]+b[min(i-1,n-i)])%MOD)%MOD;
    }
    cout<<ans;
    return 0;
}