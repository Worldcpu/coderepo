#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,pw[MN],inv[MN],lim[MN],a[MN],f[MN];

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
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int getA(int a,int b){
    return getC(a,b)*pw[b]%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    lim[0]=-1;
    for(int i=1,j=0;i<=n;i++){
        while((a[j+1]<<1)<=a[i]) j++;
        lim[i]=j;
    }
    if(lim[n]!=n-1){
        cout<<0;
        return 0;
    }
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=lim[i];j++){
            f[i]=(f[i]+f[j]*getA(n-lim[j]-2,lim[i]-lim[j]-1)%MOD)%MOD;
        }
    }
    cout<<f[n];
    return 0;
}
