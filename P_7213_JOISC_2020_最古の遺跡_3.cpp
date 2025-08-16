#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e3+15,MOD=1e9+7,INV2=500000004;
int n,m,cnt0,cnt1,a[MN],pw[MN],inv[MN],g[MN][MN],f[MN][MN];
bool vis[MN];

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
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>n;
    m=n<<1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        vis[a[i]]=1;
    }
    for(int i=0;i<=n;i++){
        g[i][0]=1;
        for(int j=1;j<=i;j++){
            g[i][j]=(g[i-1][j]+g[i-1][j-1]*2%MOD*j%MOD)%MOD;
            if(j>1) g[i][j]=(g[i][j]+j*(j-1)%MOD*g[i-1][j-2]%MOD)%MOD;
        }
    }
    f[m+1][0]=1;
    for(int i=m;i>=1;i--){
        if(vis[i]){
            cnt1++;
            for(int j=0;j<=cnt1;j++){
                f[i][j]=(f[i][j]+f[i+1][j])%MOD;
                for(int k=1;k<=cnt1-j;k++){
                    f[i][j+k]=(f[i][j+k]+f[i+1][j]*getC(cnt1-j-1,k-1)%MOD*g[k-1][k-1]%MOD*(k+1)%MOD)%MOD;
                }
            }
        }else{
            cnt0++;
            for(int j=0;j<=cnt1;j++){
                f[i][j]=(f[i][j]+f[i+1][j]*(j-cnt0+1)%MOD)%MOD;
            }
        }
    }
    for(int i=1;i<=n;i++) f[1][n]=f[1][n]*INV2%MOD;
    cout<<f[1][n];

    return 0;
}