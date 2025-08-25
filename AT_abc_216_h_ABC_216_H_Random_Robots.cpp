#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2520,MOD=998244353;
int pw[MN+15],inv[MN+15],K,n,f[MN+15][MN+15],x[MN];

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
    if(a<b||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(int MN){
    pw[0]=1;
    for(int i=1;i<=MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN]=ksm(pw[MN],MOD-2);
    for(int i=MN-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

signed main(){
    initpw(MN+5);
    cin>>K>>n;
    for(int i=1;i<=K;i++){
        cin>>x[i];
        ++x[i];
    }
    f[0][0]=1;
    for(int i=1;i<=MN;i++){
        for(int s=0;s<(1<<K);s++){
            if(!f[i-1][s]) continue;
            (f[i][s]+=f[i-1][s])%=MOD;
            int cnt=0;
            for(int j=1;j<=K;j++){
                if(!((s>>(j-1))&1)){
                    int tmp=f[i-1][s]*getC(n,i-x[j])%MOD;
                    if(tmp){
                        (f[i][s^(1<<(j-1))]+=(cnt?MOD-tmp:tmp))%=MOD;
                    }
                    cnt^=1;
                }
            }
        }
    }
    cout<<(f[MN][(1<<K)-1]*ksm(ksm(2,n*K),MOD-2)%MOD);
    return 0;
}