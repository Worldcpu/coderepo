#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=55,ML=1e4+5,MOD=1e9+7;
int n,l,r[MN],f[MN][MN][ML],pw[ML],inv[ML];

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
    for(int i=1;i<ML;i++) pw[i]=pw[i-1]*i%MOD;
    inv[ML-1]=ksm(pw[ML-1],MOD-2);
    for(int i=ML-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    init();
    cin>>n>>l;
    for(int i=1;i<=n;i++){
        cin>>r[i];
    }
    sort(r+1,r+1+n);
    f[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int k=1;k<=l;k++){
                f[i][j][k]=f[i-1][j-1][k-1];
                if(k>=r[i]) f[i][j][k]=(f[i][j][k]+f[i-1][j][k-r[i]]*2*j%MOD)%MOD;
                if(k>=2*r[i]-1){
                    f[i][j][k]=(f[i][j][k]+f[i-1][j+1][k-2*r[i]+1]*j%MOD*(j+1)%MOD)%MOD;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=l;i++){
        ans=(ans+f[n][1][i]*getC(l-i+n,n)%MOD)%MOD;
    }
    cout<<ans%MOD;
    return 0;
}
