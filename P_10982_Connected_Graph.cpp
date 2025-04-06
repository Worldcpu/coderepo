#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN=2048,MINV=1e5+15;
constexpr ll MOD=1004535809;
int n;
ll f[MN],inv[MINV],jc[MINV];

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

void getjc(){
    jc[0]=1;
    for(int i=1;i<=1e5;i++){
        jc[i]=(i*jc[i-1])%MOD;
    }

    inv[100000]=ksm(jc[100000],MOD-2);
    for(int i=1e5-1;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%MOD;
    }
}

ll getC(ll a,ll b){
    return jc[a]*inv[b]%MOD*inv[a-b]%MOD;
}

int main(){
    getjc();
    cin>>n;
    f[1]=1;
    for(int i=2;i<=n;i++){
        f[i]=ksm(2,i*(i-1)/2);
        for(int j=1;j<i;j++){
            f[i]=(f[i]-f[j]*getC(i-1,j-1)%MOD*ksm(2,(i-j)*(i-j-1)/2)%MOD)%MOD;
        }
    }
    cout<<(f[n]+MOD)%MOD;
    return 0;
}