#include<bits/stdc++.h>
using namespace std;
constexpr int T=5,N=1e5,V=1e9;
mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

void solve(){
    cout<<N<<'\n';
    for(int i=1;i<=N;i++) cout<<getrd(1,V)<<' ';
    cout<<'\n';
}

int main(){
    cout<<T<<'\n';
    int t=T;
    while(t--){
        solve();
    }
    return 0;
}