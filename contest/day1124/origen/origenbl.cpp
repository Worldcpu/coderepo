#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int pre[MN],n,a[MN],ans,cnt[2];

void solvesub1(){
    cnt[0]=1;
    for(int i=1;i<=n;i++){
        ans=(ans+cnt[pre[i]^1])%MOD;       
        cnt[pre[i]]++;
    }
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=pre[i-1]^a[i];
    }
    if(*max_element(a+1,a+1+n)==1) solvesub1();
    else{
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                ans=(ans+(pre[j]^pre[i-1])*(pre[j]^pre[i-1])%MOD)%MOD;           
            }
        }
    }
    cout<<ans;
    return 0;
}
