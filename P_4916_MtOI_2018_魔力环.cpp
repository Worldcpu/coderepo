#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15,MOD=998244353;
int pw[MN],inv[MN],phi[MN],p[MN],invnum[MN],pcnt,n,m,K;
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

void seve(){
    phi[1]=1;
    for(int i=2;i<MN;i++){
        if(!vis[i]) p[++pcnt]=i,phi[i]=i-1;
        for(int j=1;p[j]&&i*p[j]<MN;j++){
            vis[i*p[j]]=1;
            if(!(i%p[j])){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            else phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
}

void init(){
    seve();
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
    invnum[1]=1;
    for(int i=2;i<MN;i++) invnum[i]=(MOD-MOD/i)*invnum[MOD%i]%MOD;
}

int getC(int x,int y){
    if(x<y) return 0;
    return pw[x]*inv[y]%MOD*inv[x-y]%MOD;
}

int f(int m,int n){
    return getC(m+n-1,n-1);
}

int clac(int n,int m,int k){
    if(n==m) return k>=n;
    int ans=0;
    for(int i=0;i<=m/(k+1);i++){
        if(i&1){
            ans=(ans+f(m-i*(k+1),n-m)*(MOD-getC(n-m,i))%MOD)%MOD;
        }else ans=(ans+f(m-i*(k+1),n-m)*getC(n-m,i)%MOD)%MOD;
    }
    return ans*n%MOD*invnum[n-m]%MOD;
}

signed main(){
    init();
    cin>>n>>m>>K;
    int ans=0;
    for(int d=1;d<=n;d++){
        if(n%d==0&&m%d==0){
            ans=(ans+clac(n/d,m/d,K)*phi[d])%MOD;
        }
    }
    cout<<ans*invnum[n]%MOD;
    return 0;
}
