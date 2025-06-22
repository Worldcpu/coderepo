#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1520,MOD=1e9+7;
int n,m,ans,a[MN],pw[MN],inv[MN];

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
    for(int i=MN-2;i>=0;i--){
        inv[i]=(i+1)*inv[i+1]%MOD;
    }
}

int getC(int x,int y){
    if(x<y) return 0;
    return pw[x]*inv[y]%MOD*inv[x-y]%MOD;
}

signed main(){
    init();
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i];
    for(int i=0;i<n;i++){
        int ret=getC(n,i);
        for(int j=1;j<=m;j++){
            ret=ret*getC(a[j]+n-i-1,n-i-1)%MOD;
        }
        if(i&1) ans=(ans-ret+MOD)%MOD;
        else ans=(ans+ret)%MOD;
    }
    cout<<ans;
    return 0;
}
