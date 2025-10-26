#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e6+15,MOD=1e9+7;
int n,m,K,f[MN],ans;
int pw[MN],inv[MN];

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
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    cin>>n>>m>>K;
    initpw();
    f[0]=1;
    for(int i=1;i<=m+K;i++){
        f[i]=(2*f[i-1]-getC(i-1,i-K-1)+MOD-getC(i-1,m)+MOD)%MOD;
    }
    for(int i=0;i<=m+K;i++){
        ans=(ans+ksm(3,m+K-i)*getC(i+n-1,n-1)%MOD*f[i]%MOD)%MOD;
    }
    cout<<ans;



    return 0;
}