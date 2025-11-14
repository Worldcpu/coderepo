#include<bits/stdc++.h>
using namespace std;
constexpr int MN=5e5+15;
int n,a[MN];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    if(is_sorted(a+1,a+1+n)){
        cout<<0<<'\n';
        return;
    }
    for(int i=1,mx=0;i<=n;i++){
        mx=max(mx,a[i]);
        if(a[i]==i&&mx==i){
            cout<<1<<'\n';
            return;
        }
    }
    if(a[1]==n&&a[n]==1){
        cout<<3<<'\n';
    }else cout<<2<<'\n';
}

int main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}