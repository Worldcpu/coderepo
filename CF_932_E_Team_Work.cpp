#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e3+15,MOD=1e9+7,MODG=3,MODGinv=55924054;
int n,K,pw[MN],s[MN][MN],ans,inv[MN];

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
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
    s[0][0]=1;
    for(int i=1;i<MN;i++){
        for(int j=1;j<=i;j++){
            s[i][j]=(s[i-1][j-1]+s[i-1][j]*j%MOD)%MOD;
        }
    }
}

signed main(){
    init();
    cin>>n>>K;
    int lag=1,p2=ksm(2,n),inv2=ksm(2,MOD-2);
    for(int i=0;i<=min(n,K);i++){
        ans=(ans+lag*s[K][i]%MOD*p2%MOD)%MOD;
        lag=lag*(n-i)%MOD;
        p2=p2*inv2%MOD;
    }
    if(!K) ans--;
    cout<<ans;
    return 0;
}