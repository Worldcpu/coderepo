#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e6+15,MOD=998244353;
int K,n,m,ans;

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
    if(a<b||a<0||b<0) return 0;
    int ret=1;
    for(int i=a;i>=a-b+1;i--) ret=(__int128)ret*i%MOD;
    for(int i=1;i<=b;i++){
        ret=ret*ksm(i,MOD-2)%MOD;
    }
    return ret;
}

signed main(){
    cin>>n>>m>>K;
    if(m%K!=0){
        cout<<0;
        return 0;
    }
    for(int i=0;i<=n-K+1;i++){
        ans=(ans+getC(n-K+1,i)*getC(m/K-i*K+2*n-K,2*n-K)%MOD*((i&1)?-1:1)+MOD)%MOD;
    }   
    cout<<ans;
    return 0;
}