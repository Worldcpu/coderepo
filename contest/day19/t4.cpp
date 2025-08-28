#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e7+15;
int pw[MN],inv[MN],MOD,n,m,ans;

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
    for(int i=MN-2;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
}

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void init(){
    ans=0;
}

void solve(){
    cin>>n>>m;
    init();
    for(int i=0;i<=2*n&&(i*(m+1)<=m*n);i++){
        int ret=getC(2*n,i)*getC(n*m-(m+1)*i+2*n-1,2*n-1)%MOD;
        if(i&1) ans=(ans-ret+MOD)%MOD;
        else ans=(ans+ret)%MOD;
    }
    ans=(ksm(m+1,2*n)-ans+MOD)%MOD*ksm(2,MOD-2)%MOD*ksm(ksm(m+1,2*n),MOD-2)%MOD;
    cout<<ans<<'\n';
}

signed main(){
    freopen("pr.in","r",stdin);
    freopen("pr.out","w",stdout);
    cin>>MOD;
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }   


    return 0;
}