#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int ML=28,MN=5e5+15,MOD=998244353;
int cnt[ML][2],num[ML][ML][2][2],n,a[MN],pre[MN],ans;

void init(){
    for(int i=0;i<ML;i++){
        cnt[i][0]++;
        for(int j=i+1;j<ML;j++){
            num[i][j][0][0]++;
        }
    }
}

signed main(){
    init();
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pre[i]=pre[i-1]^a[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<ML;j++){
            int qwq=(1<<j)*(1ll<<j)%MOD,np=((pre[i]>>j)&1);
            ans=(ans+qwq*cnt[j][np^1]%MOD)%MOD;
            for(int k=j+1;k<ML;k++){
                int kp=((pre[i]>>k)&1);
                ans=(ans+num[j][k][np^1][kp^1]*2%MOD*(1ll<<j)%MOD*(1ll<<k)%MOD)%MOD;
            }
        }
        for(int j=0;j<ML;j++){
            int qwq=(1<<j)*(1ll<<j)%MOD,np=((pre[i]>>j)&1);
            cnt[j][np]++;
            for(int k=j+1;k<ML;k++){
                int kp=((pre[i]>>k)&1);
                num[j][k][np][kp]++;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}