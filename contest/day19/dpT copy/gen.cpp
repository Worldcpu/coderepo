#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int n=10;
mt19937 mt(time(0));

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    freopen("dp.in","w",stdout);
    cout<<n<<'\n';
    for(int i=1;i<=n;i++){
        cout<<getrd(1,3)<<' ';
    }
    return 0;
}