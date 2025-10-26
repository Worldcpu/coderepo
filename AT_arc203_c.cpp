#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MOD=998244353,MN=5e5+15;;
int pw[MN],inv[MN],n,m,K;

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
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i%MOD;
    }
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void solve(){
    cin>>n>>m>>K;
    if(K<n+m-2){
        cout<<"0\n";
    }
    else if(K==n+m-2){
        cout<<getC(n+m-2,n-1)<<'\n';
    }else if(K==n+m-1){
        cout<<getC(n+m-2,n-1)*(n*(m-1)%MOD+m*(n-1)%MOD-(n+m-2)+MOD)%MOD<<'\n';
    }else{
            int ans = getC(n + m - 2, n - 1) * ((n * (m - 1) + m * (n - 1) - n - m + 2) % MOD) % MOD * ((n * (m - 1) + m * (n - 1) - n - m + 1) % MOD) % MOD * (MOD + 1) / 2 % MOD;
            ans = (ans - getC(n + m - 4, n - 2) * (n + m - 3) % MOD + MOD) % MOD;
            ans = (ans + (n - 1) * getC(n + m - 2, m - 3) % MOD + (m - 1) * getC(n + m - 2, n - 3) % MOD) % MOD;
            cout << ans << '\n';
    }
}

signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}