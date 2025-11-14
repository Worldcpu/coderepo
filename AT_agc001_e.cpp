#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=8200,base=2000,MM=1e6+15,MOD=1e9+7;
int f[MN][MN],pw[MN],inv[MN],n,a[MM],b[MM],ans;

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
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        f[base-a[i]][base-b[i]]++;
    }
    for(int i=0;i<=4000;i++){
        for(int j=0;j<=4000;j++){
            if(i){
                f[i][j]=(f[i][j]+f[i-1][j])%MOD;
            }
            if(j){
                f[i][j]=(f[i][j]+f[i][j-1])%MOD;
            }
        }
    }
    for(int i=1;i<=n;i++){
        ans=(ans+f[a[i]+base][b[i]+base])%MOD;
        ans=(ans-getC(2*a[i]+2*b[i],2*a[i])+MOD)%MOD;
    }
    cout<<ans*ksm(2,MOD-2)%MOD;
    return 0;
}