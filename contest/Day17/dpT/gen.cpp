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
    int T=MT,n;
    while(T--){
        n=getrd(5,10);
        cout<<n<<'\n';
        for(int i=1;i<=n;i++){
            cout<<(char)(getrd(0,1)+'a');
        }
        cout<<'\n';
        for(int i=1;i<=n;i++){
            cout<<(char)(getrd(0,1)+'a');
        }
        cout<<'\n';
        for(int i=1;i<=n;i++){
            cout<<(char)(getrd(0,1)+'a');
        }
        cout<<'\n';
    }
    
    return 0;
}