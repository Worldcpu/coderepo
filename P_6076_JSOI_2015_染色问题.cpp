#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=1e9+7;
int ans,pwc[MN],pw[MN],inv[MN],n,m,c;

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
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

int getC(int x,int y){
    if(x<y) return 0;
    return pw[x]*inv[y]%MOD*inv[x-y]%MOD;
}

signed main(){
    init();
    cin>>n>>m>>c;
    for(int k=0;k<=c;k++){
        pwc[0]=1;
        for(int i=1;i<=n*m;i++) pwc[i]=(pwc[i-1]*(c-k+1)%MOD);
        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                (ans+=((i+j+k&1)?MOD-1:1)*getC(n,i)%MOD*getC(m,j)%MOD*getC(c,k)%MOD*pwc[(n-i)*(m-j)]%MOD)%=MOD;
            }
        }
    }
    cout<<ans;
    return 0;
}
