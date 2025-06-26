#include<bits/stdc++.h>
#define int long long
#define ull long long
using namespace std;
constexpr int MN=1e5+15;
constexpr ull base=13331;
constexpr ull MOD1=1e9+7,MOD2=998244353;
int n,ans;
map<ull,int> mp;

ull bkdrhas1(string s){
    ull ans=0;
    for(int i=0;i<s.length();i++){
        ans=(ans*base+(ull)s[i])%MOD1;
    }
    return ans;
}

ull bkdrhas2(string s){
    ull ans=0;
    for(int i=0;i<s.length();i++){
        ans=(ans*base+(ull)s[i])%MOD2;
    }
    return ans;
}

ull ksm(ull a,int b,int MOD){
    ull ret=1;
    while(b){
        if(b&1) ret=ret*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ret;
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int awa;
        string s;
        cin>>awa>>s;
        ull ret1=bkdrhas1(s),ret2=bkdrhas2(s);
        ret1=ret1*ksm(ksm(base,awa,MOD1)-1,MOD1-2,MOD1)%MOD1;
        ret2=ret2*ksm(ksm(base,awa,MOD2)-1,MOD2-2,MOD2)%MOD2;
        ans+=mp[ret1*MOD2+ret2]++;
    }
    cout<<ans*2+n;
    return 0;
}
