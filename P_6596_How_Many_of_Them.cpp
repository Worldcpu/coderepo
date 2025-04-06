#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll MOD=1e9+7;
constexpr int MN=55,MM=1515;
int n,m;
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

int main(){
    getinv();
    cin>>n>>m;
    if(m>=n){
        cout<<0;
        return 0;
    }
    for(int i=1;i<=n;i++){
        
    }
    return 0;
}