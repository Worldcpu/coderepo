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
    cout<<MT<<'\n';
    int T=MT;
    while(T--){
        int a=getrd(110,1e9),m=getrd(110,1e9);
        if(a==m){
            T++;
            continue;
        }
        if(a>m) swap(a,m);
        cout<<a<<' '<<m<<'\n';
    }
    
    return 0;
}