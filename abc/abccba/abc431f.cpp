#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e6+15,MOD=998244353;
int n,d,a[MN],pos[MN],ans=1,cnt[MN];
int pw[MN],inv[MN];

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

signed main(){
    initpw();
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    for(int i=1,lst=1;i<=n;i++){
        while(a[lst]+d<a[i]) lst++;
        ans=ans*(i-lst+1)%MOD;
        cnt[a[i]]++;
    }
    n=unique(a+1,a+1+n)-a-1;
    for(int i=1;i<=n;i++){
        ans=ans*inv[cnt[a[i]]]%MOD;
    }
    cout<<ans;

    return 0;
}