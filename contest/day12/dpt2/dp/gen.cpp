#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int n=2e6,m=1e6,T=100;
random_device rd;
mt19937 mt(rd());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    freopen("dp.in","w",stdout);
    cout<<T<<' '<<getrd(n-250,n)<<' '<<getrd(m-1000,m)<<'\n';
    int t=T;
    while(t--){
        cout<<getrd(1,2)<<'\n';
    }
    
    return 0;
}