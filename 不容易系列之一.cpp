#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=25;
int ans,pw[MN],n;

int getC(int a,int b){
    if(a<b) return 0;
    return pw[a]/(pw[b]*pw[a-b]);
}

void init(){
    pw[0]=1;
    for(int i=1;i<MN;i++){
        pw[i]=pw[i-1]*i;
    }
}

void solve(){
    ans=0;
    for(int i=0;i<=n;i++){
        ans+=getC(n,i)*((n-i)&1?-1:1)*pw[i];
    }
    cout<<ans<<'\n';
}

signed main(){
    init();
    while(cin>>n){
        solve();
    }
    return 0;
}
