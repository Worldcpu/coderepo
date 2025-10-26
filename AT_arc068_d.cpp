#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=1e9+7;
int n,K;
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
    initpw();
    cin>>n>>K;
    if(n==1){
        cout<<1<<'\n';
        return 0;
    }
    if(K==1){
        cout<<ksm(2,n-2)<<'\n';
        return 0;
    }
    if(n==K){
        cout<<(getC(n+K-3,n-2)-getC(n+K-3,n)+MOD)%MOD;
    }
    else cout<<ksm(2,n-K-1)*(getC(n+K-3,n-2)-getC(n+K-3,n)+MOD)%MOD;

    return 0;
}