
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e6+15,MOD=998244353;
int T,n,m,pw[MN],inv[MN],ans;

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
    if(a<b) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

void initpw(){
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    initpw();
    cin>>T>>n>>m;
    for(int i=0;i<=m;i++){
        (ans+=getC(n,i))%=MOD;
    }
    while(T--){
        int op;
        cin>>op;
        if(op==1){
            ++n;
            ans=0;
            for(int i=0;i<=m;i++){
                (ans+=getC(n,i))%=MOD;
            }
        }else{
            ans=(ans+getC(n,m+1))%MOD;   
            ++m;
        }
        cout<<ans<<'\n';
    }
    

    return 0;
}