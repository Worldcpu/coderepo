#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=998244353;
int n,mx,a[MN],f[2][MN],ans;
vector<int> vct[2];

void initdp(){
    ans=0;
    vct[0].clear();
    vct[1].clear();
    mx=0;
    for(int i=1;i<=n;i++){
        mx=max(mx,a[i]);
    }
    for(int i=0;i<=mx;i++){
        f[0][i]=f[1][i]=0;
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    initdp();
    int now=0,bef=1;
    for(int i=n;i>=1;i--){
        now^=1,bef^=1;
        int lst=a[i];
        vct[now].push_back(a[i]);
        f[now][a[i]]=1;
        for(auto p:vct[bef]){
            int cnt=ceil(1.0*a[i]/p),val=a[i]/cnt;
            f[now][val]=(f[now][val]+f[bef][p])%MOD;
            ans=(ans+(cnt-1)*i%MOD*f[bef][p]%MOD)%MOD;           
            if(lst!=val){
                vct[now].push_back(val);
                lst=val;
            }
        }
        for(auto p:vct[bef]) f[bef][p]=0;
        vct[bef].clear();
    }
    cout<<ans<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}