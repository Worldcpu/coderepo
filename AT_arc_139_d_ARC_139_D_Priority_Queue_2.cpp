#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15,MOD=998244353;
int pw[MN],inv[MN],ans,n,m,K,x,a[MN];

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
    if(a<b||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    initpw();
    cin>>n>>m>>K>>x;
    x=n-x+1;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        a[v]++;
    }
    for(int i=m;i>=1;i--){
        a[i]+=a[i+1];
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<=K;j++){
            if(a[i]<=x){
                ans=(ans+min(x,a[i]+j)*getC(K,j)%MOD*ksm(m-i+1,j)%MOD*ksm(i-1,K-j)%MOD)%MOD;
            }else ans=(ans+max(x,a[i]+j-K)*getC(K,j)%MOD*ksm(m-i+1,j)%MOD*ksm(i-1,K-j)%MOD)%MOD;
        }
    }
    cout<<ans;
    return 0;
}