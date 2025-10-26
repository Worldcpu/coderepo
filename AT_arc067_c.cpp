#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1520,MP=5e5+15,MOD=1e9+7;
int pw[MP],inv[MP],n,a,b,c,d,f[MN][MN],g[MN][MN];

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
    for(int i=1;i<MP;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MP-1]=ksm(pw[MP-1],MOD-2);
    for(int i=MP-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}


signed main(){
    initpw();
    cin>>n>>a>>b>>c>>d;

    g[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=d;j++){
            if(i<j||i%j!=0) continue;
            int s=i/j;
            g[i][j]=getC(i,s)*g[i-s][j-1]%MOD;
        }
    }

    f[a-1][0]=1;
    for(int i=a;i<=b;i++){
        for(int j=0;j<=n;j++){
            f[i][j]=f[i-1][j];
            for(int k=c;k*i<=j&&k<=d;k++){
                f[i][j]=(f[i][j]+f[i-1][j-k*i]*getC(n-(j-i*k),i*k)%MOD*g[i*k][k]%MOD*inv[k]%MOD)%MOD;
            }
        }   
    }
    cout<<f[b][n];
    return 0;
}