#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;

void solve(){
    int a,m;
    cin>>a>>m;
    int ret=0;
    for(int x=0;x<m;x++){
        if(__gcd(m,a)==__gcd(m,x+a)) ret++;
    }
    cout<<ret<<'\n';
}

signed main(){
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}