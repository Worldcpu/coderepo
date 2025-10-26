#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int pw[MN],inv[MN],n,a[MN],f[MN],ans,suml;

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
    f[1]=1;
    for(int i=3;i<MN;i+=2){
        f[i]=(i-2)*f[i-2]%MOD;
    }
}

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    initpw();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    
    a[0]=a[n+1]=-1;

    for(int i=2;i<=n+1;i++){
        if(i<=n&&(a[i]!=a[i-1]||a[i]!=a[i+1])&&a[i]!=(i&1)){
            cout<<0;
            return 0;
        }
    }

    for(int i=2,ql=1;i<=n+1;i++){
        if(a[i]!=a[i-1]){
            int len=i-ql;
            suml+=len/2;
            ql=i;
        }
    }
    ans=1;
    for(int i=2,ql=1,pre=0;i<=n+1;i++){
        if(a[i]!=a[i-1]){
            int len=i-ql;
            ans=ans*f[len]%MOD*getC(suml-pre,len/2)%MOD;
            pre+=len/2;
            ql=i;
        }
    }
    cout<<ans;
    return 0;
}