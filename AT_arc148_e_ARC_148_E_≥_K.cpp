#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e5+15,MOD=998244353;
int a[MN],n,K,ans,pw[MN],inv[MN];

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
    ans=1;
    pw[0]=1;
    for(int i=1;i<MN;i++) pw[i]=pw[i-1]*i%MOD;
    inv[MN-1]=ksm(pw[MN-1],MOD-2);
    for(int i=MN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD;
}

signed main(){
    init();
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1,r=n,cnt=1;i<=n;i++){
        while(i<r&&a[i]+a[r]>=K){
            ans=ans*cnt%MOD;
            cnt++;
            r--;
        }
        if(i>r) break;
        ans=ans*cnt%MOD;
        cnt--;
    }
    for(int i=1,cnt=0;i<=n+1;i++){
        if(a[i]!=a[i-1]){
            ans=ans*inv[cnt]%MOD;
            cnt=1;
        }else cnt++;
    }
    cout<<ans;
    return 0;
}
