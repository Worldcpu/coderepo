#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5200;
int n,m,MOD,c[MN][MN],a[MN][MN],f[MN],b[MN],s[MN],pw[MN],inv[MN],pwn[MN];

void init(){
    pw[0]=pwn[0]=1;
    for(int i=1;i<=m+1;i++){
        pw[i]=pw[i-1]*i%MOD;
        pwn[i]=pwn[i-1]*(n+1)%MOD;
    }
    inv[1]=1;
    for(int i=2;i<=m+1;i++) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
}

signed main(){
    cin>>n>>m>>MOD;
    init();
    for(int i=0;i<=m+1;i++) a[i][0]=c[i][0]=1;
    for(int i=1;i<=m+1;i++){
        for(int j=1;j<=m+1;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
            a[i][j]=(a[i-1][j]+j*a[i-1][j-1]%MOD)%MOD;
        }
    }
    b[0]=1;
    for(int i=1;i<=m+1;i++){
        for(int j=0;j<i;j++){
            b[i]=(b[i]+c[i+1][j]*b[j]%MOD)%MOD;
        }
        b[i]=(MOD-b[i]*inv[i+1]%MOD)%MOD;
    }
    s[0]=n;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=i;j++){
            s[i]=(s[i]+c[i+1][j]*b[j]%MOD*pwn[i+1-j]%MOD)%MOD;
        }
        s[i]=inv[i+1]*s[i]%MOD;
    }
    f[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=i;j++){
            f[i]=(f[i]+(j&1?1:-1)*a[i-1][j-1]*s[j]%MOD*f[i-j]%MOD+MOD)%MOD;
        }
    }
    cout<<f[m];
    return 0;
}
