#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=5e5+15,MOD=1e9+7;
int n,K,s[MN],f[MN],pwf[MN],ans,lst;

void init(){
    lst=-1;
    ans=1;
}

void solve(){
    cin>>n>>K;
    init();
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    sort(s+1,s+1+n);
    for(int i=1;i<=n&&K;i++){
        if(s[i]<=32&&K>=(1ll<<(s[i]-1))){
            K-=(1ll<<(s[i]-1));
            ans=ans*f[s[i]]%MOD;
        }else{
            K--;
            lst=s[i]-1;
            ans=ans*s[i]%MOD;
            break;
        }
    }
    while(1){
        if(!K) break;
        for(int i=1;i<=lst&&K;i++){
            if(K>=(1ll<<(i-1))){
                K-=(1ll<<(i-1));
                ans=ans*f[i]%MOD;
            }else{
                K--;
                lst=i-1;
                ans=ans*i%MOD;
                break;
            }
        }
    }
    cout<<(ans%MOD)<<'\n';
}

void initpw(){
    f[0]=pwf[0]=1;
    for(int i=1;i<MN;i++){
        f[i]=i*pwf[i-1]%MOD;
        pwf[i]=pwf[i-1]*f[i]%MOD;
    }
}

signed main(){
    initpw();
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}