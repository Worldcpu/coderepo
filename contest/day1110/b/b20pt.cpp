#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int pw[MN],inv[MN],p[MN],n;

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
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    cout<<pw[n]<<'\n';
}

signed main(){
    initpw();
    int T;
    cerr<<__lg(0);
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}