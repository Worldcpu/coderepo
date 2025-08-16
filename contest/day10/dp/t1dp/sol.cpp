#include<bits/stdc++.h>
using namespace std;
constexpr int MN=2e5+15;
int n,a[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cout<<(a[n]-a[1]<=n+1?"YES\n":"NO\n");
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}