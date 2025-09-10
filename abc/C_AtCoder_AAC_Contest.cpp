#include<bits/stdc++.h>
#define int long long
using namespace std;
int na,nb,nc;

void solve(){
    cin>>na>>nb>>nc;
    int x=min(na,nc);
    cout<<min(x,(na+nb+nc)/3)<<'\n';
}

signed main(){
    int T;
    cin>>T;
    while(T--){
        solve();
    }

    return 0;
}