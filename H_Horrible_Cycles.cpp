#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200,MOD=998244353;
int n,ans,a[MN],f[MN][MN],pw[MN],inv[MN];

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

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=a[i];j++){
            for(int k=max(0ll,j-a[i]+a[i-1]);k<=j;k++){
                f[i][j]=(f[i][j]+f[i-1][k]*getC(a[i]-a[i-1],j-k)%MOD)%MOD;
            }
        }
        ans=(ans+f[i][1]-a[i]+MOD)%MOD;
        for(int j=0;j<=a[i];j++){
            f[i][j]=(f[i][j]+f[i][j+1]*j%MOD*(j+1))%MOD;
        }
    }
    cout<<(ans*((MOD+1)/2)%MOD);
    

    return 0;
}