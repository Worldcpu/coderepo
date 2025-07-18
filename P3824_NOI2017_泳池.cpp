#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2010,MOD=998244353;
int f[MN][MN],ret[MN],a[MN],g[MN],F[MN],ans,n,m,x,y,P;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1){
            ret=1ll*ret*a%MOD;
        }
        a=1ll*a*a%MOD;
        b>>=1;
    }
    return ret;
}

void mul(int *A,int *B,int *C){
    static int res[MN<<1]; 
    memset(res,0,sizeof(res));
    for(int i=0;i<=m;i++)
        for(int j=0;j<=m;j++)
            res[i+j]=(res[i+j]+1ll*A[i]*B[j])%MOD;
    for(int i=2*m;i>m;i--){
        for(int j=m+1;~j;j--)
            res[i-j]=(res[i-j]-1ll*res[i]*a[m+1-j]%MOD+MOD)%MOD; 
    }
    for(int i=0;i<=m;i++) C[i]=res[i]%MOD;
}

int solve(){
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    memset(a,0,sizeof(a));
    memset(F,0,sizeof(F));
    memset(ret,0,sizeof(ret));
    for(int i=0;i<=m+1;i++) f[i][0]=1;
    for(int i=m;i>=1;i--){
        for(int j=1;i*j<=m;j++){
            int RL=1;
            for(int k=1;k<=j;k++){
                RL=1ll*RL*P%MOD;
                f[i][j]=(f[i][j]+1ll*(1-P+MOD)*RL%MOD*f[i+1][k-1]%MOD*f[i][j-k])%MOD;
            }
            f[i][j]=(f[i][j]+1ll*f[i+1][j]*RL)%MOD;
        }
    }
    for(int i=0;i<=m;i++){
        a[i]=(MOD-1ll*f[1][m-i]*(1-P+MOD)%MOD)%MOD;
    }
    a[m+1]=1;
    g[0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<i;j++){
            g[i]=(g[i]+1ll*g[j]*f[1][i-j-1]%MOD*(1-P+MOD))%MOD;
        }
    }
    F[1]=1;
    ret[0]=1;
    int b=n+1;
    if(m==0) F[0]=(MOD-a[0])%MOD,F[1]=0;
    while(b){
        if(b&1) mul(ret,F,ret);
        mul(F,F,F);
        b>>=1;
    }
    ans=0;
    for(int i=0;i<=m;i++){
        ans=(ans+1ll*g[i]*ret[i])%MOD;
    }
    return 1ll*ans*ksm(1-P+MOD,MOD-2)%MOD;
}

int main(){
    cin>>n>>m>>x>>y;
    P=1ll*x*ksm(y,MOD-2)%MOD;
    int w1=solve();
    m--;
    int w2=solve();
    cout<<(w1-w2+MOD)%MOD; 
    return 0;
}
