#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15,MOD=998244353;
int pw[MN],inv[MN],ans,r,g,b,K;

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
    cin>>r>>g>>b>>K;
    for(int i=K;i<=min(r,g);i++){
        (ans+=((i-K&1)?MOD-1:1)*getC(i,K)%MOD*getC(r+g+b-i,i)%MOD*getC(r+g+b-2*i,r-i)%MOD*getC(g+b-i,g-i)%MOD)%=MOD;
    }
    cout<<ans;
    return 0;
}
