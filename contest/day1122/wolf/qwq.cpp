#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=3e7+15,MOD=998244353;
int pw[MN],inv[MN],n,x,y,z,ans;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*(a)%MOD;
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

int getF(int n){
    if((n+x+y)&1) return 0;
    if(n<x+y) return 0;
    int t=(x+y+n)/2;
    return getC(n,t)*getC(n,t-x)%MOD;
}


signed main(){
    init();
    cin>>n>>x>>y>>z;
    x=abs(x);
    y=abs(y);
    z=abs(z);
    if(n<abs(x)+abs(y)+abs(z)||(n-x-y-z)&1){
        cout<<0;
        return 0;
    }
    for(int i=z;i<=n;i++){
        if((z-i)%2) continue;
        int ret=getF(n-i);
        ret=ret*getC(i,(i+z)/2)%MOD;
        ret=ret*getC(n,i)%MOD;
        (ans+=ret)%=MOD;
    }
    cout<<ans;
    return 0;
}
