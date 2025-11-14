#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353,MV=5e5;
int pw[MN],inv[MN],n,K,cnt[MN],ans;

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

int getC(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return pw[a]*inv[b]%MOD*inv[a-b]%MOD;
}

signed main(){
    initpw();
    cin>>n>>K;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        cnt[x]++;
    }
    for(int i=0,sum=0;i<=MV;i++){
        if(cnt[i]) continue;
        if(i!=0){
            ans=(ans+getC(i+K-sum-1,K-sum))%MOD;
        }
        sum++;
        if(sum>K) break;
    }
    cout<<ans;
    return 0;
}