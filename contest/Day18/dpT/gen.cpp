#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int MT=1;
mt19937 mt(time(0));

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    freopen("dp.in","w",stdout);
    cout<<getrd(100,1000);
    
    return 0;
}