
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int MN=1e5+15;
int a,m;


int phi(int n){
    int ans=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0){
                n/=i;
            }
        }
    }
    if(n>=2){
        ans=ans/n*(n-1);
    }
    return ans;
}



void solve(){
    cin>>a>>m;
    cout<<phi(m/__gcd(a,m))<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}