#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2520,MOD=998244353;
int n,K,ans,L[MN],R[MN],pw[MN],inv[MN];
int f[2][MN][MN],sum[2][MN][MN];

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
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

signed main(){
    initpw();
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        L[i]=max(0ll,x-K);
        R[i]=min(i,K+x);
    }
    f[0][0][0]=sum[0][0][0]=1;
    for(int i=1,now=0;i<=n;i++){
        now^=1;
        for(int j=0;j<=i;j++){
            for(int k=L[i];k<=min(R[i],j);k++){
                f[now][j][k]=(f[now][j][k]+f[now^1][j][k]*j%MOD)%MOD;
                if(j) (f[now][j][k]+=f[now^1][j-1][k])%=MOD;
                if(j&&k) (f[now][j][k]+=sum[now^1][j-1][min(k-1,R[i-1])]*inv[j-k]%MOD)%=MOD;
                (sum[now][j][k]+=f[now][j][k]*pw[j-k]%MOD)%=MOD;
                if(k) (sum[now][j][k]+=sum[now][j][k-1])%=MOD;
            }
        }
        for(int j=0;j<i;j++){
            for(int k=L[i-1];k<=R[i-1];k++){
                f[now^1][j][k]=sum[now^1][j][k]=0;
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=L[n];j<=min(i,R[n]);j++){
            (ans+=f[n&1][i][j]*pw[n-j]%MOD*inv[n-i]%MOD)%=MOD;
        }
    }
    cout<<ans;
    return 0;
}