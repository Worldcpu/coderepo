#include<bits/stdc++.h>
#include <random>
#define int long long
using namespace std;
constexpr int MT=120,N=20;
random_device rd;
mt19937 mt(rd());

int getrd(int l,int r){
    return mt()%(r-l+1)+l;
}

signed main(){
    freopen("dp.in","w",stdout);
    cout<<MT<<'\n';
    int T=MT;
    while(T--){
        int n=getrd(5,N);
        cout<<n<<'\n';
        for(int i=1;i<=n;i++){
            int l=getrd(1,n),r=getrd(1,n);
            if(l>r) swap(l,r);
            cout<<l<<' '<<r<<'\n';
        }
    }
    
    return 0;
}