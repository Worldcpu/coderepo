#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=2000+10,MOD=998244353;
int n,a,b,p,c[N],d[N][N],f[N];

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n>>a>>b;
    p=a*ksm(b,MOD-2)%MOD;
    d[1][0]=d[1][1]=1;
    for(int i=2;i<=n;i++){
        d[i][0]=1;
        for(int j=1;j<=i;j++){
            d[i][j]=(d[i-1][j]*ksm((1-p+MOD)%MOD,j)%MOD+d[i-1][j-1]*ksm(p,i-j)%MOD)%MOD;
        }
    }
    for(int i=1;i<=n;i++){
        int tmp=0;
        for(int j=1;j<i;j++){
            tmp=(tmp+c[j]*d[i][j]%MOD)%MOD;
        }
        c[i]=(1-tmp+MOD)%MOD;
    }
    for(int i=1;i<=n;i++){
        int ret=0;
        for(int j=1;j<i;j++){
            int tmp=(f[j]+f[i-j])%MOD;
            tmp=(tmp+j*(i-j)%MOD)%MOD;
            tmp=(tmp+j*(j-1)%MOD*ksm(2,MOD-2)%MOD)%MOD;
            ret=(ret+c[j]*d[i][j]%MOD*tmp%MOD)%MOD;
        }
        ret=(ret+c[i]*d[i][i]%MOD*(i*(i-1)%MOD*ksm(2,MOD-2)%MOD)%MOD)%MOD;
        f[i]=ret*ksm((1-c[i]*d[i][i]%MOD+MOD)%MOD,MOD-2)%MOD;
    }
    cout<<f[n];
    return 0;
}
