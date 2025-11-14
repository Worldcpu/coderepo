#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e7+15,MOD=998244353;
int n,m,pw[MN],inv[MN],sum[MN],ans;

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

signed main(){
    initpw();
    cin>>n>>m;
    sum[0]=1;
    for(int i=1;i<=m;i++){
        sum[i]=(sum[i-1]+getC(n+i-1,n-1))%MOD;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            if(j+n-1+i>m) break;
            ans=(ans+getC(n-1,j)*sum[(m-j-n+1-i)/3]%MOD)%MOD;
        }
    }
    cout<<ans;
    return 0;
}