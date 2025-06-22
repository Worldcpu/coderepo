#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=1e5+3;
int n,K,tot,pw[MN],f[MN],inv[MN],a[MN];

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
    inv[1]=1;
    for(int i=2;i<MN;i++) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
}

signed main(){
    init();
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=n;i>=1;i--){
        if(a[i]){
            ++tot;
            for(int j=1;j*j<=i;j++){
                if(i%j==0){
                    a[j]^=1;
                    if(j*j!=i) a[i/j]^=1;
                }
            }
        }
    }
    for(int i=n;i>=1;i--){
        f[i]=((n-i)*f[i+1]%MOD+n)%MOD*inv[i]%MOD;
    }
    int ans=0;
    if(tot<=K) ans=tot;
    else{
        for(int i=tot;i>K;i--){
            (ans+=f[i])%=MOD;
        }
        (ans+=K)%=MOD;
    }
    cout<<ans*pw[n]%MOD;
    return 0;
}
