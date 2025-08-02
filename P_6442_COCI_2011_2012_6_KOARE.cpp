#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=22,MM=1e6+15,MOD=1e9+7;
int n,m,ans,f[1<<MN],pw2[MM];

void initpw(){
    pw2[0]=1;
    for(int i=1;i<MM;i++){
        pw2[i]=pw2[i-1]*2%MOD;
    }
}

signed main(){
    initpw();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k,st=(1<<m)-1;
        cin>>k;
        while(k--){
            int x;
            cin>>x;
            st^=(1<<(x-1));
        }
        f[st]++;
    }
    for(int i=0;i<21;i++){
        for(int j=0;j<(1<<21);j++){
            if((j>>i)&1){
                (f[j^(1<<i)]+=f[j])%=MOD;
            }
        }
    }
    for(int i=0;i<(1<<m);i++){
        int cnt=__builtin_popcountll(i);
        if(cnt&1){
            ans=(ans-pw2[f[i]]+MOD)%MOD;
        }
        else ans=(ans+pw2[f[i]])%MOD;
    }
    cout<<ans;
    return 0;
}