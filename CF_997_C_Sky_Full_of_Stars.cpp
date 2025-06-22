#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MOD=998244353;
int pw[MN],inv[MN],ans,n;

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
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    init();
    cin>>n;
    int tmp1=0,tmp2=0;
    for(int i=1;i<=n;i++){
        tmp1=(tmp1+(i+1&1?MOD-1:1)*getC(n,i)%MOD*ksm(3,n*(n-i)+i)%MOD+MOD)%MOD;
    }
    ans=tmp1*2%MOD;
    tmp1=0;
    tmp2=ksm(3,MOD-2);
    for(int i=1;i<=n;i++){
        tmp1=(tmp1+(i&1?MOD-1:1)*getC(n,i)%MOD*ksm(tmp2,n*i)%MOD*(ksm((1-ksm(tmp2,n-i)),n)-1)+MOD)%MOD;
    }
    ans=(ans+tmp1*(-ksm(3,n*n+1))%MOD+MOD)%MOD;
    cout<<ans;
    return 0;
}
