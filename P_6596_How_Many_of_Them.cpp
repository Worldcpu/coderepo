#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll MOD=1e9+7;
constexpr ll MN=57,MM=2515;
ll n,m;
ll inv[MM],jc[MM],f[MN][MM],g[MN][MM][MN],h[MN];

ll ksm(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1){
            ret=ret*a%MOD;
        }
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

void getinv(){
    jc[0]=1;
    for(int i=1;i<=1500;i++){
        jc[i]=(i*jc[i-1])%MOD;
    }
    inv[1500]=ksm(jc[1500],MOD-2);
    for(int i=1500-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

ll getC(ll a,ll b){
    return jc[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void geth(){
    h[1]=1;
    for(int i=2;i<=n;i++){
        h[i]=ksm(2,i*(i-1)/2);
        for(int j=1;j<i;j++){
            h[i]=(h[i]-h[j]*getC(i-1,j-1)%MOD*ksm(2,(i-j)*(i-j-1)/2)%MOD)%MOD;
        }
        h[i]=(h[i]+MOD)%MOD;
    }
}

int main(){
    getinv();
    cin>>n>>m;
    geth();
    g[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            for(int k=1;k<i;k++){
                ll tmp=0;
                for(int x=1;x<=min(i-k,j);x++){
                    tmp=(tmp+g[i-k][x][j-x]%MOD*ksm(k,x)%MOD)%MOD;
                }
                f[i][j]=(f[i][j]+f[k][0]*getC(i-1,k-1)%MOD*tmp)%MOD;
            }
        }

        f[i][0]=h[i];
        for(int j=1;j<i;j++){
            f[i][0]=((f[i][0]-f[i][j])%MOD+MOD)%MOD;
        }

        for(int j=1;j<=i;j++){
            for(int k=0;k<i;k++){
                for(int p=1;p<=i;p++){
                    for(int q=0;q<=k;q++){
                        g[i][j][k]=(g[i][j][k]+f[p][q]*p%MOD*getC(i-1,p-1)%MOD*g[i-p][j-1][k-q])%MOD;
                    }
                }
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=min(n,m);i++){
        ans=(ans+f[n][i])%MOD;
    }
    cout<<ans;
    return 0;
}

//公式如下
//https://www.latexlive.com/#JTVDYmVnaW4lN0JhbGlnbiU3RCUwQWgoaSkmPSUyMFAxMDk4MiUwQSUwQSU1QyU1QyUwQSUwQWYoaSxqKSY9JTVDc3VtJTIwJTVDbGltaXRzJTIwXyU3Qms9MSU3RCU1RSU3QmktMSU3RGYoaywwKSU1Q3RpbWVzJTVDYmVnaW4lN0JwbWF0cml4JTdEJTBBaS0xJTIwJTVDJTVDJTIway0xJTBBJTBBJTVDZW5kJTdCcG1hdHJpeCU3RCUwQSU1Q3RpbWVzJTBBJTVDc3VtJTVDbGltaXRzXyU3Qng9MSU3RCU1RSU3QiU1Q21pbiUyMChpLWssaiklN0QlMjBnKGktayxqLXgseCkqayU1RXglMEElMEElNUMlNUMlMEFmKGssMCkmPWgoayktJTVDc3VtJTVDbGltaXRzJTIwXyU3Qmo9MSU3RCU1RSU3QmstMSU3RGYoaiwwKSUwQSUwQSU1QyU1Q2coaSxqLGspJj0lNUNzdW0lNUNsaW1pdHNfJTdCcD0xJTdEJTVFJTdCaS0xJTdEJTVDc3VtJTIwJTVDbGltaXRzJTIwXyU3QnE9MSU3RCU1RSU3QmslN0RmKHAscSkqcColNUNiZWdpbiU3QnBtYXRyaXglN0QlMEFpLTElMjAlNUMlNUMlMjBwLTElMEElMEElNUNlbmQlN0JwbWF0cml4JTdEJTBBJTBBKmcoaS1wLHEtMSxrLXEpJTBBJTBBJTVDZW5kJTdCYWxpZ24lN0Q=