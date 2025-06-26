#include<bits/stdc++.h>
using namespace std;
constexpr int MN=1520;
int T,n,a[MN],b[MN];

void solve(){
    cin>>n;
    int x=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i]-a[i-1];
    }
    for(int i=n;i>=1;i-=2) x^=b[i];
    if(x) cout<<"TAK\n";
    else cout<<"NIE\n";
}

int main(){
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
