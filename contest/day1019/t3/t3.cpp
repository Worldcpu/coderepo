#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4e6+15;
int pw[MN],inv[MN],MOD,n,f[MN][3],pw2[MN];

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
    pw2[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
        pw2[i]=(pw2[i-1]+pw2[i-1])%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    cin>>n>>MOD;
    initpw();
    f[1][1]=getC(n,1);
    f[2][2]=getC(n,2);
    for(int i=1;i<n;i++){
        if(i+1<=n&&i>=1){
            f[i+1][1]=(f[i+1][1]+f[i][1]*pw2[i-1]%MOD*getC(n-i,1)%MOD)%MOD;
        }
        if(i+2<=n&&i>=1){
            f[i+2][2]=(f[i+2][2]+f[i][1]*pw2[2*(i-1)]%MOD*getC(n-i,2)%MOD)%MOD;
        }
        if(i+1<=n&&i>=2){
            f[i+1][1]=(f[i+1][1]+f[i][2]*pw2[i-2]%MOD*getC(n-i,1)%MOD)%MOD;
        }
        if(i+2<=n&&i>=2){
            f[i+2][2]=(f[i+2][2]+f[i][2]*pw2[2*(i-2)]%MOD*getC(n-i,2)%MOD)%MOD;
        }
    }
    cout<<(f[n][1]+f[n][2])%MOD;
    return 0;
}