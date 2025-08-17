#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int T=10;
random_device rd;
mt19937 mt(rd());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    freopen("dp.in","w",stdout);
    int t=T;
    cout<<t<<'\n';
    while(t--){
        int x=getrd(1,100),y=getrd(1,100);
        while(x==y){
            x=getrd(1,100);
            y=getrd(1,100);
        }
        cout<<x<<' '<<y<<'\n';
    }
    
    return 0;
}