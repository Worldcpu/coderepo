#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=2e4+15,MOD=998244353;
int f[MN][2],n,m,ans,b[MN];
string st;
map<int,bool> mp;

void init(){
    ans=0;
    mp.clear();
    for(int i=1;i<=n;i++){
        b[i]=0;
        f[i][0]=f[i][1]=0;
    }
}

void solve(){
    cin>>n>>m>>st;
    init();   
    st="P"+st+"S";
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    b[n+1]=0;
    for(int i=0;i<=n;i++){
        if(st[i]=='S'||st[i+1]=='P') continue;
        int sum=b[i]+b[i+1];
        if(mp.count(sum)) continue;
        mp[sum]=1;
        f[0][0]=1;
        for(int i=1;i<=n+1;i++){
            f[i][0]=f[i][1]=0;
            if(st[i]!='S'){
                if(abs(b[i]-b[i-1])<=m) (f[i][0]+=f[i-1][0])%=MOD;
                int mx=b[i]+b[i-1]-sum;
                mx=mx/2+(mx%2);
                if(abs(mx)<=m){
                    f[i][0]=(f[i][0]+f[i-1][1])%MOD;
                }
            }
            if(st[i]!='P'){
                if(b[i-1]+b[i]==sum){
                    f[i][1]=(f[i][1]+f[i-1][0])%MOD;
                }
                if(abs(b[i]-b[i-1])<=m){
                    (f[i][1]+=f[i-1][1])%=MOD;
                }
            }
        }
        ans=(ans+f[n+1][1])%MOD;
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