#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=4090,MOD=1e9+9;
int n,K,ans,fc[MN],f[MN][MN],a[MN],b[MN],c[MN];

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
    fc[0]=1;
    for(int i=1;i<MN;i++){
        fc[i]=fc[i-1]*i%MOD;
    }
}

int getC(int a,int b){
    return fc[a]*ksm(fc[b],MOD-2)%MOD*ksm(fc[a-b],MOD-2)%MOD;
}

signed main(){
    init();
    cin>>n>>K;
    K=(n+K)/2;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);
    for(int i=1,p=1;i<=n;i++){
        while(p<=n&&b[p]<a[i]){
            p++;
        }
        c[i]=(p-1);
    }
    for(int i=0;i<=n;i++) f[i][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            f[i][j]=(f[i][j]+f[i-1][j-1]*max(c[i]-j+1,0ll)%MOD+f[i-1][j])%MOD;
        }
    }
    for(int i=K;i<=n;i++){
        int tmp=f[n][i]*fc[n-i]%MOD; 
        ans=(ans+tmp*getC(i,K)*((i-K)&1?-1:1)%MOD)%MOD;
    }
    cout<<(ans+MOD)%MOD;
    return 0;
}
