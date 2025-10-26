#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=520,MOD=998244353,INV2=499122177;
int m,v,ans;

int ksm(int a,int b){
    int ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

int sum(int l,int r){
    return (l+r)*(r-l+1)%MOD*INV2%MOD;
}

void init(){
    ans=1;
}

void solve(){
    cin>>m>>v;
    init();
    while(m--){
        int op,l,r;
        cin>>op>>l>>r;
        if(op==1){
            ans=ans*(l+r)%MOD*INV2%MOD;
        }
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